#include "bmi270.h"
#include "bmi270_conf.h"
#include "stm32f722xx_app.h"
#include "stm32f722xx_memory_map.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Sets the Reset and Clock Control registers.
///
/// This function initializes the system's clock configuration by setting up
/// the Reset and Clock Control (RCC) registers for the desired system
/// performance and peripheral clock settings.
///
static void rcc_setup(void);

///
/// \brief Sets GPIO pins for the application.
///
/// This function initializes the General Purpose Input/Output (GPIO) pins
/// required by the application.
///
static void gpio_setup(void);

///
/// \brief Turns the LED on.
///
static void led_on(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static void rcc_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
}

static void gpio_setup(void)
{
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);
}

static void led_on(void)
{
    gpio_set(GPIOA, GPIO2);
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void app_start(void)
{
    rcc_setup();
    gpio_setup();

    /* Turn on the green led to signalize that it reached the application. */
    led_on();

    struct bmi270_dev *bmi270 = bmi270_dev_get();

    /* Never return */
    while (1);
}
