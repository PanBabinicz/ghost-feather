#ifndef _MOTOR_H
#define _MOTOR_H

#include <stdint.h>
#include "tim.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
typedef enum motor_inst
{
    MOTOR_INST_BEGIN = 0,
    MOTOR_INST_1     = 0,
    MOTOR_INST_2,
    MOTOR_INST_3,
    MOTOR_INST_4,
    MOTOR_INST_TOTAL,
} motor_inst_t;

///
/// \brief
///
struct motor_dev
{
    struct tim_dev *tim;
    struct ll_tim_ccr_data ccr_data;
    ll_tim_ccr_ch_t ccr_ch;
};

///
/// brief
///
struct motor_dev* motor_dev_arr_get(void);

///
/// brief
///
void motor_init(void);

///
/// brief
///
void motor_upd(const motor_inst_t inst, const uint32_t pwm);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _MOTOR_H */
