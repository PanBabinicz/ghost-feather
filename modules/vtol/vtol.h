#ifndef _VTOL_H
#define _VTOL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The VTOL take-off steps type.
///
typedef enum vtol_take_off_step
{
    VTOL_TAKE_OFF_STEP_0 = 0,
    VTOL_TAKE_OFF_STEP_1,
    VTOL_TAKE_OFF_STEP_2,
    VTOL_TAKE_OFF_STEP_3,
} vtol_take_off_step_t;

///
/// \brief The VTOL land steps type.
///
typedef enum vtol_land_step
{
    VTOL_LAND_STEP_0 = 0,
    VTOL_LAND_STEP_1,
    VTOL_LAND_STEP_2,
    VTOL_LAND_STEP_3,
} vtol_land_step_t;

///
/// \brief The VTOL status type.
///
typedef enum vtol_stat
{
    VTOL_STAT_OFF = 0,
    VTOL_STAT_ON,
} vtol_stat_t;

///
/// \brief Performs VTOL take-off (arming) procedure.
///
/// Executes the VTOL take-off (arming) sequence using RC input signals.
/// The function implements a step-based state machine that monitors
/// roll, pitch, and throttle stick positions to safely transition
/// the VTOL system from OFF to ON state.
///
/// The procedure must be completed in the correct order with the
/// throttle held in a low position. Once all steps are satisfied,
/// the VTOL status is set to active.
///
/// \note This function does not produce output directly and is
///       expected to be called periodically (e.g., in the main loop).
///
/// \warning Incorrect or out-of-order stick movements will prevent
///          successful take-off activation.
///
void vtol_take_off_proc(void);

///
/// \brief Performs VTOL landing (disarming) procedure.
///
/// Executes the VTOL landing (disarming) sequence based on RC input
/// signals. The function implements a step-based state machine that
/// monitors roll, pitch, and throttle stick positions to safely
/// transition the VTOL system from ON to OFF state.
///
/// The landing sequence must be performed in the correct order with
/// the throttle held in a low position. Upon successful completion,
/// the VTOL status is set to inactive.
///
/// \note This function performs no direct output and is intended to
///       be called periodically (e.g., within the main control loop).
///
/// \warning If the stick sequence is interrupted or performed out of
///          order, the landing (disarming) procedure will not complete.
///
void vtol_land_proc(void);

///
/// \brief Gets VTOL status.
///
/// \return vtol_stat_t The VTOL status.
///
vtol_stat_t vtol_stat_get(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _VTOL_H */
