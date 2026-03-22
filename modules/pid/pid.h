#ifndef _PID_H
#define _PID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef float float32_t;

///
/// \brief Initializes the PID controller.
///
/// \param[in] handle The pointer to PID controller.
/// \param[in] kp     The proportional term gain.
/// \param[in] ki     The integral term gain.
/// \param[in] kd     The derivative term gain.
/// \param[in] dt     The time step value.
///
void pid_init(struct pid *const handle, const float32_t kp, const float32_t ki, const float32_t kd,
        const float32_t dt);

///
/// \brief Deinitializes the PID controller.
///
/// \param[in] handle The pointer to PID controller.
///
void pid_deinit(struct pid *const handle);

///
/// \brief Updates the PID controller control variable.
///
/// \param[in] handle The pointer to PID controller.
/// \param[in] sp     The setpoint value.
/// \param[in] pv     The process variable value.
///
/// \return float32_t The control variable.
///
float32_t pid_update(struct pid *const handle, float32_t sp, float32_t pv);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _PID_H */
