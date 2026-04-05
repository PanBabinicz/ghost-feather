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
/// |   FLYSKY FS-R6B    CH4 |s+-|  --> Yaw
/// |                    CH3 |s+-|  --> Throttle
/// |                    CH2 |s+-|  --> Pitch
/// |                    CH1 |s+-|  --> Roll
///  ----------------------------
///

///
/// \brief The 32-bit floating-ponit type.
///
typedef float float32_t;

///
/// \brief The RC channel identifiers.
///
typedef enum rc_ch
{
    RC_CH_BEGIN = 0,
    RC_CH_1     = 0,    /* Roll     */
    RC_CH_2,            /* Pitch    */
    RC_CH_3,            /* Throttle */
    RC_CH_4,            /* Yaw      */
    RC_CH_5,            /* SWA      */
    RC_CH_6,            /* SWB      */
    RC_CH_TOTAL,
} rc_ch_t;

///
/// \brief The RC channel normalization type.
///
typedef enum rc_norm
{
    RC_NORM_SYM = 0,
    RC_NORM_ASYM,
} rc_norm_t;

///
/// \brief The RC signal components.
///
struct rc_sig
{
    uint32_t raw;
    float32_t norm;
};

///
/// \brief The RC structure.
///
struct rc
{
    struct tim_dev *tim;
    struct ll_tim_ccr_data ccr_data;
    ll_tim_ccr_ch_t ccr_ch;
    struct rc_sig sig;
};

///
/// \brief Initializes the RC channel.
///
/// \param[in] handle The pointer to the RC channel.
/// \param[in] inst   The timer instance.
/// \param[in] ch     The timer capture/compare channel.
///
void rc_init(struct rc *const handle, const tim_inst_t inst, const ll_tim_ccr_ch_t ch);

///
/// \brief Denitializes the RC channel.
///
/// \param[in] handle The pointer to the RC channel.
///
void rc_deinit(struct rc *const handle);

///
/// \brief Gets RC channel.
///
/// \param[in] ch The RC channel.
///
/// \return struct rc* The RC channel pointer.
///
struct rc* rc_get(const rc_ch_t ch);

///
/// \brief Generates PWM pulse width from capture/compare register.
///
/// \param[in] handle The pointer to the RC channel.
///
void rc_sig_raw_gen(struct rc *const handle);

///
/// \brief Normalizes PWM pulse width for a given RC channel.
///
/// \param[in] handle The pointer to the RC channel.
/// \param[in] norm   The normalization type.
///
void rc_sig_norm(struct rc *const handle, const rc_norm_t norm);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _RC_H */
