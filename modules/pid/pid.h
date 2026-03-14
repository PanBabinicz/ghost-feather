#ifndef _PID_H
#define _PID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef float float32_t;

///
/// \brief The PID controller instance type.
///
typedef enum pid_inst
{
    PID_INST_BEGIN = 0,
    PID_INST_ROLL  = 0,
    PID_INST_PITCH,
    PID_INST_TOTAL,
} pid_inst_t;

///
/// \brief Initializes the PID controller.
///
/// \param[in] inst The PID controller instance.
/// \param[in] kp   The proportional term gain.
/// \param[in] ki   The integral term gain.
/// \param[in] kd   The derivative term gain.
/// \param[in] dt   The time step value.
///
void pid_init(const pid_inst_t inst, const float32_t kp, const float32_t ki, const float32_t kd
        const float32_t dt);

///
/// \brief Deinitializes the PID controller.
///
/// \param[in] inst The PID controller instance.
///
void pid_deinit(const pid_inst_t inst);

///
/// \brief Updates the PID controller control variable.
///
/// \param[in] inst The PID controller instance.
/// \param[in] sp   The setpoint value.
/// \param[in] pv   The process variable value.
///
/// \return float32_t The control variable.
///
float32_t pid_update(const pid_inst_t inst, float32_t sp, float32_t pv);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _PID_H */
