#include "app.h"
#include "ahrs.h"
#include "bmi270.h"
#include "cf.h"
#include "ghf.h"
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

///
/// \brief The maximum degree used to map RC normalized signal.
///
static const float32_t max_degree = 30.0f;

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
/// \brief Enters the safe mode. All motors are turned off until safe mode is deactivated.
///
static void enter_safe_mode(struct ghf *const handle);

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

static void enter_safe_mode(struct ghf *const handle)
{
    motor_update(ghf->module.motor_1, 1000);
    motor_update(ghf->module.motor_2, 1000);
    motor_update(ghf->module.motor_3, 1000);
    motor_update(ghf->module.motor_4, 1000);

    while (ghf->module.rc_5->sig.norm > 0.8f)
    {
        rc_sig_raw_gen(ghf->module.rc_5);
        rc_sig_norm(ghf->module.rc_5, RC_NORM_ASYM);

        led_on();
        timing_delay_us(1000 * 1000);
        led_off();
        timing_delay_us(1000 * 1000);
    }
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void app_start(void)
{
    struct ghf *ghf = ghf_get();

    led_on();
    ghf_init(ghf);
    led_off();

    /* Never return */
    while (1)
    {
        ghf->data.time.start = timing_cnt_get();
        vtol_take_off_proc();

        if (vtol_stat_get() == VTOL_STAT_ON)
        {
            bmi270_acc_read();
            bmi270_gyr_read();

            ghf->data.raw_data.ax = bmi270_acc_get_x();
            ghf->data.raw_data.ay = bmi270_acc_get_y();
            ghf->data.raw_data.az = bmi270_acc_get_z();
            ghf->data.raw_data.gx = bmi270_gyr_get_x() - ghf->data.calib.gx;
            ghf->data.raw_data.gy = bmi270_gyr_get_y() - ghf->data.calib.gy;
            ghf->data.raw_data.gz = bmi270_gyr_get_z() - ghf->data.calib.gz;

            ahrs_update(ghf->module.ahrs, &ghf->data.raw_data);

            rc_sig_raw_gen(ghf->module.rc_1);
            rc_sig_raw_gen(ghf->module.rc_2);
            rc_sig_raw_gen(ghf->module.rc_3);
            rc_sig_raw_gen(ghf->module.rc_4);
            rc_sig_raw_gen(ghf->module.rc_5);

            rc_sig_norm(ghf->module.rc_1, RC_NORM_SYM);
            rc_sig_norm(ghf->module.rc_2, RC_NORM_SYM);
            rc_sig_norm(ghf->module.rc_3, RC_NORM_ASYM);
            rc_sig_norm(ghf->module.rc_4, RC_NORM_SYM);
            rc_sig_corm(ghf->module.rc_5, RC_NORM_ASYM);

            ghf->data.throttle = ghf->module.rc_3->sig.norm;

            ghf->data.roll  = pid_update(ghf->module.pid_roll,  ghf->module.rc_1->sig.norm*max_degree, ghf->module.ahrs->out.roll);
            ghf->data.pitch = pid_update(ghf->module.pid_pitch, ghf->module.rc_2->sig.norm*max_degree, ghf->module.ahrs->out.pitch);
            ghf->data.yaw   = pid_update(ghf->module.pid_yaw,   ghf->module.rc_4->sig.norm*max_degree, ghf->module.ahrs->out.yaw);
            //ghf->data.yaw   = ghf->module.rc_4->sig.norm * 0.66f;

            if (ghf->data.throttle < 0.2f)
            {
                ghf->data.roll  = 0.0f;
                ghf->data.pitch = 0.0f;
                ghf->data.yaw   = 0.0f;
            }

            ghf->data.pwm1 = 1000 + (1000 * (ghf->data.throttle + ghf->data.roll + ghf->data.pitch + ghf->data.yaw));
            ghf->data.pwm2 = 1000 + (1000 * (ghf->data.throttle - ghf->data.roll + ghf->data.pitch - ghf->data.yaw));
            ghf->data.pwm3 = 1000 + (1000 * (ghf->data.throttle + ghf->data.roll - ghf->data.pitch - ghf->data.yaw));
            ghf->data.pwm4 = 1000 + (1000 * (ghf->data.throttle - ghf->data.roll - ghf->data.pitch + ghf->data.yaw));

            ghf->data.pwm1 = (ghf->data.pwm1 > 2000) ? 2000 : ghf->data.pwm1;
            ghf->data.pwm1 = (ghf->data.pwm1 < 1000) ? 1000 : ghf->data.pwm1;

            ghf->data.pwm2 = (ghf->data.pwm2 > 2000) ? 2000 : ghf->data.pwm2;
            ghf->data.pwm2 = (ghf->data.pwm2 < 1000) ? 1000 : ghf->data.pwm2;

            ghf->data.pwm3 = (ghf->data.pwm3 > 2000) ? 2000 : ghf->data.pwm3;
            ghf->data.pwm3 = (ghf->data.pwm3 < 1000) ? 1000 : ghf->data.pwm3;

            ghf->data.pwm4 = (ghf->data.pwm4 > 2000) ? 2000 : ghf->data.pwm4;
            ghf->data.pwm4 = (ghf->data.pwm4 < 1000) ? 1000 : ghf->data.pwm4;

            motor_update(ghf->module.motor_1, ghf->data.pwm1);
            motor_update(ghf->module.motor_2, ghf->data.pwm2);
            motor_update(ghf->module.motor_3, ghf->data.pwm3);
            motor_update(ghf->module.motor_4, ghf->data.pwm4);

            /* Safe mode. */
            if (ghf->module.rc_5->sig.norm > 0.8f)
            {
                enter_safe_mode(ghf);
            }
        }

        vtol_land_proc();

        do
        {
            ghf->data.time.stop  = timing_cnt_get();
            ghf->data.time.total = ghf->data.time.stop - ghf->data.time.start;
            ghf->data.time.total = ghf->data.time.total * TIMING_TICK_DURATION * 1000000;
        } while (ghf->data.time.total < ghf->config.dt * 1000000);
    }
}
