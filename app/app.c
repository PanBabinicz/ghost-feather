#include "app.h"
#include "rc.h"
#include "tim.h"
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
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void app_start(void)
{
    led_on();
    tim_init();
    rc_init();

    struct rc_dev *rc_dev_arr = rc_dev_arr_get();

    struct rc_dev *rc_dev_1 = &rc_dev_arr[RC_CH_1];
    struct rc_dev *rc_dev_2 = &rc_dev_arr[RC_CH_2];
    struct rc_dev *rc_dev_3 = &rc_dev_arr[RC_CH_3];
    struct rc_dev *rc_dev_4 = &rc_dev_arr[RC_CH_4];
    struct rc_dev *rc_dev_5 = &rc_dev_arr[RC_CH_5];
    struct rc_dev *rc_dev_6 = &rc_dev_arr[RC_CH_6];

    /* Never return */
    while (1)
    {
        rc_sig_raw_gen(RC_CH_1);
        rc_sig_raw_gen(RC_CH_2);
        rc_sig_raw_gen(RC_CH_3);
        rc_sig_raw_gen(RC_CH_4);
        rc_sig_raw_gen(RC_CH_5);
        rc_sig_raw_gen(RC_CH_6);
    }
}
