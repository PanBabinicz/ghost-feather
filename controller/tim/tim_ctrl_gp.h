#ifndef _TIM_CTRL_GP_H
#define _TIM_CTRL_GP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
union tim_ctrl_gpx_tim2345_cr1
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cen      : 1;
        uint16_t udis     : 1;
        uint16_t urs      : 1;
        uint16_t opm      : 1;
        uint16_t dir      : 1;
        uint16_t cms      : 2;
        uint16_t arpe     : 1;
        uint16_t ckd      : 2;
        uint16_t          : 1;
        uint16_t uifremap : 1;
        uint16_t          : 4;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_cr2
{
    uint16_t r;
    struct bit_field
    {
        uint16_t          : 3;
        uint16_t ccds     : 1;
        uint16_t mms      : 3;
        uint16_t ti1s     : 1;
        uint16_t          : 8;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_smcr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t sms      : 3;
        uint32_t occs     : 1;
        uint32_t ts       : 3;
        uint32_t msm      : 1;
        uint32_t etf      : 4;
        uint32_t etps     : 2;
        uint32_t ece      : 1;
        uint32_t etp      : 1;
        uint32_t sms_msb  : 1;
        uint32_t          : 15;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_dier
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uie      : 1;
        uint16_t cc1ie    : 1;
        uint16_t cc2ie    : 1;
        uint16_t cc3ie    : 1;
        uint16_t cc4ie    : 1;
        uint16_t          : 1;
        uint16_t tie      : 1;
        uint16_t          : 1;
        uint16_t ude      : 1;
        uint16_t cc1de    : 1;
        uint16_t cc2de    : 1;
        uint16_t cc3de    : 1;
        uint16_t cc4de    : 1;
        uint16_t          : 1;
        uint16_t tde      : 1;
        uint16_t          : 1;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_sr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uif      : 1;
        uint16_t cc1if    : 1;
        uint16_t cc2if    : 1;
        uint16_t cc3if    : 1;
        uint16_t cc4if    : 1;
        uint16_t          : 1;
        uint16_t tif      : 1;
        uint16_t          : 2;
        uint16_t cc1of    : 1;
        uint16_t cc2of    : 1;
        uint16_t cc3of    : 1;
        uint16_t cc4of    : 1;
        uint16_t          : 3;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_egr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ug       : 1;
        uint16_t cc1g     : 1;
        uint16_t cc2g     : 1;
        uint16_t cc3g     : 1;
        uint16_t cc4g     : 1;
        uint16_t          : 1;
        uint16_t tg       : 1;
        uint16_t          : 9;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_ccmr1
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc1s     : 2;
        uint32_t ic1psc   : 2;
        uint32_t ic1f     : 4;
        uint32_t cc2s     : 2;
        uint32_t ic2psc   : 2;
        uint32_t ic2f     : 4;
        uint32_t          : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_ccmr1_alt
{
    uint32_t r;
    struct bit_field
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
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_ccmr2
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc3s     : 2;
        uint32_t ic3psc   : 2;
        uint32_t ic3f     : 4;
        uint32_t cc4s     : 2;
        uint32_t ic4psc   : 2;
        uint32_t ic4f     : 4;
        uint32_t          : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_ccmr2_alt
{
    uint32_t r;
    struct bit_field
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
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_ccer
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cc1e     : 1;
        uint16_t cc1p     : 1;
        uint16_t          : 1;
        uint16_t cc1np    : 1;
        uint16_t cc2e     : 1;
        uint16_t cc2p     : 1;
        uint16_t          : 1;
        uint16_t cc2np    : 1;
        uint16_t cc3e     : 1;
        uint16_t cc3p     : 1;
        uint16_t          : 1;
        uint16_t cc3np    : 1;
        uint16_t cc4e     : 1;
        uint16_t cc4p     : 1;
        uint16_t          : 1;
        uint16_t cc4np    : 1;
    };
};

///
/// \brief
///
/// \note  TIM2 and TIM5 have 32bit counter. Use 'r' to get/modify content of the counter.
///
union tim_ctrl_gpx_tim2345_cnt
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cnt      : 16;
        uint32_t          : 15;
        uint32_t uifcpy   : 1;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_psc
{
    uint16_t r;
    struct bit_field
    {
        uint16_t psc      : 16;
    };
};

///
/// \brief
///
/// \note  TIM2 and TIM5 have 32bit auto reload register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_arr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t arr      : 16;
        uint32_t          : 16;
    };
};

///
/// \brief
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr1
{
    uint32_t r;
    struct bit_field
    {
        uint32_t ccr1     : 16;
        uint32_t          : 16;
    };
};

///
/// \brief
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr2
{
    uint32_t r;
    struct bit_field
    {
        uint32_t ccr2     : 16;
        uint32_t          : 16;
    };
};

///
/// \brief
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr3
{
    uint32_t r;
    struct bit_field
    {
        uint32_t ccr3     : 16;
        uint32_t          : 16;
    };
};

///
/// \brief
///
/// \note  TIM2 and TIM5 have 32bit capture/compare register. Use 'r' to get/modify theirs content.
///
union tim_ctrl_gpx_tim2345_ccr4
{
    uint32_t r;
    struct bit_field
    {
        uint32_t ccr4     : 16;
        uint32_t          : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_dcr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t dba      : 5;
        uint16_t          : 3;
        uint16_t dbl      : 5;
        uint16_t          : 3;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2345_dmar
{
    uint16_t r;
    struct bit_field
    {
        uint16_t dmab     : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim2_or
{
    uint16_t r;
    struct bit_field
    {
        uint16_t          : 10;
        uint16_t itr1_rmp : 2;
        uint16_t          : 4;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim5_or
{
    uint16_t r;
    struct bit_field
    {
        uint16_t          : 6;
        uint16_t ti4_rmp  : 2;
        uint16_t          : 8;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_cr1
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cen      : 1;
        uint16_t udis     : 1;
        uint16_t urs      : 1;
        uint16_t opm      : 1;
        uint16_t          : 3;
        uint16_t arpe     : 1;
        uint16_t ckd      : 2;
        uint16_t          : 1;
        uint16_t uifremap : 1;
        uint16_t          : 4;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_smcr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t sms      : 3;
        uint32_t          : 1;
        uint32_t ts       : 3;
        uint32_t msm      : 1;
        uint32_t          : 8;
        uint32_t sms_msb  : 1;
        uint32_t          : 15;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_dier
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uie      : 1;
        uint16_t cc1ie    : 1;
        uint16_t cc2ie    : 1;
        uint16_t          : 3;
        uint16_t tie      : 1;
        uint16_t          : 9;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_sr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uif      : 1;
        uint16_t cc1if    : 1;
        uint16_t cc2if    : 1;
        uint16_t          : 3;
        uint16_t tif      : 1;
        uint16_t          : 2;
        uint16_t cc1of    : 1;
        uint16_t cc2of    : 1;
        uint16_t          : 5;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_egr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ug       : 1;
        uint16_t cc1g     : 1;
        uint16_t cc2g     : 1;
        uint16_t          : 3;
        uint16_t tg       : 1;
        uint16_t          : 9;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_ccmr1
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc1s     : 2;
        uint32_t ic1psc   : 2;
        uint32_t ic1f     : 4;
        uint32_t cc2s     : 2;
        uint32_t ic2psc   : 2;
        uint32_t ic2f     : 4;
        uint32_t          : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_ccmr1_alt
{
    uint32_t r;
    struct bit_field
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
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_ccer
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cc1e     : 1;
        uint16_t cc1p     : 1;
        uint16_t          : 1;
        uint16_t cc1np    : 1;
        uint16_t cc2e     : 1;
        uint16_t cc2p     : 1;
        uint16_t          : 1;
        uint16_t cc2np    : 1;
        uint16_t          : 8;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_cnt
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cnt      : 16;
        uint32_t          : 15;
        uint32_t uifcpy   : 1;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_psc
{
    uint16_t r;
    struct bit_field
    {
        uint16_t psc      : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_arr
{
    uint16_t r;
    struct bit_field
    {
        uint32_t arr      : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_ccr1
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ccr1     : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim912_ccr2
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ccr2     : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_cr1
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cen      : 1;
        uint16_t udis     : 1;
        uint16_t urs      : 1;
        uint16_t opm      : 1;
        uint16_t          : 3;
        uint16_t arpe     : 1;
        uint16_t ckd      : 2;
        uint16_t          : 1;
        uint16_t uifremap : 1;
        uint16_t          : 4;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_dier
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uie      : 1;
        uint16_t cc1ie    : 1;
        uint16_t          : 10;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_sr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uif      : 1;
        uint16_t cc1if    : 1;
        uint16_t          : 7;
        uint16_t cc1of    : 1;
        uint16_t          : 6;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_egr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ug       : 1;
        uint16_t cc1g     : 1;
        uint16_t          : 10;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_ccmr1
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc1s     : 2;
        uint32_t ic1psc   : 2;
        uint32_t ic1f     : 4;
        uint32_t          : 24;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_ccmr1_alt
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc1s     : 2;
        uint32_t oc1fe    : 1;
        uint32_t oc1pe    : 1;
        uint32_t oc1m     : 3;
        uint32_t          : 9;
        uint32_t oc1m_msb : 1;
        uint32_t          : 15;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_ccer
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cc1e     : 1;
        uint16_t cc1p     : 1;
        uint16_t          : 1;
        uint16_t cc1np    : 1;
        uint16_t          : 12;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_cnt
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cnt      : 16;
        uint32_t          : 15;
        uint32_t uifcpy   : 1;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_psc
{
    uint16_t r;
    struct bit_field
    {
        uint16_t psc      : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_arr
{
    uint16_t r;
    struct bit_field
    {
        uint32_t arr      : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim10111314_ccr1
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ccr1     : 16;
    };
};

///
/// \brief
///
union tim_ctrl_gpx_tim11_or
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ti1_rmp  : 2;
        uint16_t ccr1     : 14;
    };
};

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_GP_H */
