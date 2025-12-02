#ifndef _TIM_CTRL_ADVX_H
#define _TIM_CTRL_ADVX_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "tim_ctrl_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
typedef enum tim_ctrl_adv6_tim18_id
{
    TIM_CTRL_ADV6_TIM18_ID_1 = 0,
    TIM_CTRL_ADV6_TIM18_ID_8,
} tim_ctrl_adv6_tim18_id_t;

///
/// \brief
///
typedef enum tim_ctrl_adv6_tim18_mode
{
    TIM_CTRL_ADV6_TIM18_MODE_IN_CAP = 0,
    TIM_CTRL_ADV6_TIM18_MODE_OUT_COMP,
} tim_ctrl_adv6_tim18_mode_t;

///
/// \brief
///
union tim_ctrl_adv6_tim18_cr1
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
/// \brief
///
union tim_ctrl_adv6_tim18_cr2
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
        uint32_t       : 8;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_smcr
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
/// \brief
///
union tim_ctrl_adv6_tim18_dier
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
/// \brief
///
union tim_ctrl_adv6_tim18_sr
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
/// \brief
///
union tim_ctrl_adv6_tim18_egr
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
/// \brief
///
union tim_ctrl_adv6_tim18_ccmr1_in
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
/// \brief
///
union tim_ctrl_adv6_tim18_ccmr1_out
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
/// \brief
///
union tim_ctrl_adv6_tim18_ccmr2_in
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
/// \brief
///
union tim_ctrl_adv6_tim18_ccmr2_out
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
/// \brief
///
union tim_ctrl_adv6_tim18_ccer
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
/// \brief
///
union tim_ctrl_adv6_tim18_cnt
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
/// \brief
///
union tim_ctrl_adv6_tim18_psc
{
    uint32_t r;
    struct
    {
        uint32_t psc : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_arr
{
    uint32_t r;
    struct
    {
        uint32_t arr : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_rcr
{
    uint32_t r;
    struct
    {
        uint32_t rep : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_ccr1
{
    uint32_t r;
    struct
    {
        uint32_t ccr1 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_ccr2
{
    uint32_t r;
    struct
    {
        uint32_t ccr2 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_ccr3
{
    uint32_t r;
    struct
    {
        uint32_t ccr3 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_ccr4
{
    uint32_t r;
    struct
    {
        uint32_t ccr4 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_bdtr
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
/// \brief
///
union tim_ctrl_adv6_tim18_dcr
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
/// \brief
///
union tim_ctrl_adv6_tim18_dmar
{
    uint32_t r;
    struct
    {
        uint32_t dmab : 32;
    } bf;
};

///
/// \brief
///
union tim_ctrl_adv6_tim18_ccmr3
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
/// \brief
///
union tim_ctrl_adv6_tim18_ccr5
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
/// \brief
///
union tim_ctrl_adv6_tim18_ccr6
{
    uint32_t r;
    struct
    {
        uint32_t ccr6 : 16;
        uint32_t      : 16;
    } bf;
};

///
/// \brief
///
struct tim_ctrl_adv6_tim18_regs
{
    union tim_ctrl_adv6_tim18_cr1  cr1;
    union tim_ctrl_adv6_tim18_cr2  cr2;
    union tim_ctrl_adv6_tim18_smcr smcr;
    union tim_ctrl_adv6_tim18_dier dier;
    union tim_ctrl_adv6_tim18_sr   sr;
    union tim_ctrl_adv6_tim18_egr  egr;
    union
    {
        union tim_ctrl_adv6_tim18_ccmr1_in  in;
        union tim_ctrl_adv6_tim18_ccmr1_out out;

    } ccmr1;
    union
    {
        union tim_ctrl_adv6_tim18_ccmr2_in  in;
        union tim_ctrl_adv6_tim18_ccmr2_out out;

    } ccmr2;
    union tim_ctrl_adv6_tim18_ccer  ccer;
    union tim_ctrl_adv6_tim18_cnt   cnt;
    union tim_ctrl_adv6_tim18_psc   psc;
    union tim_ctrl_adv6_tim18_arr   arr;
    union tim_ctrl_adv6_tim18_rcr   rcr;
    union tim_ctrl_adv6_tim18_ccr1  ccr1;
    union tim_ctrl_adv6_tim18_ccr2  ccr2;
    union tim_ctrl_adv6_tim18_ccr3  ccr3;
    union tim_ctrl_adv6_tim18_ccr4  ccr4;
    union tim_ctrl_adv6_tim18_bdtr  bdtr;
    union tim_ctrl_adv6_tim18_dcr   dcr;
    union tim_ctrl_adv6_tim18_dmar  dmar;
    union tim_ctrl_adv6_tim18_ccmr3 ccmr3;
    union tim_ctrl_adv6_tim18_ccr5  ccr5;
    union tim_ctrl_adv6_tim18_ccr6  ccr6;
};

///
/// \brief
///
struct tim_ctrl_adv6_tim18_dev
{
    volatile struct tim_ctrl_adv6_tim18_regs *rmap;
    struct tim_ctrl_adv6_tim18_regs rtmp;
    tim_ctrl_adv6_tim18_id_t id;
    tim_ctrl_adv6_tim18_mode_t ccmr1_mode;
    tim_ctrl_adv6_tim18_mode_t ccmr2_mode;
    tim_ctrl_stat_t stat;
};

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_adv6_tim18_init(void *tim);

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_adv6_tim18_deinit(void *tim);

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_adv6_tim18_init(void *tim);

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_adv6_tim18_init(void *tim);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_ADVX_H */
