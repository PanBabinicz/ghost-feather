#include "app.h"
#include "ahrs.h"
#include "bmi270.h"
#include "cf.h"
#include "motor.h"
#include "pid.h"
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
/// \brief Initializes all the modules used in application.
///
static void app_init(void);

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
static void app_init(void)
{
    tim_init();
    rc_init();
    motor_init();
    cf_init(CF_INST_ROLL, 0.95f, 0.0f);
    cf_init(CF_INST_PITCH, 0.95f, 0.0f);
    pid_init(PID_INST_ROLL, 1.0f, 1.0f, 1.0f, 1.0f);
    pid_init(PID_INST_PITCH, 1.0f, 1.0f, 1.0f, 1.0f);
    ll_spi_dev_init(LL_SPI_INST_SPI1);

    //timing_delay_us(1000 * 1000 * 15);

    if (bmi270_init() != BMI270_RES_OK)
    {
        led_on();
        while(1);
    }
    bmi270_pwr_mode_set(BMI270_PWR_MODE_NORM_IMU);
}

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
    struct ahrs_dev *ahrs = ahrs_dev_get();

    struct rc_dev *rc_dev_arr = rc_dev_arr_get();
    struct rc_dev *rc_dev_3 = &rc_dev_arr[RC_CH_3];

    uint32_t dwt_cnt_start, dwt_cnt_stop, dwt_cnt_total;

    app_init();

    /* Never return */
    while (1)
    {
        dwt_cnt_start = timing_cnt_get();
        vtol_take_off_proc();

        bmi270_acc_read();
        bmi270_gyr_read();

        ahrs_acc_norm(bmi270_acc_get_x(), bmi270_acc_get_y(), bmi270_acc_get_z());
        ahrs_ang_calc();

        if (vtol_stat_get() == VTOL_STAT_ON)
        {

            struct rc_sig *roll     = &rc_dev_arr[RC_CH_4].sig;
            struct rc_sig *pitch    = &rc_dev_arr[RC_CH_2].sig;
            struct rc_sig *throttle = &rc_dev_arr[RC_CH_3].sig;
            struct rc_sig *yaw      = &rc_dev_arr[RC_CH_1].sig;

            int32_t pwm1, pwm2, pwm3, pwm4;

            rc_sig_raw_gen(RC_CH_1);
            rc_sig_raw_gen(RC_CH_2);
            rc_sig_raw_gen(RC_CH_3);
            rc_sig_raw_gen(RC_CH_4);

            rc_sig_norm(RC_CH_1);
            rc_sig_norm(RC_CH_2);
            rc_sig_norm(RC_CH_3);
            rc_sig_norm(RC_CH_4);

            throttle->norm = (throttle->norm > 1.0) ? 1.0 : throttle->norm;

            if (throttle->norm > 0.3)
            {
                roll->norm = (roll->norm >  1.0) ?  1.0 : roll->norm;
                roll->norm = (roll->norm < -1.0) ? -1.0 : roll->norm;

                pitch->norm = (pitch->norm >  1.0) ?  1.0 : pitch->norm;
                pitch->norm = (pitch->norm < -1.0) ? -1.0 : pitch->norm;

                yaw->norm = (yaw->norm >  1.0) ?  1.0 : yaw->norm;
                yaw->norm = (yaw->norm < -1.0) ? -1.0 : yaw->norm;
            }
            else
            {
                roll->norm  = 0.0;
                pitch->norm = 0.0;
                yaw->norm   = 0.0;
            }

            pwm1 = 1000 + (1000 * (throttle->norm - roll->norm + pitch->norm + yaw->norm));
            pwm2 = 1000 + (1000 * (throttle->norm + roll->norm + pitch->norm - yaw->norm));
            pwm3 = 1000 + (1000 * (throttle->norm + roll->norm - pitch->norm + yaw->norm));
            pwm4 = 1000 + (1000 * (throttle->norm - roll->norm - pitch->norm - yaw->norm));

            pwm1 = (pwm1 > 2000) ? 2000 : pwm1;
            pwm1 = (pwm1 < 1000) ? 1000 : pwm1;

            pwm2 = (pwm2 > 2000) ? 2000 : pwm2;
            pwm2 = (pwm2 < 1000) ? 1000 : pwm2;

            pwm3 = (pwm3 > 2000) ? 2000 : pwm3;
            pwm3 = (pwm3 < 1000) ? 1000 : pwm3;

            pwm4 = (pwm4 > 2000) ? 2000 : pwm4;
            pwm4 = (pwm4 < 1000) ? 1000 : pwm4;

            motor_upd(MOTOR_1, pwm1);
            motor_upd(MOTOR_2, pwm2);
            motor_upd(MOTOR_3, pwm3);
            motor_upd(MOTOR_4, pwm4);
        }

        vtol_land_proc();

        dwt_cnt_stop = timing_cnt_get();
        dwt_cnt_total = dwt_cnt_stop - dwt_cnt_start;
    }
}
