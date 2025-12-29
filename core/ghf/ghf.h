#ifndef _GHF_H
#define _GHF_H

#include <stdint.h>
#include <stdbool.h>
#include "rf_ctrl.h"
#include "tim_ctrl.h"

///
/// \brief Result codes for ghost feather firmware operations.
///
/// This enumeration defines the possible outcomes of operations
/// performed by the ghost feather firmware.
///
typedef enum ghf_res
{
    GHF_RES_OK = 0,
    GHF_RES_ERR,
} ghf_res_t;

///
/// \brief
///
typedef enum ghf_stat
{
    GHF_STAT_OFF = 0,
    GHF_STAT_ON,
} ghf_stat_t;

///
/// \brief
///
typedef enum ghf_launch_step
{
    GHF_LAUNCH_STEP_1 = 0,
    GHF_LAUNCH_STEP_2,
    GHF_LAUNCH_STEP_3,
    GHF_LAUNCH_STEP_4,
} ghf_launch_step_t;

///
/// \brief
///
typedef enum ghf_land_step
{
    GHF_LAND_STEP_1 = 0,
    GHF_LAND_STEP_2,
    GHF_LAND_STEP_3,
    GHF_LAND_STEP_4,
} ghf_land_step_t;

///
/// \brief
///
struct ghf_throttle
{
    struct tim_ctrl_ccr_data ccr_data;
    uint32_t sig_raw;
    uint32_t sig_norm;
};

///
/// \brief
///
struct ghf_yaw
{
    struct tim_ctrl_ccr_data ccr_data;
    uint32_t sig_raw;
    uint32_t sig_norm;
};

///
/// \brief
///
struct ghf_pitch
{
    struct tim_ctrl_ccr_data ccr_data;
    uint32_t sig_raw;
    uint32_t sig_norm;
};

///
/// \brief
///
struct ghf_roll
{
    struct tim_ctrl_ccr_data ccr_data;
    uint32_t sig_raw;
    uint32_t sig_norm;
};

///
/// \brief
///
struct ghf_ctrl
{
    struct ghf_throttle throttle;
    struct ghf_yaw yaw;
    struct ghf_pitch pitch;
    struct ghf_roll roll;
};

///
/// \brief
///
struct ghf_sys
{
    struct rf_ctrl_dev *rf[RF_CTRL_CH_TOTAL];
};

///
/// \brief
///
struct ghf_dev
{
    struct ghf_ctrl ctrl;
    struct ghf_sys sys;
    ghf_launch_step_t launch_step;
    ghf_land_step_t land_step;
    ghf_stat_t stat;
};

///
/// \brief
///
ghf_res_t ghf_dev_init(struct ghf_dev *const ghf);

///
/// \brief
///
ghf_res_t ghf_launch_proc(struct ghf_dev *const ghf);

///
/// \brief
///
ghf_res_t ghf_land_proc(struct ghf_dev *const ghf);

///
/// \brief SysTick delay execution for a specified number of milliseconds.
///
/// \param[in] ms The number of milliseconds.
///
void ghfc_systick_delay_ms(const uint32_t ms);

#endif  /* _GHF_H */
