#ifndef _PID_CTRL_H
#define _PID_CTRL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The PID controller result type.
///
/// This enum indicates the outcome of an operation performed on a PID
/// controller.
///
typedef enum pid_ctrl_res
{
    PID_CTRL_RES_OK = 0,
    PID_CTRL_RES_ERR,
} pid_ctrl_res_t;

///
/// \brief PID controller instance identifiers.
///
/// This enumeration defines the available PID controller instances
/// managed by the PID control layer.
///
typedef enum pid_ctrl_inst
{
    PID_CTRL_INST_BEGIN = 0,
    PID_CTRL_INST_HORIZ = 0,
    PID_CTRL_INST_TOTAL,
} tim_ctrl_inst_t;

///
/// \brief Initializes the PID devices.
///
/// This function should be called during system initialization.
///
pid_ctrl_res_t pid_ctrl_init(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _PID_CTRL_H */

