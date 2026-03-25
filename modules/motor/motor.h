#ifndef _MOTOR_H
#define _MOTOR_H

#include <stdint.h>
#include "tim.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The motor instance type.
///
typedef enum motor_inst
{
    MOTOR_INST_BEGIN = 0,
    MOTOR_INST_1     = 0,
    MOTOR_INST_2,
    MOTOR_INST_3,
    MOTOR_INST_4,
    MOTOR_INST_TOTAL,
} motor_inst_t;

///
/// \brief The motor structure.
///
struct motor
{
    struct tim_dev *tim;
    struct ll_tim_ccr_data ccr_data;
    ll_tim_ccr_ch_t ccr_ch;
};

///
/// \brief Initializes selected motor.
///
/// \param[in] handle The pointer to the motor.
/// \param[in] inst   The timer instance.
/// \param[in] ch     The timer capture/compare channel.
///
void motor_init(struct motor *const handle, const tim_inst_t inst, const ll_tim_ccr_ch_t ch);

///
/// \brief Deinitializes selected motor.
///
/// \param[in] handle The pointer to the motor.
///
void motor_deinit(struct motor *const handle);

///
/// \brief Gets the motor pointer.
///
/// \param[in] inst The motor instance.
///
/// \return struct motor* The motor pointer.
///
struct motor* motor_get(const motor_inst_t inst);

///
/// \brief Updates the motor using PWM signal.
///
/// \param[in] handle The pointer to the motor.
/// \param[in] pwm    The PWM signal.
///
void motor_update(const struct motor *const handle, const uint32_t pwm);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _MOTOR_H */
