#include "stm32f722xx_first_bootloader.h"
#include "stm32f722xx_memory_map.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

static void second_bootloader_startup(uint32_t sp, uint32_t pc);
static void rcc_setup(void);
static void gpio_setup(void);
static void led_on(void);

__attribute__((naked))
static void second_bootloader_startup(uint32_t pc, uint32_t sp)
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
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);
}

static void led_on(void)
{
    gpio_set(GPIOB, GPIO7);
}

void first_bootloader_start(void)
{
    rcc_setup();
    gpio_setup();

    /* Turn on the blue led to signalize that we reached the first bootloader */
    led_on();

    uint32_t *second_bootloader_code         = (uint32_t*)&__bootrom2_start__;
    uint32_t second_bootloader_stack_pointer = second_bootloader_code[0];
    uint32_t second_bootloader_reset_handler = second_bootloader_code[1];

    second_bootloader_startup(second_bootloader_reset_handler, second_bootloader_stack_pointer);
    
    /* Never return */
    while (1);

}
