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
/// \brief
///
void pid_init(const pid_inst_t inst, const float32_t kp, const float32_t ki, const float32_t kd);

///
/// \brief
///
void pid_deinit(const pid_inst_t inst);

///
/// \brief
///
float32_t pid_update(const pid_inst_t inst, float32_t err);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _PID_H */
