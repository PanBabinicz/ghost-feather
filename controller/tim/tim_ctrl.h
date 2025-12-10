#ifndef _TIM_CTRL_H
#define _TIM_CTRL_H

#include <stdint.h>
#include "tim_ctrl_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
typedef enum tim_ctrl_inst
{
    TIM_CTRL_INST_BEGIN = 0,
    TIM_CTRL_INST_TIM4  = 0,
    TIM_CTRL_INST_TIM12,
    TIM_CTRL_INST_TIM8,
    TIM_CTRL_INST_TOTAL,
} tim_ctrl_inst_t;

///
/// \brief
///
struct tim_ctrl_dev
{
    void *tim;
    tim_ctrl_res_t (*init)(void *tim);
    tim_ctrl_res_t (*deinit)(void *tim);
    tim_ctrl_res_t (*enable)(void *tim);
    tim_ctrl_res_t (*disable)(void *tim);
};

///
/// \brief
///
struct tim_ctrl_dev* tim_ctrl_dev_get(tim_ctrl_inst_t inst);

///
/// \brief
///
void tim_ctrl_init(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_H */
