#include "bmi270.h"
#include "bmi270_conf.h"
#include "app.h"
#include "memory_map.h"
#include "ghost_feather_common.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Turns the LED on.
///
static void led_on(void);

///
/// \brief Turns the LED off.
///
static void led_off(void);

///
/// \brief Turns the LED panic mode.
///
static void led_panic(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static void led_on(void)
{
    gpio_set(GPIOA, GPIO2);
}

static void led_off(void)
{
    gpio_clear(GPIOA, GPIO2);
}

static void led_panic(void)
{
    while (1)
    {
        systick_delay_us(500000);
        gpio_toggle(GPIOA, GPIO2);
    }
}

void _systick_handler(void)
{
    systick_cnt++;
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void app_start(void)
{
    systick_init(GHOST_FEATHER_COMMON_US_IN_CYCLES);

    //led_on();
    led_panic();

    struct bmi270_dev *bmi270 = bmi270_dev_get();

    /* Never return */
    while (1);
}
