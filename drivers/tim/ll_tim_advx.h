#ifndef _LL_TIM_ADVX_H
#define _LL_TIM_ADVX_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ll_tim_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief Identifier for advanced timers TIM1 and TIM8.
///
/// This enum selects which general-purpose timer instance is being referenced.
///
typedef enum ll_tim_adv6_tim18_id
{
    LL_TIM_ADV6_TIM18_ID_1 = 0,
    LL_TIM_ADV6_TIM18_ID_8,
} ll_tim_adv6_tim18_id_t;

///
/// \brief Operating mode for advanced timers TIM8 and TIM8.
///
/// Specifies whether the timer is configured for input capture or
/// output compare functionality.
///
typedef enum ll_tim_adv6_tim18_mode
{
    LL_TIM_ADV6_TIM18_MODE_IN_CAP = 0,
    LL_TIM_ADV6_TIM18_MODE_OUT_COMP,
} ll_tim_adv6_tim18_mode_t;

///
/// \brief Control Register 1 (CR1) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_cr1
{
    uint32_t r;
    struct
    {
        uint32_t cen      : 1;
        uint32_t udis     : 1;
        uint32_t urs      : 1;
        uint32_t opm      : 1;
        uint32_t dir      : 1;
        uint32_t cms      : 2;
        uint32_t arpe     : 1;
        uint32_t ckd      : 2;
        uint32_t          : 1;
        uint32_t uifremap : 1;
        uint32_t          : 20;
    } bf;
};

///
/// \brief Control Register 2 (CR2) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_cr2
{
    uint32_t r;
    struct
    {
        uint32_t ccpc  : 1;
        uint32_t       : 1;
        uint32_t ccus  : 1;
        uint32_t ccds  : 1;
        uint32_t       : 1;
        uint32_t mms   : 3;
        uint32_t ti1s  : 1;
        uint32_t ois1  : 1;
        uint32_t ois1n : 1;
        uint32_t ois2  : 1;
        uint32_t ois2n : 1;
        uint32_t ois3  : 1;
        uint32_t ois3n : 1;
        uint32_t ois4  : 1;
        uint32_t       : 1;
        uint32_t ois5  : 1;
        uint32_t       : 1;
        uint32_t ois6  : 1;
        uint32_t       : 1;
        uint32_t mms2  : 4;
        uint32_t       : 7;
    } bf;
};

///
/// \brief Slave Mode Control Register (SMCR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_smcr
{
    uint32_t r;
    struct
    {
        uint32_t sms     : 3;
        uint32_t         : 1;
        uint32_t ts      : 3;
        uint32_t msm     : 1;
        uint32_t etf     : 4;
        uint32_t etps    : 2;
        uint32_t ece     : 1;
        uint32_t etp     : 1;
        uint32_t sms_msb : 1;
        uint32_t         : 15;
    } bf;
};

///
/// \brief DMA/Interrupt Enable Register (DIER) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_dier
{
    uint32_t r;
    struct
    {
        uint32_t uie   : 1;
        uint32_t cc1ie : 1;
        uint32_t cc2ie : 1;
        uint32_t cc3ie : 1;
        uint32_t cc4ie : 1;
        uint32_t comie : 1;
        uint32_t tie   : 1;
        uint32_t bie   : 1;
        uint32_t ude   : 1;
        uint32_t cc1de : 1;
        uint32_t cc2de : 1;
        uint32_t cc3de : 1;
        uint32_t cc4de : 1;
        uint32_t comde : 1;
        uint32_t tde   : 1;
        uint32_t       : 17;
    } bf;
};

///
/// \brief Status Register (SR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_sr
{
    uint32_t r;
    struct
    {
        uint32_t uif   : 1;
        uint32_t cc1if : 1;
        uint32_t cc2if : 1;
        uint32_t cc3if : 1;
        uint32_t cc4if : 1;
        uint32_t comif : 1;
        uint32_t tif   : 1;
        uint32_t bif   : 1;
        uint32_t b2if  : 1;
        uint32_t cc1of : 1;
        uint32_t cc2of : 1;
        uint32_t cc3of : 1;
        uint32_t cc4of : 1;
        uint32_t       : 3;
        uint32_t cc5if : 1;
        uint32_t cc6if : 1;
        uint32_t       : 14;
    } bf;
};

///
/// \brief Event Generation Register (EGR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_egr
{
    uint32_t r;
    struct
    {
        uint32_t ug   : 1;
        uint32_t cc1g : 1;
        uint32_t cc2g : 1;
        uint32_t cc3g : 1;
        uint32_t cc4g : 1;
        uint32_t comg : 1;
        uint32_t tg   : 1;
        uint32_t bg   : 1;
        uint32_t b2g  : 1;
        uint32_t      : 23;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 1 Input Mode (CCMR1) for advanced
///        timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccmr1_in
{
    uint32_t r;
    struct
    {
        uint32_t cc1s   : 2;
        uint32_t ic1psc : 2;
        uint32_t ic1f   : 4;
        uint32_t cc2s   : 2;
        uint32_t ic2psc : 2;
        uint32_t ic2f   : 4;
        uint32_t        : 16;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 1 Output Mode (CCMR1) for advanced
///        timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccmr1_out
{
    uint32_t r;
    struct
    {
        uint32_t cc1s     : 2;
        uint32_t oc1fe    : 1;
        uint32_t oc1pe    : 1;
        uint32_t oc1m     : 3;
        uint32_t oc1ce    : 1;
        uint32_t cc2s     : 2;
        uint32_t oc2fe    : 1;
        uint32_t oc2pe    : 1;
        uint32_t oc2m     : 3;
        uint32_t oc2ce    : 1;
        uint32_t oc1m_msb : 1;
        uint32_t          : 7;
        uint32_t oc2m_msb : 1;
        uint32_t          : 7;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 2 Input Mode (CCMR2) for advanced
///        timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccmr2_in
{
    uint32_t r;
    struct
    {
        uint32_t cc3s   : 2;
        uint32_t ic3psc : 2;
        uint32_t ic3f   : 4;
        uint32_t cc4s   : 2;
        uint32_t ic4psc : 2;
        uint32_t ic4f   : 4;
        uint32_t        : 16;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 2 Output Mode (CCMR2) for advanced
///        timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccmr2_out
{
    uint32_t r;
    struct
    {
        uint32_t cc3s     : 2;
        uint32_t oc3fe    : 1;
        uint32_t oc3pe    : 1;
        uint32_t oc3m     : 3;
        uint32_t oc3ce    : 1;
        uint32_t cc4s     : 2;
        uint32_t oc4fe    : 1;
        uint32_t oc4pe    : 1;
        uint32_t oc4m     : 3;
        uint32_t oc4ce    : 1;
        uint32_t oc3m_msb : 1;
        uint32_t          : 7;
        uint32_t oc4m_msb : 1;
        uint32_t          : 7;
    } bf;
};

///
/// \brief Capture/Compare Enable Register (CCER) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccer
{
    uint32_t r;
    struct
    {
        uint32_t cc1e  : 1;
        uint32_t cc1p  : 1;
        uint32_t cc1ne : 1;
        uint32_t cc1np : 1;
        uint32_t cc2e  : 1;
        uint32_t cc2p  : 1;
        uint32_t cc2ne : 1;
        uint32_t cc2np : 1;
        uint32_t cc3e  : 1;
        uint32_t cc3p  : 1;
        uint32_t cc3ne : 1;
        uint32_t cc3np : 1;
        uint32_t cc4e  : 1;
        uint32_t cc4p  : 1;
        uint32_t       : 1;
        uint32_t cc4np : 1;
        uint32_t cc5e  : 1;
        uint32_t cc5p  : 1;
        uint32_t       : 2;
        uint32_t cc6e  : 1;
        uint32_t cc6p  : 1;
        uint32_t       : 10;
    } bf;
};

///
/// \brief Counter Register (CNT) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_cnt
{
    uint32_t r;
    struct
    {
        uint32_t cnt    : 16;
        uint32_t        : 15;
        uint32_t uifcpy : 1;
    } bf;
};

///
/// \brief Prescaler Register (PSC) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_psc
{
    uint32_t r;
    struct
    {
        uint32_t psc : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Auto-Reload Register (ARR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_arr
{
    uint32_t r;
    struct
    {
        uint32_t arr : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Repetition Counter Register (RCR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_rcr
{
    uint32_t r;
    struct
    {
        uint32_t rep : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 1 (CCR1) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccr1
{
    uint32_t r;
    struct
    {
        uint32_t ccr1 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 2 (CCR2) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccr2
{
    uint32_t r;
    struct
    {
        uint32_t ccr2 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 3 (CCR3) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccr3
{
    uint32_t r;
    struct
    {
        uint32_t ccr3 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 4 (CCR4) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccr4
{
    uint32_t r;
    struct
    {
        uint32_t ccr4 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Break And Dead-Time Register (BDTR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_bdtr
{
    uint32_t r;
    struct
    {
        uint32_t dtg  : 8;
        uint32_t lock : 2;
        uint32_t ossi : 1;
        uint32_t ossr : 1;
        uint32_t bke  : 1;
        uint32_t bkp  : 1;
        uint32_t aoe  : 1;
        uint32_t moe  : 1;
        uint32_t bkf  : 4;
        uint32_t bk2f : 4;
        uint32_t bk2e : 1;
        uint32_t bk2p : 1;
        uint32_t      : 6;
    } bf;
};

///
/// \brief DMA Control Register (DCR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_dcr
{
    uint32_t r;
    struct
    {
        uint32_t dba : 5;
        uint32_t     : 3;
        uint32_t dbl : 5;
        uint32_t     : 19;
    } bf;
};

///
/// \brief DMA Address For Full Transfer Register (DMAR) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_dmar
{
    uint32_t r;
    struct
    {
        uint32_t dmab : 32;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 3 (CCMR3) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccmr3
{
    uint32_t r;
    struct
    {
        uint32_t          : 2;
        uint32_t oc5fe    : 1;
        uint32_t oc5pe    : 1;
        uint32_t oc5m     : 3;
        uint32_t oc5ce    : 1;
        uint32_t          : 2;
        uint32_t oc6fe    : 1;
        uint32_t oc6pe    : 1;
        uint32_t oc6m     : 3;
        uint32_t oc6ce    : 1;
        uint32_t oc5m_msb : 1;
        uint32_t          : 7;
        uint32_t oc6m_msb : 1;
        uint32_t          : 7;
    } bf;
};

///
/// \brief Capture/Compare Register 5 (CCR5) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccr5
{
    uint32_t r;
    struct
    {
        uint32_t ccr5  : 16;
        uint32_t       : 13;
        uint32_t gc5c1 : 1;
        uint32_t gc5c2 : 1;
        uint32_t gc5c3 : 1;
    } bf;
};

///
/// \brief Capture/Compare Register 6 (CCR6) for advanced timers TIM1 and TIM8.
///
union ll_tim_adv6_tim18_ccr6
{
    uint32_t r;
    struct
    {
        uint32_t ccr6 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Register map for advanced timers TIM1 and TIM8.
///
/// This structure represents the memory-mapped register layout of the
/// advanced timers TIM1 and TIM8. The register order and reserved
/// fields are aligned with the device reference manual to allow
/// direct access via a peripheral base address.
///
struct ll_tim_adv6_tim18_regs
{
    union ll_tim_adv6_tim18_cr1  cr1;
    union ll_tim_adv6_tim18_cr2  cr2;
    union ll_tim_adv6_tim18_smcr smcr;
    union ll_tim_adv6_tim18_dier dier;
    union ll_tim_adv6_tim18_sr   sr;
    union ll_tim_adv6_tim18_egr  egr;
    union
    {
        union ll_tim_adv6_tim18_ccmr1_in  in;
        union ll_tim_adv6_tim18_ccmr1_out out;

    } ccmr1;
    union
    {
        union ll_tim_adv6_tim18_ccmr2_in  in;
        union ll_tim_adv6_tim18_ccmr2_out out;

    } ccmr2;
    union ll_tim_adv6_tim18_ccer  ccer;
    union ll_tim_adv6_tim18_cnt   cnt;
    union ll_tim_adv6_tim18_psc   psc;
    union ll_tim_adv6_tim18_arr   arr;
    union ll_tim_adv6_tim18_rcr   rcr;
    union ll_tim_adv6_tim18_ccr1  ccr1;
    union ll_tim_adv6_tim18_ccr2  ccr2;
    union ll_tim_adv6_tim18_ccr3  ccr3;
    union ll_tim_adv6_tim18_ccr4  ccr4;
    union ll_tim_adv6_tim18_bdtr  bdtr;
    union ll_tim_adv6_tim18_dcr   dcr;
    union ll_tim_adv6_tim18_dmar  dmar;
    uint32_t res0[1];
    union ll_tim_adv6_tim18_ccmr3 ccmr3;
    union ll_tim_adv6_tim18_ccr5  ccr5;
    union ll_tim_adv6_tim18_ccr6  ccr6;
};

///
/// \brief Runtime device context for advanced timers TIM1 and TIM8.
///
/// This structure holds all runtime state required to control a TIM1 and TIM8
/// instance. It includes a pointer to the memory-mapped registers, a temporary
/// shadow copy for safe modification, capture/compare history, configuration
/// modes, and initialization status.
///
struct ll_tim_adv6_tim18_dev
{
    volatile struct ll_tim_adv6_tim18_regs *rmap;
    struct ll_tim_adv6_tim18_regs rtmp;
    struct ll_tim_ccr_data ccr_data[6];
    ll_tim_adv6_tim18_id_t id;
    ll_tim_adv6_tim18_mode_t ccmr1_mode;
    ll_tim_adv6_tim18_mode_t ccmr2_mode;
    ll_tim_stat_t stat;
};

///
/// \brief Initializes the advanced timer (TIM1 and TIM8).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_adv6_tim18_init(void *tim);

///
/// \brief Deinitializes the advanced timer (TIM1 and TIM8).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_adv6_tim18_deinit(void *tim);

///
/// \brief Enables the advanced timer (TIM1 and TIM8).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_adv6_tim18_enable(void *tim);

///
/// \brief Disables the advanced timer (TIM1 and TIM8).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_adv6_tim18_disable(void *tim);

///
/// \brief Gets capture/compare register data (TIM1 and TIM8).
///
/// \param[in]  tim The pointer to timer device.
/// \param[in]  ch  The capture/compare channel.
/// \param[out] ccr The capture/compare data.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_adv6_tim18_ccr_data_get(void *tim, const ll_tim_ccr_ch_t ch,
        struct ll_tim_ccr_data *const ccr);

///
/// \brief Sets capture/compare register value (TIM1 and TIM8).
///
/// \param[in  tim The pointer to timer device.
/// \param[in  ch  The capture/compare channel.
/// \param[in] ccr The capture/compare data.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_adv6_tim18_ccr_set(void *tim, const ll_tim_ccr_ch_t ch, const uint32_t ccr);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_TIM_ADVX_H */
