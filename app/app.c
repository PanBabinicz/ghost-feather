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

struct ghf_time
{
    uint32_t start;
    uint32_t stop;
    uint32_t total;
};

struct ghf_data
{
    struct ghf_time time;
    float32_t roll;
    float32_t pitch;
    float32_t throttle;
    float32_t yaw;
    uint32_t  pwm1;
    uint32_t  pwm2;
    uint32_t  pwm3;
    uint32_t  pwm4;
    struct ahrs_raw_data raw_data;
    struct ahrs_calib calib;
};

struct ghf_config
{
    float32_t kp;
    float32_t ki;
    float32_t kd;
    float32_t acc_scale;
    float32_t gyr_scale;
    float32_t alpha;
    float32_t dt;
};

struct ghf_module
{
    struct ahrs  *ahrs;
    struct rc    *rc_1;
    struct rc    *rc_2;
    struct rc    *rc_3;
    struct rc    *rc_4;
    struct rc    *rc_5;
    struct rc    *rc_6;
    struct motor *motor_1;
    struct motor *motor_2;
    struct motor *motor_3;
    struct motor *motor_4;
    struct pid   *pid_roll;
    struct pid   *pid_pitch;
    struct pid   *pid_yaw;
};

struct ghf
{
    struct ghf_module module;
    struct ghf_config config;
    struct ghf_data   data;
};

static const float32_t max_degree = 30.0f;

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief
///
static void app_setup(struct ghf *const handle);

///
/// \brief Initializes all the modules used in application.
///
static void app_init(struct ghf *const handle);

///
/// \brief
///
static void app_calib(struct ghf *const handle);

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
static void app_setup(struct ghf *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    handle->module.ahrs = ahrs_get();

    handle->module.rc_1 = rc_get(RC_CH_1);
    handle->module.rc_2 = rc_get(RC_CH_2);
    handle->module.rc_3 = rc_get(RC_CH_3);
    handle->module.rc_4 = rc_get(RC_CH_4);
    handle->module.rc_5 = rc_get(RC_CH_5);
    handle->module.rc_6 = rc_get(RC_CH_6);

    handle->module.motor_1 = motor_get(MOTOR_INST_1);
    handle->module.motor_2 = motor_get(MOTOR_INST_2);
    handle->module.motor_3 = motor_get(MOTOR_INST_3);
    handle->module.motor_4 = motor_get(MOTOR_INST_4);

    handle->module.pid_roll  = pid_get(PID_INST_ROLL);
    handle->module.pid_pitch = pid_get(PID_INST_PITCH);
    handle->module.pid_yaw   = pid_get(PID_INST_YAW);

    handle->config.kp        = 0.01f;
    handle->config.ki        = 0.00f;
    handle->config.kd        = 0.00f;
    handle->config.acc_scale = 1.0f / 4096.0f;
    handle->config.gyr_scale = 1.0f / 16.4f;
    handle->config.alpha     = 0.1f;
    handle->config.dt        = 1.0f / 4000.0f;

    handle->data.time.start = 0;
    handle->data.time.stop  = 0;
    handle->data.time.total = 0;

    handle->data.pwm1 = 0;
    handle->data.pwm2 = 0;
    handle->data.pwm3 = 0;
    handle->data.pwm4 = 0;

    handle->data.roll     = 0.0f;
    handle->data.pitch    = 0.0f;
    handle->data.throttle = 0.0f;
    handle->data.yaw      = 0.0f;

    handle->data.raw_data.ax = 0;
    handle->data.raw_data.ay = 0;
    handle->data.raw_data.az = 0;
    handle->data.raw_data.gx = 0;
    handle->data.raw_data.gy = 0;
    handle->data.raw_data.gz = 0;

    handle->data.calib.gx = 0;
    handle->data.calib.gy = 0;
    handle->data.calib.gz = 0;
}

static void app_init(struct ghf *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    ll_spi_dev_init(LL_SPI_INST_SPI1);

    tim_init();

    ahrs_init(handle->module.ahrs, handle->config.acc_scale, handle->config.gyr_scale,
            handle->config.alpha, handle->config.dt);

    rc_init(handle->module.rc_1, TIM_INST_12, LL_TIM_CCR_CH1);
    rc_init(handle->module.rc_2, TIM_INST_12, LL_TIM_CCR_CH2);
    rc_init(handle->module.rc_3, TIM_INST_8,  LL_TIM_CCR_CH1);
    rc_init(handle->module.rc_4, TIM_INST_8,  LL_TIM_CCR_CH2);
    rc_init(handle->module.rc_5, TIM_INST_8,  LL_TIM_CCR_CH3);
    rc_init(handle->module.rc_6, TIM_INST_8,  LL_TIM_CCR_CH4);

    motor_init(handle->module.motor_1, TIM_INST_4, LL_TIM_CCR_CH1);
    motor_init(handle->module.motor_2, TIM_INST_4, LL_TIM_CCR_CH2);
    motor_init(handle->module.motor_3, TIM_INST_4, LL_TIM_CCR_CH3);
    motor_init(handle->module.motor_4, TIM_INST_4, LL_TIM_CCR_CH4);

    pid_init(handle->module.pid_roll,  handle->config.kp, handle->config.ki, handle->config.kd, handle->config.dt);
    pid_init(handle->module.pid_pitch, handle->config.kp, handle->config.ki, handle->config.kd, handle->config.dt);
    pid_init(handle->module.pid_yaw,   handle->config.kp, handle->config.ki, handle->config.kd, handle->config.dt);

    timing_delay_us(1000 * 1000 * 5);

    if (bmi270_init() != BMI270_RES_OK)
    {
        while(1);
    }
    bmi270_pwr_mode_set(BMI270_PWR_MODE_NORM_IMU);
}

static void app_calib(struct ghf *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    int32_t gx = 0;
    int32_t gz = 0;
    int32_t gy = 0;

    for (int i=0; i<100; ++i)
    {
        bmi270_gyr_read();
        gx += bmi270_gyr_get_x();
        gy += bmi270_gyr_get_y();
        gz += bmi270_gyr_get_z();
    }

    handle->data.calib.gx = gx / 100;
    handle->data.calib.gy = gy / 100;
    handle->data.calib.gz = gz / 100;
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
    struct ghf ghf;

    float32_t time_in_us;
    float32_t time;

    led_on();
    app_setup(&ghf);
    app_init(&ghf);
    app_calib(&ghf);
    led_off();

    /* Never return */
    while (1)
    {
        ghf.data.time.start = timing_cnt_get();
        vtol_take_off_proc();

        if (vtol_stat_get() == VTOL_STAT_ON)
        {
            bmi270_acc_read();
            bmi270_gyr_read();

            ghf.data.raw_data.ax = bmi270_acc_get_x();
            ghf.data.raw_data.ay = bmi270_acc_get_y();
            ghf.data.raw_data.az = bmi270_acc_get_z();
            ghf.data.raw_data.gx = bmi270_gyr_get_x() - ghf.data.calib.gx;
            ghf.data.raw_data.gy = bmi270_gyr_get_y() - ghf.data.calib.gy;
            ghf.data.raw_data.gz = bmi270_gyr_get_z() - ghf.data.calib.gz;

            ahrs_update(ghf.module.ahrs, &ghf.data.raw_data);

            rc_sig_raw_gen(ghf.module.rc_1);
            rc_sig_raw_gen(ghf.module.rc_2);
            rc_sig_raw_gen(ghf.module.rc_3);
            rc_sig_raw_gen(ghf.module.rc_4);

            rc_sig_norm(ghf.module.rc_1, RC_NORM_SYM);
            rc_sig_norm(ghf.module.rc_2, RC_NORM_SYM);
            rc_sig_norm(ghf.module.rc_3, RC_NORM_ASYM);
            rc_sig_norm(ghf.module.rc_4, RC_NORM_SYM);

            ghf.data.throttle = ghf.module.rc_3->sig.norm;

            ghf.data.roll  = pid_update(ghf.module.pid_roll,  ghf.module.rc_1->sig.norm*max_degree, ghf.module.ahrs->out.roll);
            ghf.data.pitch = pid_update(ghf.module.pid_pitch, ghf.module.rc_2->sig.norm*max_degree, ghf.module.ahrs->out.pitch);
            ghf.data.yaw   = pid_update(ghf.module.pid_yaw,   ghf.module.rc_4->sig.norm*max_degree, ghf.module.ahrs->out.yaw);
            //ghf.data.yaw   = ghf.module.rc_4->sig.norm * 0.66f;

            if (ghf.data.throttle < 0.2f)
            {
                ghf.data.roll  = 0.0f;
                ghf.data.pitch = 0.0f;
                ghf.data.yaw   = 0.0f;
            }

            ghf.data.pwm1 = 1000 + (1000 * (ghf.data.throttle + ghf.data.roll + ghf.data.pitch + ghf.data.yaw));
            ghf.data.pwm2 = 1000 + (1000 * (ghf.data.throttle - ghf.data.roll + ghf.data.pitch - ghf.data.yaw));
            ghf.data.pwm3 = 1000 + (1000 * (ghf.data.throttle + ghf.data.roll - ghf.data.pitch - ghf.data.yaw));
            ghf.data.pwm4 = 1000 + (1000 * (ghf.data.throttle - ghf.data.roll - ghf.data.pitch + ghf.data.yaw));

            ghf.data.pwm1 = (ghf.data.pwm1 > 2000) ? 2000 : ghf.data.pwm1;
            ghf.data.pwm1 = (ghf.data.pwm1 < 1000) ? 1000 : ghf.data.pwm1;

            ghf.data.pwm2 = (ghf.data.pwm2 > 2000) ? 2000 : ghf.data.pwm2;
            ghf.data.pwm2 = (ghf.data.pwm2 < 1000) ? 1000 : ghf.data.pwm2;

            ghf.data.pwm3 = (ghf.data.pwm3 > 2000) ? 2000 : ghf.data.pwm3;
            ghf.data.pwm3 = (ghf.data.pwm3 < 1000) ? 1000 : ghf.data.pwm3;

            ghf.data.pwm4 = (ghf.data.pwm4 > 2000) ? 2000 : ghf.data.pwm4;
            ghf.data.pwm4 = (ghf.data.pwm4 < 1000) ? 1000 : ghf.data.pwm4;

            motor_update(ghf.module.motor_1, ghf.data.pwm1);
            motor_update(ghf.module.motor_2, ghf.data.pwm2);
            motor_update(ghf.module.motor_3, ghf.data.pwm3);
            motor_update(ghf.module.motor_4, ghf.data.pwm4);
        }

        vtol_land_proc();

        //time = (timing_cnt_get() - ghf.data.time.start) * TIMING_TICK_DURATION * 1000000;

        do
        {
            ghf.data.time.stop  = timing_cnt_get();
            ghf.data.time.total = ghf.data.time.stop - ghf.data.time.start;
            ghf.data.time.total = ghf.data.time.total * TIMING_TICK_DURATION * 1000000;
        } while (ghf.data.time.total < ghf.config.dt * 1000000);

        time = ghf.data.time.total;
    }
}
