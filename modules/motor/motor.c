#include "motor.h"
#include "rc.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The motor devices array.
///
static struct motor_dev motor_dev_arr[MOTOR_TOTAL];

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
struct motor_dev* motor_dev_arr_get(void)
{
    return &motor_dev_arr[0];
}

void motor_init(void)
{
    struct tim_dev *tim_dev_arr = tim_dev_arr_get();

    motor_dev_arr[MOTOR_1].tim = &tim_dev_arr[TIM_INST_4];
    motor_dev_arr[MOTOR_2].tim = &tim_dev_arr[TIM_INST_4];
    motor_dev_arr[MOTOR_3].tim = &tim_dev_arr[TIM_INST_4];
    motor_dev_arr[MOTOR_4].tim = &tim_dev_arr[TIM_INST_4];

    motor_dev_arr[MOTOR_1].ccr_ch = LL_TIM_CCR_CH1;
    motor_dev_arr[MOTOR_2].ccr_ch = LL_TIM_CCR_CH2;
    motor_dev_arr[MOTOR_3].ccr_ch = LL_TIM_CCR_CH3;
    motor_dev_arr[MOTOR_4].ccr_ch = LL_TIM_CCR_CH4;
}

void motor_upd(const motor_t motor, const uint32_t pwm)
{
    struct motor_dev *dev = &motor_dev_arr[motor];
    dev->tim->ccr_set(dev->tim->tim, dev->ccr_ch, pwm);
}
