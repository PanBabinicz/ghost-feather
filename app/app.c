#include "app.h"
#include "bmi270.h"
#include "motor.h"
#include "rc.h"
#include "tim.h"
#include "timing.h"
#include "ll_spi.h"
#include "vtol.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

#include <math.h>

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
    (void)timing_init();

    struct ll_spi_dev* spi1 = ll_spi_dev_get();
    ll_spi_dev_init(spi1);

    if (bmi270_init() != BMI270_RES_OK)
    {
        while(1);
    }
    bmi270_pwr_mode_set(BMI270_PWR_MODE_NORM_IMU);

    struct rc_dev *rc_dev_arr = rc_dev_arr_get();
    struct rc_dev *rc_dev_3 = &rc_dev_arr[RC_CH_3];

    int16_t acc_x, acc_y, acc_z;
    int16_t gyr_x, gyr_y, gyr_z;

    uint32_t dwt_cnt_start, dwt_cnt_stop, dwt_cnt_total;

    float32_t acc_x_norm, acc_y_norm, acc_z_norm;
    float32_t acc_norm, acc_roll_ang, acc_pitch_ang;

    timing_start();

    /* Never return */
    while (1)
    {
        dwt_cnt_start = timing_cnt_get();
        vtol_take_off_proc();

        bmi270_acc_read();
        bmi270_gyr_read();

        acc_x = bmi270_acc_get_x();
        acc_y = bmi270_acc_get_y();
        acc_z = bmi270_acc_get_z();

        gyr_x = bmi270_gyr_get_x();
        gyr_y = bmi270_gyr_get_y();
        gyr_z = bmi270_gyr_get_z();

        acc_norm = sqrtf((acc_x * acc_x) + (acc_y * acc_y) + (acc_z * acc_z));

        acc_x_norm = acc_x / acc_norm;
        acc_y_norm = acc_y / acc_norm;
        acc_z_norm = acc_z / acc_norm;

        acc_roll_ang = atan2(acc_y, acc_z);
        acc_roll_ang *= 57.2958;

        if (vtol_stat_get() == VTOL_STAT_ON)
        {
            struct rc_sig *roll     = &rc_dev_arr[RC_CH_1].sig;
            struct rc_sig *pitch    = &rc_dev_arr[RC_CH_2].sig;
            struct rc_sig *throttle = &rc_dev_arr[RC_CH_3].sig;
            struct rc_sig *yaw      = &rc_dev_arr[RC_CH_4].sig;

            rc_sig_raw_gen(RC_CH_1);
            rc_sig_raw_gen(RC_CH_2);
            rc_sig_raw_gen(RC_CH_3);
            rc_sig_raw_gen(RC_CH_4);

            rc_sig_norm(RC_CH_1);
            rc_sig_norm(RC_CH_2);
            rc_sig_norm(RC_CH_3);
            rc_sig_norm(RC_CH_4);

            roll->norm     = (roll->norm > 1.0) ? 1.0 : roll->norm;
            pitch->norm    = (pitch->norm > 1.0) ? 1.0 : pitch->norm;
            throttle->norm = (throttle->norm > 1.0) ? 1.0 : throttle->norm;
            yaw->norm      = (yaw->norm > 1.0) ? 1.0 : yaw->norm;

            //motor_upd(MOTOR_INST_1, 1000 + (1000 * (0)));
            //motor_upd(MOTOR_INST_2, 1000 + (1000 * (throttle->norm)));
            //motor_upd(MOTOR_INST_3, 1000 + (1000 * (0)));
            //motor_upd(MOTOR_INST_4, 1000 + (1000 * (0)));
        }

        vtol_land_proc();

        dwt_cnt_stop = timing_cnt_get();
        dwt_cnt_total = dwt_cnt_stop - dwt_cnt_start;
    }
}
