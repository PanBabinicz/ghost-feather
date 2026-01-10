#ifndef _MOTOR_H
#define _MOTOR_H

#include <stdint.h>
#include "tim.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The motor indentifiers.
///
typedef enum motor
{
    MOTOR_BEGIN = 0,
    MOTOR_1     = 0,
    MOTOR_2,
    MOTOR_3,
    MOTOR_4,
    MOTOR_TOTAL,
} motor_t;

///
/// \brief The motor device.
///
struct motor_dev
{
    struct tim_dev *tim;
    struct ll_tim_ccr_data ccr_data;
    ll_tim_ccr_ch_t ccr_ch;
};

///
/// \brief Gets the motor device array.
///
/// \return struct motor_dev* The address of first motor device.
///
struct motor_dev* motor_dev_arr_get(void);

///
/// \brief Initializes all motor devices.
///
void motor_init(void);

///
/// brief Updates selected motor using PWM signal.
///
/// param[in] motor_t  motor The motor identifier.
/// param[in] uint32_t pwm   The PWM signal.
///
void motor_upd(const motor_t motor, const uint32_t pwm);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _MOTOR_H */
