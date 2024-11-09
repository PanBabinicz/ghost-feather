#include "stm32f722xx_second_bootloader.h"
#include "stm32f722xx_memory_map.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

static void rcc_setup(void);
static void gpio_setup(void);
static void led_on(void);

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
    
    /* Never return */
    while (1);

}
