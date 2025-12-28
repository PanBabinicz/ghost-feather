#ifndef _TIM_CTRL_COMMON_H
#define _TIM_CTRL_COMMON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The TIM controller result type.
///
/// This enum indicates the outcome of an operation performed on a TIM
/// controller.
///
typedef enum tim_ctrl_res
{
    TIM_CTRL_RES_OK = 0,
    TIM_CTRL_RES_ERR,
} tim_ctrl_res_t;

///
/// \brief The TIM controller status type.
///
/// This enum reflects whether a TIM peripheral is currently initialized or
/// not.
///
typedef enum tim_ctrl_stat
{
    TIM_CTRL_STAT_DEINIT = 0,
    TIM_CTRL_STAT_INIT,
} tim_ctrl_stat_t;

///
/// \brief The TIM controller capture/compare register instance type.
///
/// This enum identifies a specific CCR within a TIM peripheral.
/// Few TIM peripherals support up to 6 capture/compare channels.
///
typedef enum tim_ctrl_inst_ccr
{
    TIM_CTRL_INST_CCR1 = 1,
    TIM_CTRL_INST_CCR2,
    TIM_CTRL_INST_CCR3,
    TIM_CTRL_INST_CCR4,
    TIM_CTRL_INST_CCR5,
    TIM_CTRL_INST_CCR6,
} tim_ctrl_inst_ccr_t;

///
/// \brief The TIM controller capture/compare register data.
///
/// Stores previous and current capture values for a specific CCR.
/// This is useful for calculating differences such as pulse width,
/// period, or duty cycle.
///
struct tim_ctrl_ccr_data
{
    uint32_t prev;
    uint32_t curr;
};

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_COMMON_H */
