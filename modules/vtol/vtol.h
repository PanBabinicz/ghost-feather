#ifndef _VTOL_H
#define _VTOL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
typedef enum vtol_take_off_step
{
    VTOL_TAKE_OFF_STEP_0 = 0,
    VTOL_TAKE_OFF_STEP_1,
    VTOL_TAKE_OFF_STEP_2,
    VTOL_TAKE_OFF_STEP_3,
} vtol_take_off_step_t;

///
/// \brief
///
typedef enum vtol_land_step
{
    VTOL_LAND_STEP_0 = 0,
    VTOL_LAND_STEP_1,
    VTOL_LAND_STEP_2,
    VTOL_LAND_STEP_3,
} vtol_land_step_t;

///
/// \brief
///
typedef enum vtol_stat
{
    VTOL_STAT_OFF = 0,
    VTOL_STAT_ON,
} vtol_stat_t;

///
/// \brief
///
void vtol_take_off_proc(void);

///
/// \brief
///
void vtol_land_proc(void);

///
/// \brief
///
vtol_stat_t vtol_stat_get(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _VTOL_H */
