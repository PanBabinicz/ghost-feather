#ifndef _RC_H
#define _RC_H

#include <stdint.h>
#include "tim.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// Used timers inside ghost feather system:
///
/// MOTOR0 -> TIM4_CH4  (PB9)   gp4_16
/// MOTOR1 -> TIM4_CH3  (PB8)   gp4_16
/// MOTOR2 -> TIM4_CH2  (PB7)   gp4_16
/// MOTOR3 -> TIM4_CH1  (PB6)   gp4_16
///
/// RFCH1  -> TIM12_CH1 (PB14)  gp2
/// RFCH2  -> TIM12_CH2 (PB15)  gp2
/// RFCH3  -> TIM8_CH1  (PC6)   adv4
/// RFCH4  -> TIM8_CH2  (PC7)   adv4
/// RFCH5  -> TIM8_CH3  (PC8)   adv4
/// RFCH6  -> TIM8_CH4  (PC9)   adv4
///
///  ----------------------------
/// |                    BAT |*+-|
/// |                    CH6 |s+-|  --> SWB
/// |                    CH5 |s+-|  --> SWA
/// |   FLYSKY FS-R6B    CH4 |s+-|
/// |                    CH3 |s+-|
/// |                    CH2 |s+-|
/// |                    CH1 |s+-|
///  ----------------------------
///

/// TODO
/// \brief
///
typedef enum rc_ch
{
    RC_CH_BEGIN = 0,
    RC_CH_1     = 0,
    RC_CH_2,
    RC_CH_3,
    RC_CH_4,
    RC_CH_5,
    RC_CH_6,
    RC_CH_TOTAL,
} rc_ch_t;

/// TODO
/// \brief
///
struct rc_sig
{
    uint32_t raw;
    uint32_t norm;
};

/// TODO
/// \brief
///
struct rc_dev
{
    struct tim_dev *tim;
    struct ll_tim_ccr_data ccr_data;
    ll_tim_ccr_ch_t ccr_ch;
    struct rc_sig sig;
};

///
/// \brief
///
struct rc_dev* rc_dev_arr_get(void);

///
/// \brief
///
void rc_init(void);

///
/// \brief
///
void rc_sig_raw_gen(rc_ch_t ch);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _RC_H */
