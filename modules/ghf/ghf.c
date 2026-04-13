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

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The ghf object.
///
static struct ghf ghf;

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief Setups the ghf.
///
/// \param[in] The pointer to ghf.
///
static void setup(struct ghf *const handle);

///
/// \brief Calibrates the ghf IMU.
///
/// \param[in] The pointer to ghf.
///
static void calib(struct ghf *const handle);

///
/// \brief Checks the ready signal from radio.
///
/// \param[in] The pointer to ghf.
///
static void is_ready(struct ghf *const handle);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static void setup(struct ghf *const handle)
{
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

static void calib(struct ghf *const handle)
{
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

static void is_ready(struct ghf *const handle)
{
    rc_sig_raw_gen(handle->module.rc_6);
    rc_sig_norm(handle->module.rc_6, RC_NORM_ASYM);

    while (handle->module.rc_6->sig.norm > 0.8f)
    {
        rc_sig_raw_gen(handle->module.rc_6);
        rc_sig_norm(handle->module.rc_6, RC_NORM_ASYM);
    }
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void ghf_init(struct ghf *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    setup(handle);

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

    is_ready(handle);

    if (bmi270_init() != BMI270_RES_OK)
    {
        while(1);
    }
    bmi270_pwr_mode_set(BMI270_PWR_MODE_NORM_IMU);

    calib(handle);
}

void ghf_deinit(struct ghf *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    memset(handle, 0, sizeof(struct ghf));
}

struct ghf* ghf_get(void)
{
    return &ghf;
}
