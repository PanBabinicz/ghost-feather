#ifndef _TIM_H
#define _TIM_H

#include <stdint.h>
#include "ll_tim_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/// TODO
/// \brief
///
typedef enum tim_res
{
    TIM_RES_OK = 0,
    TIM_RES_ERR,
} tim_res_t;

/// TODO
/// \brief
///
typedef enum tim_inst
{
    TIM_INST_BEGIN = 0,
    TIM_INST_4     = 0,
    TIM_INST_12,
    TIM_INST_8,
    TIM_INST_TOTAL,
} tim_inst_t;

/// TODO
/// \brief
///
struct tim_dev
{
    void *tim;
    ll_tim_res_t (*init)(void *tim);
    ll_tim_res_t (*deinit)(void *tim);
    ll_tim_res_t (*enable)(void *tim);
    ll_tim_res_t (*disable)(void *tim);
    ll_tim_res_t (*ccr_data_get)(void *tim, const ll_tim_ccr_ch_t ch, struct ll_tim_ccr_data *const ccr);
    ll_tim_res_t (*ccr_set)(void *tim, const ll_tim_ccr_ch_t ch, const uint32_t ccr);
};

///
/// \brief
///
struct tim_dev* tim_dev_get(tim_inst_t inst);

///
/// \brief
///
struct tim_dev* tim_dev_arr_get(void);

///
/// \brief
///
void tim_init(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_H */
