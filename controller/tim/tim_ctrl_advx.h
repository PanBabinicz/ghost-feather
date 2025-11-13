#ifndef _TIM_CTRL_ADV_H
#define _TIM_CTRL_ADV_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
union tim_ctrl_adv4_timx_cr1
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
union tim_ctrl_adv4_timx_cr2
{
    uint32_t r;
    struct bit_field
    {
        uint32_t ccpc     : 1;
        uint32_t          : 1;
        uint32_t ccus     : 1;
        uint32_t ccds     : 1;
        uint32_t          : 1;
        uint32_t mms      : 3;
        uint32_t ti1s     : 1;
        uint32_t ois1     : 1;
        uint32_t ois1n    : 1;
        uint32_t ois2     : 1;
        uint32_t ois2n    : 1;
        uint32_t ois3     : 1;
        uint32_t ois3n    : 1;
        uint32_t ois4     : 1;
        uint32_t          : 1;
        uint32_t ois5     : 1;
        uint32_t          : 1;
        uint32_t ois6     : 1;
        uint32_t          : 1;
        uint32_t mms2     : 4;
        uint32_t          : 8;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_smcr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t sms      : 3;
        uint32_t          : 1;
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
union tim_ctrl_adv4_timx_dier
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uie      : 1;
        uint16_t cc1ie    : 1;
        uint16_t cc2ie    : 1;
        uint16_t cc3ie    : 1;
        uint16_t cc4ie    : 1;
        uint16_t comie    : 1;
        uint16_t tie      : 1;
        uint16_t bie      : 1;
        uint16_t ude      : 1;
        uint16_t cc1de    : 1;
        uint16_t cc2de    : 1;
        uint16_t cc3de    : 1;
        uint16_t cc4de    : 1;
        uint16_t comde    : 1;
        uint16_t tde      : 1;
        uint16_t          : 1;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_sr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t uif      : 1;
        uint32_t cc1if    : 1;
        uint32_t cc2if    : 1;
        uint32_t cc3if    : 1;
        uint32_t cc4if    : 1;
        uint32_t comif    : 1;
        uint32_t tif      : 1;
        uint32_t bif      : 1;
        uint32_t b2if     : 1;
        uint32_t cc1of    : 1;
        uint32_t cc2of    : 1;
        uint32_t cc3of    : 1;
        uint32_t cc4of    : 1;
        uint32_t          : 3;
        uint32_t cc5if    : 1;
        uint32_t cc6if    : 1;
        uint32_t          : 14;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_egr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ug       : 1;
        uint16_t cc1g     : 1;
        uint16_t cc2g     : 1;
        uint16_t cc3g     : 1;
        uint16_t cc4g     : 1;
        uint16_t comg     : 1;
        uint16_t tg       : 1;
        uint16_t bg       : 1;
        uint16_t b2g      : 1;
        uint16_t          : 7;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccmr1_in
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
union tim_ctrl_adv4_timx_ccmr1_out
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
union tim_ctrl_adv4_timx_ccmr2_in
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
union tim_ctrl_adv4_timx_ccmr2_out
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
union tim_ctrl_adv4_timx_ccer
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc1e     : 1;
        uint32_t cc1p     : 1;
        uint32_t cc1ne    : 1;
        uint32_t cc1np    : 1;
        uint32_t cc2e     : 1;
        uint32_t cc2p     : 1;
        uint32_t cc2ne    : 1;
        uint32_t cc2np    : 1;
        uint32_t cc3e     : 1;
        uint32_t cc3p     : 1;
        uint32_t cc3ne    : 1;
        uint32_t cc3np    : 1;
        uint32_t cc4e     : 1;
        uint32_t cc4p     : 1;
        uint32_t          : 1;
        uint32_t cc4np    : 1;
        uint32_t cc5e     : 1;
        uint32_t cc5p     : 1;
        uint32_t          : 2;
        uint32_t cc6e     : 1;
        uint32_t cc6p     : 1;
        uint32_t          : 10;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_cnt
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
union tim_ctrl_adv4_timx_psc
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
union tim_ctrl_adv4_timx_arr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t arr      : 16;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_rcr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t rep      : 16;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccr1
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
union tim_ctrl_adv4_timx_ccr2
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
union tim_ctrl_adv4_timx_ccr3
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ccr3     : 16;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccr4
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ccr4     : 16;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_bdtr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t dtg      : 8;
        uint32_t lock     : 2;
        uint32_t ossi     : 1;
        uint32_t ossr     : 1;
        uint32_t bke      : 1;
        uint32_t bkp      : 1;
        uint32_t aoe      : 1;
        uint32_t moe      : 1;
        uint32_t bkf      : 4;
        uint32_t bk2f     : 4;
        uint32_t bk2e     : 1;
        uint32_t bk2p     : 1;
        uint32_t          : 6;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_dcr
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
union tim_ctrl_adv4_timx_dmar
{
    uint32_t r;
    struct bit_field
    {
        uint32_t dmab     : 32;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccmr3
{
    uint32_t r;
    struct bit_field
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
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccr5
{
    uint32_t r;
    struct bit_field
    {
        uint32_t ccr5     : 16;
        uint32_t          : 13;
        uint32_t gc5c1    : 1;
        uint32_t gc5c2    : 1;
        uint32_t gc5c3    : 1;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccr6
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ccr6     : 16;
    };
};

///
/// \brief
///
struct tim_ctrl_adv4_timx_regs
{
    union tim_ctrl_adv4_timx_cr1           cr1;
    union tim_ctrl_adv4_timx_cr2           cr2;
    union tim_ctrl_adv4_timx_smcr          smcr;
    union tim_ctrl_adv4_timx_dier          dier;
    union tim_ctrl_adv4_timx_sr            sr;
    union tim_ctrl_adv4_timx_egr           egr;
    union
    {
        union tim_ctrl_adv4_timx_ccmr1_in  in;
        union tim_ctrl_adv4_timx_ccmr1_out out;

    } ccmr1;
    union
    {
        union tim_ctrl_adv4_timx_ccmr2_in  in;
        union tim_ctrl_adv4_timx_ccmr2_out out;

    } ccmr2;
    union tim_ctrl_adv4_timx_ccer          ccer;
    union tim_ctrl_adv4_timx_cnt           cnt;
    union tim_ctrl_adv4_timx_psc           psc;
    union tim_ctrl_adv4_timx_arr           arr;
    union tim_ctrl_adv4_timx_rcr           rcr;
    union tim_ctrl_adv4_timx_ccr1          ccr1;
    union tim_ctrl_adv4_timx_ccr2          ccr2;
    union tim_ctrl_adv4_timx_ccr3          ccr3;
    union tim_ctrl_adv4_timx_ccr4          ccr4;
    union tim_ctrl_adv4_timx_bdtr          bdtr;
    union tim_ctrl_adv4_timx_dcr           dcr;
    union tim_ctrl_adv4_timx_dmar          dmar;
    union tim_ctrl_adv4_timx_ccmr3         ccmr3;
    union tim_ctrl_adv4_timx_ccr5          ccr5;
    union tim_ctrl_adv4_timx_ccr6          ccr6;
};

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_ADV_H */
