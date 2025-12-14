#ifndef _TIM_CTRL_GPX_H
#define _TIM_CTRL_GPX_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "tim_ctrl_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief Output Compare (OC) modes for TIM2, TIM3, TIM4, and TIM5.
///
/// This enum defines the available output compare operating modes supported
/// by general-purpose timers TIM2–TIM5. These modes control how the timer
/// output behaves when a compare match occurs, including frozen output,
/// toggling, PWM generation, and one-pulse operation.
///
typedef enum tim_ctrl_gpx_tim2345_oc_mode
{
    TIM_CTRL_GPX_TIM2345_OC_MODE_FRZ = 0,
    TIM_CTRL_GPX_TIM2345_OC_MODE_ACT,
    TIM_CTRL_GPX_TIM2345_OC_MODE_INACT,
    TIM_CTRL_GPX_TIM2345_OC_MODE_TOG,
    TIM_CTRL_GPX_TIM2345_OC_MODE_FINACT,
    TIM_CTRL_GPX_TIM2345_OC_MODE_FACT,
    TIM_CTRL_GPX_TIM2345_OC_MODE_PWM1,
    TIM_CTRL_GPX_TIM2345_OC_MODE_PWM2,
    TIM_CTRL_GPX_TIM2345_OC_MODE_OPM1,
    TIM_CTRL_GPX_TIM2345_OC_MODE_OPM2,
    TIM_CTRL_GPX_TIM2345_OC_MODE_CPWM1 = 12,
    TIM_CTRL_GPX_TIM2345_OC_MODE_CPWM2,
    TIM_CTRL_GPX_TIM2345_OC_MODE_APWM1,
    TIM_CTRL_GPX_TIM2345_OC_MODE_APWM2,
} tim_ctrl_gpx_tim2345_oc_mode_t;

///
/// \brief Identifier for general-purpose timers TIM2–TIM5.
///
/// This enum selects which general-purpose timer instance is being referenced.
///
typedef enum tim_ctrl_gpx_tim2345_id
{
    TIM_CTRL_GPX_TIM2345_ID_2 = 0,
    TIM_CTRL_GPX_TIM2345_ID_3,
    TIM_CTRL_GPX_TIM2345_ID_4,
    TIM_CTRL_GPX_TIM2345_ID_5,
} tim_ctrl_gpx_tim2345_id_t;

///
/// \brief Operating mode for general-purpose timers TIM2–TIM5.
///
/// Specifies whether the timer is configured for input capture or
/// output compare functionality.
///
typedef enum tim_ctrl_gpx_tim2345_mode
{
    TIM_CTRL_GPX_TIM2345_MODE_IN_CAP = 0,
    TIM_CTRL_GPX_TIM2345_MODE_OUT_COMP,
} tim_ctrl_gpx_tim2345_mode_t;

///
/// \brief Identifier for general-purpose timers TIM9 and TIM12.
///
/// This enum selects which general-purpose timer instance is being referenced.
///
typedef enum tim_ctrl_gpx_tim912_id
{
    TIM_CTRL_GPX_TIM912_ID_9 = 0,
    TIM_CTRL_GPX_TIM912_ID_12,
} tim_ctrl_gpx_tim912_id_t;

///
/// \brief Operating mode for general-purpose timers TIM9 and TIM12.
///
/// Specifies whether the timer is configured for input capture or
/// output compare functionality.
///
typedef enum tim_ctrl_gpx_tim912_mode
{
    TIM_CTRL_GPX_TIM912_MODE_IN_CAP = 0,
    TIM_CTRL_GPX_TIM912_MODE_OUT_COMP,
} tim_ctrl_gpx_tim912_mode_t;

///
/// \brief Identifier for general-purpose timers TIM10-TIM14.
///
/// This enum selects which general-purpose timer instance is being referenced.
///
typedef enum tim_ctrl_gpx_tim10111314_id
{
    TIM_CTRL_GPX_TIM10111314_ID_10 = 0,
    TIM_CTRL_GPX_TIM10111314_ID_11,
    TIM_CTRL_GPX_TIM10111314_ID_13,
    TIM_CTRL_GPX_TIM10111314_ID_14,
} tim_ctrl_gpx_tim10111314_id_t;

///
/// \brief Operating mode for general-purpose timers TIM10-TIM14.
///
/// Specifies whether the timer is configured for input capture or
/// output compare functionality.
///
typedef enum tim_ctrl_gpx_tim10111314_mode
{
    TIM_CTRL_GPX_TIM10111314_MODE_IN_CAP = 0,
    TIM_CTRL_GPX_TIM10111314_MODE_OUT_COMP,
} tim_ctrl_gpx_tim10111314_mode_t;

///
/// \brief Control Register 1 (CR1) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_cr1
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
/// \brief Control Register 2 (CR2) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_cr2
{
    uint32_t r;
    struct
    {
        uint32_t      : 3;
        uint32_t ccds : 1;
        uint32_t mms  : 3;
        uint32_t ti1s : 1;
        uint32_t      : 24;
    } bf;
};

///
/// \brief Slave Mode Control Register (SMCR) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_smcr
{
    uint32_t r;
    struct
    {
        uint32_t sms     : 3;
        uint32_t occs    : 1;
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
/// \brief DMA/Interrupt Enable Register (DIER) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_dier
{
    uint32_t r;
    struct
    {
        uint32_t uie   : 1;
        uint32_t cc1ie : 1;
        uint32_t cc2ie : 1;
        uint32_t cc3ie : 1;
        uint32_t cc4ie : 1;
        uint32_t       : 1;
        uint32_t tie   : 1;
        uint32_t       : 1;
        uint32_t ude   : 1;
        uint32_t cc1de : 1;
        uint32_t cc2de : 1;
        uint32_t cc3de : 1;
        uint32_t cc4de : 1;
        uint32_t       : 1;
        uint32_t tde   : 1;
        uint32_t       : 17;
    } bf;
};

///
/// \brief Status Register (SR) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_sr
{
    uint32_t r;
    struct
    {
        uint32_t uif   : 1;
        uint32_t cc1if : 1;
        uint32_t cc2if : 1;
        uint32_t cc3if : 1;
        uint32_t cc4if : 1;
        uint32_t       : 1;
        uint32_t tif   : 1;
        uint32_t       : 2;
        uint32_t cc1of : 1;
        uint32_t cc2of : 1;
        uint32_t cc3of : 1;
        uint32_t cc4of : 1;
        uint32_t       : 19;
    } bf;
};

///
/// \brief Event Generation Register (EGR) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_egr
{
    uint32_t r;
    struct
    {
        uint32_t ug   : 1;
        uint32_t cc1g : 1;
        uint32_t cc2g : 1;
        uint32_t cc3g : 1;
        uint32_t cc4g : 1;
        uint32_t      : 1;
        uint32_t tg   : 1;
        uint32_t      : 25;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 1 Input Mode (CCMR1) for general-purpose
///        timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_ccmr1_in
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
/// \brief Capture/Compare Mode Register 1 Output Mode (CCMR1) for general-purpose
///        timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_ccmr1_out
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
/// \brief Capture/Compare Mode Register 2 Input Mode (CCMR2) for general-purpose
///        timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_ccmr2_in
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
/// \brief Capture/Compare Mode Register 2 Output Mode (CCMR2) for general-purpose
///        timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_ccmr2_out
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
/// \brief Capture/Compare Enable Register (CCER) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_ccer
{
    uint32_t r;
    struct
    {
        uint32_t cc1e  : 1;
        uint32_t cc1p  : 1;
        uint32_t       : 1;
        uint32_t cc1np : 1;
        uint32_t cc2e  : 1;
        uint32_t cc2p  : 1;
        uint32_t       : 1;
        uint32_t cc2np : 1;
        uint32_t cc3e  : 1;
        uint32_t cc3p  : 1;
        uint32_t       : 1;
        uint32_t cc3np : 1;
        uint32_t cc4e  : 1;
        uint32_t cc4p  : 1;
        uint32_t       : 1;
        uint32_t cc4np : 1;
        uint32_t       : 16;
    } bf;
};

///
/// \brief Counter Register (CNT) for general-purpose timers TIM2–TIM5.
///
/// \note  TIM2 and TIM5 have 32bit counter. Use 'r' to get/modify content of the counter.
///
union tim_ctrl_gpx_tim2345_cnt
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
/// \brief Prescaler Register (PSC) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_psc
{
    uint32_t r;
    struct
    {
        uint32_t psc : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Auto-Reload Register (ARR) for general-purpose timers TIM2–TIM5.
///
/// \note  TIM2 and TIM5 have 32bit auto reload register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_arr
{
    uint32_t r;
    struct
    {
        uint32_t arr : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 1 (CCR1) for general-purpose timers TIM2–TIM5.
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr1
{
    uint32_t r;
    struct
    {
        uint32_t ccr1 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 2 (CCR2) for general-purpose timers TIM2–TIM5.
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr2
{
    uint32_t r;
    struct
    {
        uint32_t ccr2 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 3 (CCR3) for general-purpose timers TIM2–TIM5.
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr3
{
    uint32_t r;
    struct
    {
        uint32_t ccr3 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 4 (CCR4) for general-purpose timers TIM2–TIM5.
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr4
{
    uint32_t r;
    struct
    {
        uint32_t ccr4 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief DMA Control Register (DCR) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_dcr
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
/// \brief DMA Address For Full Transfer Register (DMAR) for general-purpose timers TIM2–TIM5.
///
union tim_ctrl_gpx_tim2345_dmar
{
    uint32_t r;
    struct
    {
        uint32_t dmab : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief TIM2 Option Register (TIM2_OR).
///
union tim_ctrl_gpx_tim2_or
{
    uint32_t r;
    struct
    {
        uint32_t          : 10;
        uint32_t itr1_rmp : 2;
        uint32_t          : 20;
    } bf;
};

///
/// \brief TIM5 Option Register (TIM5_OR).
///
union tim_ctrl_gpx_tim5_or
{
    uint32_t r;
    struct
    {
        uint32_t         : 6;
        uint32_t ti4_rmp : 2;
        uint32_t         : 24;
    } bf;
};

///
/// \brief Control Register 1 (CR1) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_cr1
{
    uint32_t r;
    struct
    {
        uint32_t cen      : 1;
        uint32_t udis     : 1;
        uint32_t urs      : 1;
        uint32_t opm      : 1;
        uint32_t          : 3;
        uint32_t arpe     : 1;
        uint32_t ckd      : 2;
        uint32_t          : 1;
        uint32_t uifremap : 1;
        uint32_t          : 20;
    } bf;
};

///
/// \brief Slave Mode Control Register (SMCR) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_smcr
{
    uint32_t r;
    struct
    {
        uint32_t sms     : 3;
        uint32_t         : 1;
        uint32_t ts      : 3;
        uint32_t msm     : 1;
        uint32_t         : 8;
        uint32_t sms_msb : 1;
        uint32_t         : 15;
    } bf;
};

///
/// \brief Interrupt Enable Register (DIER) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_dier
{
    uint32_t r;
    struct
    {
        uint32_t uie   : 1;
        uint32_t cc1ie : 1;
        uint32_t cc2ie : 1;
        uint32_t       : 3;
        uint32_t tie   : 1;
        uint32_t       : 25;
    } bf;
};

///
/// \brief Status Register (SR) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_sr
{
    uint32_t r;
    struct
    {
        uint32_t uif   : 1;
        uint32_t cc1if : 1;
        uint32_t cc2if : 1;
        uint32_t       : 3;
        uint32_t tif   : 1;
        uint32_t       : 2;
        uint32_t cc1of : 1;
        uint32_t cc2of : 1;
        uint32_t       : 21;
    } bf;
};

///
/// \brief Event Generation Register (EGR) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_egr
{
    uint32_t r;
    struct
    {
        uint32_t ug   : 1;
        uint32_t cc1g : 1;
        uint32_t cc2g : 1;
        uint32_t      : 3;
        uint32_t tg   : 1;
        uint32_t      : 25;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 1 Input Mode (CCMR1) for general-purpose
///        timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_ccmr1_in
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
/// \brief Capture/Compare Mode Register 1 Output Mode (CCMR1) for general-purpose
///        timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_ccmr1_out
{
    uint32_t r;
    struct
    {
        uint32_t cc1s     : 2;
        uint32_t oc1fe    : 1;
        uint32_t oc1pe    : 1;
        uint32_t oc1m     : 3;
        uint32_t          : 1;
        uint32_t cc2s     : 2;
        uint32_t oc2fe    : 1;
        uint32_t oc2pe    : 1;
        uint32_t oc2m     : 3;
        uint32_t          : 1;
        uint32_t oc1m_msb : 1;
        uint32_t          : 7;
        uint32_t oc2m_msb : 1;
        uint32_t          : 7;
    } bf;
};

///
/// \brief Capture/Compare Enable Register (CCER) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_ccer
{
    uint32_t r;
    struct
    {
        uint32_t cc1e  : 1;
        uint32_t cc1p  : 1;
        uint32_t       : 1;
        uint32_t cc1np : 1;
        uint32_t cc2e  : 1;
        uint32_t cc2p  : 1;
        uint32_t       : 1;
        uint32_t cc2np : 1;
        uint32_t       : 24;
    } bf;
};

///
/// \brief Counter Register (CNT) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_cnt
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
/// \brief Prescaler Register (CNT) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_psc
{
    uint32_t r;
    struct
    {
        uint32_t psc : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Auto-Reload Register (ARR) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_arr
{
    uint32_t r;
    struct
    {
        uint32_t arr : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 1 (CCR1) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_ccr1
{
    uint32_t r;
    struct
    {
        uint32_t ccr1 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Capture/Compare Register 2 (CCR2) for general-purpose timers TIM9 and TIM12.
///
union tim_ctrl_gpx_tim912_ccr2
{
    uint32_t r;
    struct
    {
        uint32_t ccr2 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief Control Register 1 (CR1) for general-purpose timers TIM10–TIM14.
///
union tim_ctrl_gpx_tim10111314_cr1
{
    uint32_t r;
    struct
    {
        uint32_t cen      : 1;
        uint32_t udis     : 1;
        uint32_t urs      : 1;
        uint32_t opm      : 1;
        uint32_t          : 3;
        uint32_t arpe     : 1;
        uint32_t ckd      : 2;
        uint32_t          : 1;
        uint32_t uifremap : 1;
        uint32_t          : 20;
    } bf;
};

///
/// \brief Interrupt Enable Register (DIER) for general-purpose timers TIM10–TIM14.
///
union tim_ctrl_gpx_tim10111314_dier
{
    uint32_t r;
    struct
    {
        uint32_t uie   : 1;
        uint32_t cc1ie : 1;
        uint32_t       : 30;
    } bf;
};

///
/// \brief Status Register (SR) for general-purpose timers TIM10–TIM14.
///
union tim_ctrl_gpx_tim10111314_sr
{
    uint32_t r;
    struct
    {
        uint32_t uif   : 1;
        uint32_t cc1if : 1;
        uint32_t       : 7;
        uint32_t cc1of : 1;
        uint32_t       : 22;
    } bf;
};

///
/// \brief Event Generation Register (EGR) for general-purpose timers TIM10–TIM14.
///
union tim_ctrl_gpx_tim10111314_egr
{
    uint32_t r;
    struct
    {
        uint32_t ug   : 1;
        uint32_t cc1g : 1;
        uint32_t      : 30;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 1 Input Mode (CCMR1) for general-purpose
///        timers TIM10-TIM14.
///
union tim_ctrl_gpx_tim10111314_ccmr1_in
{
    uint32_t r;
    struct
    {
        uint32_t cc1s   : 2;
        uint32_t ic1psc : 2;
        uint32_t ic1f   : 4;
        uint32_t        : 24;
    } bf;
};

///
/// \brief Capture/Compare Mode Register 1 Output Mode (CCMR1) for general-purpose
///        timers TIM10-TIM14.
///
union tim_ctrl_gpx_tim10111314_ccmr1_out
{
    uint32_t r;
    struct
    {
        uint32_t cc1s     : 2;
        uint32_t oc1fe    : 1;
        uint32_t oc1pe    : 1;
        uint32_t oc1m     : 3;
        uint32_t          : 9;
        uint32_t oc1m_msb : 1;
        uint32_t          : 15;
    } bf;
};

///
/// \brief Capture/Compare Enable Register (CCER) for general-purpose timers TIM10-TIM14.
///
union tim_ctrl_gpx_tim10111314_ccer
{
    uint32_t r;
    struct
    {
        uint32_t cc1e  : 1;
        uint32_t cc1p  : 1;
        uint32_t       : 1;
        uint32_t cc1np : 1;
        uint32_t       : 28;
    } bf;
};

///
/// \brief Counter Register (CNT) for general-purpose timers TIM10-TIM14.
///
union tim_ctrl_gpx_tim10111314_cnt
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
/// \brief Prescaler Register (PSC) for general-purpose timers TIM10-TIM14.
///
union tim_ctrl_gpx_tim10111314_psc
{
    uint32_t r;
    struct
    {
        uint32_t psc : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Auto-Reload Register (ARR) for general-purpose timers TIM10-TIM14.
///
union tim_ctrl_gpx_tim10111314_arr
{
    uint32_t r;
    struct
    {
        uint32_t arr : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Capture/Compare Register (CCR1) for general-purpose timers TIM10-TIM14.
///
union tim_ctrl_gpx_tim10111314_ccr1
{
    uint32_t r;
    struct
    {
        uint16_t ccr1 : 16;
        uint16_t      : 16;
    } bf;
};

///
/// \brief TIM11 Option Register (TIM11_OR).
///
union tim_ctrl_gpx_tim11_or
{
    uint32_t r;
    struct
    {
        uint32_t ti1_rmp : 2;
        uint32_t         : 30;
    } bf;
};

///
/// \brief Register map for general-purpose timers TIM2–TIM5.
///
/// This structure represents the memory-mapped register layout of the
/// general-purpose timers TIM2, TIM3, TIM4, and TIM5. The register order
/// and reserved fields are aligned with the device reference manual to
/// allow direct access via a peripheral base address.
///
struct tim_ctrl_gpx_tim2345_regs
{
    union tim_ctrl_gpx_tim2345_cr1  cr1;
    union tim_ctrl_gpx_tim2345_cr2  cr2;
    union tim_ctrl_gpx_tim2345_smcr smcr;
    union tim_ctrl_gpx_tim2345_dier dier;
    union tim_ctrl_gpx_tim2345_sr   sr;
    union tim_ctrl_gpx_tim2345_egr  egr;
    union
    {
        union tim_ctrl_gpx_tim2345_ccmr1_in  in;
        union tim_ctrl_gpx_tim2345_ccmr1_out out;
    } ccmr1;
    union
    {
        union tim_ctrl_gpx_tim2345_ccmr2_in  in;
        union tim_ctrl_gpx_tim2345_ccmr2_out out;
    } ccmr2;
    union tim_ctrl_gpx_tim2345_ccer ccer;
    union tim_ctrl_gpx_tim2345_cnt  cnt;
    union tim_ctrl_gpx_tim2345_psc  psc;
    union tim_ctrl_gpx_tim2345_arr  arr;
    uint32_t res0[1];
    union tim_ctrl_gpx_tim2345_ccr1 ccr1;
    union tim_ctrl_gpx_tim2345_ccr2 ccr2;
    union tim_ctrl_gpx_tim2345_ccr3 ccr3;
    union tim_ctrl_gpx_tim2345_ccr4 ccr4;
    uint32_t res1[1];
    union tim_ctrl_gpx_tim2345_dcr  dcr;
    union tim_ctrl_gpx_tim2345_dmar dmar;
    union tim_ctrl_gpx_tim2_or      tim2_or;
    union tim_ctrl_gpx_tim5_or      tim5_or;
};

///
/// \brief Register map for timers TIM9 and TIM12.
///
/// This structure defines the memory-mapped register layout for TIM9 and
/// TIM12. The register order and reserved fields are aligned with the
/// device reference manual to allow direct access via a peripheral base address.
///
struct tim_ctrl_gpx_tim912_regs
{
    union tim_ctrl_gpx_tim912_cr1  cr1;
    uint32_t res0[1];
    union tim_ctrl_gpx_tim912_smcr smcr;
    union tim_ctrl_gpx_tim912_dier dier;
    union tim_ctrl_gpx_tim912_sr   sr;
    union tim_ctrl_gpx_tim912_egr  egr;
    union
    {
        union tim_ctrl_gpx_tim912_ccmr1_in  in;
        union tim_ctrl_gpx_tim912_ccmr1_out out;
    } ccmr1;
    uint32_t res1[1];
    union tim_ctrl_gpx_tim912_ccer ccer;
    union tim_ctrl_gpx_tim912_cnt  cnt;
    union tim_ctrl_gpx_tim912_psc  psc;
    union tim_ctrl_gpx_tim912_arr  arr;
    uint32_t res2[1];
    union tim_ctrl_gpx_tim912_ccr1 ccr1;
    union tim_ctrl_gpx_tim912_ccr2 ccr2;
};

///
/// \brief Register map for timers TIM10-TIM14.
///
/// This structure defines the memory-mapped register layout for TIM10, TIM11,
/// TIM13, and TIM14. The register order and reserved fields are aligned with the
/// device reference manual to allow direct access via a peripheral base address.
///
struct tim_ctrl_gpx_tim10111314_regs
{
    union tim_ctrl_gpx_tim10111314_cr1  cr1;
    uint32_t res0[2];
    union tim_ctrl_gpx_tim10111314_dier dier;
    union tim_ctrl_gpx_tim10111314_sr   sr;
    union tim_ctrl_gpx_tim10111314_egr  egr;
    union
    {
        union tim_ctrl_gpx_tim10111314_ccmr1_in  in;
        union tim_ctrl_gpx_tim10111314_ccmr1_out out;
    } ccmr1;
    uint32_t res1[1];
    union tim_ctrl_gpx_tim10111314_ccer ccer;
    union tim_ctrl_gpx_tim10111314_cnt  cnt;
    union tim_ctrl_gpx_tim10111314_psc  psc;
    union tim_ctrl_gpx_tim10111314_arr  arr;
    uint32_t res2[1];
    union tim_ctrl_gpx_tim10111314_ccr1 ccr1;
    uint32_t res3[6];
    union tim_ctrl_gpx_tim11_or tim11_or;
};

///
/// \brief Runtime device context for general-purpose timers TIM2–TIM5.
///
/// This structure holds all runtime state required to control a TIM2–TIM5
/// instance. It includes a pointer to the memory-mapped registers, a temporary
/// shadow copy for safe modification, capture/compare history, configuration
/// modes, and initialization status.
///
struct tim_ctrl_gpx_tim2345_dev
{
    volatile struct tim_ctrl_gpx_tim2345_regs *rmap;
    struct tim_ctrl_gpx_tim2345_regs rtmp;
    struct tim_ctrl_ccr_data ccr_data[4];
    tim_ctrl_gpx_tim2345_id_t id;
    tim_ctrl_gpx_tim2345_mode_t ccmr1_mode;
    tim_ctrl_gpx_tim2345_mode_t ccmr2_mode;
    tim_ctrl_stat_t stat;
};

///
/// \brief Runtime device context for general-purpose timers TIM9 and TIM12.
///
/// This structure holds all runtime state required to control a TIM9 and TIM12
/// instance. It includes a pointer to the memory-mapped registers, a temporary
/// shadow copy for safe modification, capture/compare history, configuration
/// modes, and initialization status.
///
struct tim_ctrl_gpx_tim912_dev
{
    volatile struct tim_ctrl_gpx_tim912_regs *rmap;
    struct tim_ctrl_gpx_tim912_regs rtmp;
    struct tim_ctrl_ccr_data ccr_data[2];
    tim_ctrl_gpx_tim912_id_t id;
    tim_ctrl_gpx_tim912_mode_t ccmr1_mode;
    tim_ctrl_stat_t stat;
};

///
/// \brief Runtime device context for general-purpose timers TIM10-TIM14.
///
/// This structure holds all runtime state required to control a TIM10-TIM14
/// instance. It includes a pointer to the memory-mapped registers, a temporary
/// shadow copy for safe modification, capture/compare history, configuration
/// modes, and initialization status.
///
struct tim_ctrl_gpx_tim10111314_dev
{
    volatile struct tim_ctrl_gpx_tim10111314_regs *rmap;
    struct tim_ctrl_gpx_tim10111314_regs rtmp;
    struct tim_ctrl_ccr_data ccr_data[1];
    tim_ctrl_gpx_tim10111314_id_t id;
    tim_ctrl_gpx_tim10111314_mode_t ccmr1_mode;
    tim_ctrl_stat_t stat;
};

///
/// \brief Initializes the general-purpose timer (TIM2-TIM5).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim2345_init(void *tim);

///
/// \brief Initializes the general-purpose timer (TIM9 and TIM12).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim912_init(void *tim);

///
/// \brief Initializes the general-purpose timer (TIM10-TIM14).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim10111314_init(void *tim);

///
/// \brief Deinitializes the general-purpose timer (TIM2-TIM5).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim2345_deinit(void *tim);

///
/// \brief Deinitializes the general-purpose timer (TIM9 and TIM12).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim912_deinit(void *tim);

///
/// \brief Deinitializes the general-purpose timer (TIM10-TIM14).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim10111314_deinit(void *tim);

///
/// \brief Enables the general-purpose timer (TIM2-TIM5).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim2345_enable(void *tim);

///
/// \brief Enables the general-purpose timer (TIM9 and TIM12).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim912_enable(void *tim);

///
/// \brief Enables the general-purpose timer (TIM10-TIM14).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim10111314_enable(void *tim);

///
/// \brief Disables the general-purpose timer (TIM2-TIM5).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim2345_disable(void *tim);

///
/// \brief Disables the general-purpose timer (TIM9 and TIM12).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim912_disable(void *tim);

///
/// \brief Disables the general-purpose timer (TIM10-TIM14).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim10111314_disable(void *tim);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_GPX_H */
