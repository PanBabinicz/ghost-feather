#ifndef _MOTOR_CTRL_H
#define _MOTOR_CTRL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The motor controller result type.
///
/// This enum indicates the outcome of an operation performed on a
/// motor controller.
///
typedef enum motor_ctrl_res
{
    MOTOR_CTRL_RES_OK = 0,
    MOTOR_CTRL_RES_ERR,
} motor_ctrl_res_t;

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _MOTOR_CTRL_H */
