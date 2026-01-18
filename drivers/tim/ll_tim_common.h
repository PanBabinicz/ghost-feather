#ifndef _LL_TIM_COMMON_H
#define _LL_TIM_COMMON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The TIM result type.
///
typedef enum ll_tim_res
{
    LL_TIM_RES_OK = 0,
    LL_TIM_RES_ERR,
} ll_tim_res_t;

///
/// \brief The TIM status type.
///
/// This enum reflects whether a TIM peripheral is currently initialized or
/// not.
///
typedef enum ll_tim_stat
{
    LL_TIM_STAT_DEINIT = 0,
    LL_TIM_STAT_INIT,
} ll_tim_stat_t;

///
/// \brief The TIM capture/compare register instance type.
///
/// This enum identifies a specific CCR within a TIM peripheral.
/// Few TIM peripherals support up to 6 capture/compare channels.
///
typedef enum ll_tim_ccr_ch
{
    LL_TIM_CCR_CH1 = 0,
    LL_TIM_CCR_CH2,
    LL_TIM_CCR_CH3,
    LL_TIM_CCR_CH4,
    LL_TIM_CCR_CH5,
    LL_TIM_CCR_CH6,
} ll_tim_ccr_ch_t;

///
/// \brief The TIM capture/compare register data.
///
/// Stores previous and current capture values for a specific CCR.
/// This is useful for calculating differences such as pulse width,
/// period, or duty cycle.
///
struct ll_tim_ccr_data
{
    uint32_t prev;
    uint32_t curr;
};

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_TIM_COMMON_H */
