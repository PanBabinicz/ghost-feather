#include "app.h"
#include "motor.h"
#include "rc.h"
#include "tim.h"
#include "vtol.h"
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
    motor_init();

    struct rc_dev *rc_dev_arr = rc_dev_arr_get();
    struct rc_dev *rc_dev_3 = &rc_dev_arr[RC_CH_3];

    /* Never return */
    while (1)
    {
        vtol_take_off_proc();

        if (vtol_stat_get() == VTOL_STAT_ON)
        {
            struct rc_sig *throttle = &rc_dev_arr[RC_CH_3].sig;
            rc_sig_raw_gen(RC_CH_3);
            rc_sig_norm(RC_CH_3);

            throttle->norm = (throttle->norm > 1.0) ? 1.0 : throttle->norm;

            motor_upd(MOTOR_INST_1, 1000 + (1000 * (0)));
            motor_upd(MOTOR_INST_2, 1000 + (1000 * (throttle->norm)));
            motor_upd(MOTOR_INST_3, 1000 + (1000 * (0)));
            motor_upd(MOTOR_INST_4, 1000 + (1000 * (0)));
        }

        vtol_land_proc();
    }
}
