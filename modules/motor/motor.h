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
typedef enum motor
{
    MOTOR_BEGIN = 0,
    MOTOR_1     = 0,
    MOTOR_2,
    MOTOR_3,
    MOTOR_4,
    MOTOR_TOTAL,
} motor_t;

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
void motor_upd(const motor_t motor, const uint32_t pwm);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _MOTOR_H */
