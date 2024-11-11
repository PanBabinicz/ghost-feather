#include "stm32f722xx_second_bootloader.h"
#include "stm32f722xx_memory_map.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

static void app_startup(uint32_t pc, uint32_t sp);
static void rcc_setup(void);
static void gpio_setup(void);
static void led_on(void);

__attribute__((naked))
static void app_startup(uint32_t pc, uint32_t sp)
{
    __asm("                                             \n\
          .syntax unified                               \n\
          .cpu cortex-m7                                \n\
          .thumb                                        \n\
          msr msp, r1 /* load r1 into MSP */            \n\
          bx r0       /* branch to the address at r0 */ \n\
    ");
}

static void rcc_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
}

static void gpio_setup(void)
{
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);
}

static void led_on(void)
{
    gpio_set(GPIOB, GPIO14);
}

void second_bootloader_start(void)
{
    rcc_setup();
    gpio_setup();

    /* Turn on the red led to signalize that we reached the second bootloader */
    led_on();

    uint32_t *app_code         = (uint32_t*)&__approm_start__;
    uint32_t app_stack_pointer = app_code[0];
    uint32_t app_reset_handler = app_code[1];

    app_startup(app_reset_handler, app_stack_pointer);
    
    /* Never return */
    while (1);

}
