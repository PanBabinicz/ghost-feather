#include "ll_tim_advx.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief Default register configuration for TIM1 and TIM8 after power-on reset.
///
/// This constant structure represents the expected reset (POR) state of the
/// advanced timer registers TIM1 and TIM8. It is used as a known-good baseline
/// for initialization and for restoring registers to their default values
/// before applying custom configuration.
///
static const struct ll_tim_adv6_tim18_regs ll_tim_adv6_tim18_por =
{
    .cr1 =
    {
        .bf =
        {
            .cen      = 0x00,
            .udis     = 0x00,
            .urs      = 0x00,
            .opm      = 0x00,
            .dir      = 0x00,
            .cms      = 0x00,
            .arpe     = 0x00,
            .ckd      = 0x00,
            .uifremap = 0x00,
        },
    },

    .cr2 =
    {
        .bf =
        {
            .ccpc  = 0x00,
            .ccus  = 0x00,
            .ccds  = 0x00,
            .mms   = 0x00,
            .ti1s  = 0x00,
            .ois1  = 0x00,
            .ois1n = 0x00,
            .ois2  = 0x00,
            .ois2n = 0x00,
            .ois3  = 0x00,
            .ois3n = 0x00,
            .ois4  = 0x00,
            .ois5  = 0x00,
            .ois6  = 0x00,
            .mms2  = 0x00,
        },
    },

    .smcr =
    {
        .bf =
        {
            .sms     = 0x00,
            .ts      = 0x00,
            .msm     = 0x00,
            .etf     = 0x00,
            .etps    = 0x00,
            .ece     = 0x00,
            .etp     = 0x00,
            .sms_msb = 0x00,
        },
    },

    .dier =
    {
        .bf =
        {
            .uie   = 0x00,
            .cc1ie = 0x00,
            .cc2ie = 0x00,
            .cc3ie = 0x00,
            .cc4ie = 0x00,
            .comie = 0x00,
            .tie   = 0x00,
            .bie   = 0x00,
            .ude   = 0x00,
            .cc1de = 0x00,
            .cc2de = 0x00,
            .cc3de = 0x00,
            .cc4de = 0x00,
            .comde = 0x00,
            .tde   = 0x00,
        },
    },

    .sr =
    {
        .bf =
        {
            .uif   = 0x00,
            .cc1if = 0x00,
            .cc2if = 0x00,
            .cc3if = 0x00,
            .cc4if = 0x00,
            .comif = 0x00,
            .tif   = 0x00,
            .bif   = 0x00,
            .b2if  = 0x00,
            .cc1of = 0x00,
            .cc2of = 0x00,
            .cc3of = 0x00,
            .cc4of = 0x00,
            .cc5if = 0x00,
            .cc6if = 0x00,
        },
    },

    .egr =
    {
        .bf =
        {
            .ug   = 0x00,
            .cc1g = 0x00,
            .cc2g = 0x00,
            .cc3g = 0x00,
            .cc4g = 0x00,
            .comg = 0x00,
            .tg   = 0x00,
            .bg   = 0x00,
            .b2g  = 0x00,
        },
    },

    .ccmr1 =
    {
        .out =
        {
            .bf =
            {
                .cc1s     = 0x00,
                .oc1fe    = 0x00,
                .oc1pe    = 0x00,
                .oc1m     = 0x00,
                .oc1ce    = 0x00,
                .cc2s     = 0x00,
                .oc2fe    = 0x00,
                .oc2pe    = 0x00,
                .oc2m     = 0x00,
                .oc2ce    = 0x00,
                .oc1m_msb = 0x00,
                .oc2m_msb = 0x00,
            },
        },
    },

    .ccmr2 =
    {
        .out =
        {
            .bf =
            {
                .cc3s     = 0x00,
                .oc3fe    = 0x00,
                .oc3pe    = 0x00,
                .oc3m     = 0x00,
                .oc3ce    = 0x00,
                .cc4s     = 0x00,
                .oc4fe    = 0x00,
                .oc4pe    = 0x00,
                .oc4m     = 0x00,
                .oc4ce    = 0x00,
                .oc3m_msb = 0x00,
                .oc4m_msb = 0x00,
            },
        },
    },

    .ccer =
    {
        .bf =
        {
            .cc1e  = 0x00,
            .cc1p  = 0x00,
            .cc1ne = 0x00,
            .cc1np = 0x00,
            .cc2e  = 0x00,
            .cc2p  = 0x00,
            .cc2ne = 0x00,
            .cc2np = 0x00,
            .cc3e  = 0x00,
            .cc3p  = 0x00,
            .cc3ne = 0x00,
            .cc3np = 0x00,
            .cc4e  = 0x00,
            .cc4p  = 0x00,
            .cc4np = 0x00,
            .cc5e  = 0x00,
            .cc5p  = 0x00,
            .cc6e  = 0x00,
            .cc6p  = 0x00,
        },
    },

    .cnt =
    {
        .bf =
        {
            .cnt    = 0x00,
            .uifcpy = 0x00,
        },
    },

    .psc =
    {
        .bf =
        {
            .psc = 0x00,
        },
    },

    .arr =
    {
        .bf =
        {
            .arr = 0xffff,
        },
    },

    .rcr =
    {
        .bf =
        {
            .rep = 0x00,
        },
    },

    .ccr1 =
    {
        .bf =
        {
            .ccr1 = 0x00,
        },
    },

    .ccr2 =
    {
        .bf =
        {
            .ccr2 = 0x00,
        },
    },

    .ccr3 =
    {
        .bf =
        {
            .ccr3 = 0x00,
        },
    },

    .ccr4 =
    {
        .bf =
        {
            .ccr4 = 0x00,
        },
    },

    .bdtr =
    {
        .bf =
        {
            .dtg  = 0x00,
            .lock = 0x00,
            .ossi = 0x00,
            .ossr = 0x00,
            .bke  = 0x00,
            .bkp  = 0x00,
            .aoe  = 0x00,
            .moe  = 0x00,
            .bkf  = 0x00,
            .bk2f = 0x00,
            .bk2e = 0x00,
            .bk2p = 0x00,
        },
    },

    .dcr =
    {
        .bf =
        {
            .dba = 0x00,
            .dbl = 0x00,
        },
    },

    .dmar =
    {
        .bf =
        {
            .dmab = 0x00,
        },
    },

    .ccmr3 =
    {
        .bf =
        {
            .oc5fe    = 0x00,
            .oc5pe    = 0x00,
            .oc5m     = 0x00,
            .oc5ce    = 0x00,
            .oc6fe    = 0x00,
            .oc6pe    = 0x00,
            .oc6m     = 0x00,
            .oc6ce    = 0x00,
            .oc5m_msb = 0x00,
            .oc6m_msb = 0x00,
        },
    },

    .ccr5 =
    {
        .bf =
        {
            .ccr5  = 0x00,
            .gc5c1 = 0x00,
            .gc5c2 = 0x00,
            .gc5c3 = 0x00,
        },
    },

    .ccr6 =
    {
        .bf =
        {
            .ccr6 = 0x00,
        },
    },
};

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ll_tim_res_t ll_tim_adv6_tim18_init(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_adv6_tim18_dev *dev = (struct ll_tim_adv6_tim18_dev *)tim;

    if (dev->stat == LL_TIM_STAT_INIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.r  = dev->rtmp.cr1.r;
    dev->rmap->cr2.r  = dev->rtmp.cr2.r;
    dev->rmap->smcr.r = dev->rtmp.smcr.r;
    dev->rmap->dier.r = dev->rtmp.dier.r;
    dev->rmap->sr.r   = dev->rtmp.sr.r;
    dev->rmap->egr.r  = dev->rtmp.egr.r;

    /* TODO: Not every channel can be input. */
    if (dev->ccmr1_mode == LL_TIM_ADV6_TIM18_MODE_IN_CAP)
    {
        dev->rmap->ccmr1.in.r = dev->rtmp.ccmr1.in.r;
    }
    else
    {
        dev->rmap->ccmr1.out.r = dev->rtmp.ccmr1.out.r;
    }

    if (dev->ccmr2_mode == LL_TIM_ADV6_TIM18_MODE_IN_CAP)
    {
        dev->rmap->ccmr2.in.r = dev->rtmp.ccmr2.in.r;
    }
    else
    {
        dev->rmap->ccmr2.out.r = dev->rtmp.ccmr2.out.r;
    }

    dev->rmap->ccer.r  = dev->rtmp.ccer.r;
    dev->rmap->cnt.r   = dev->rtmp.cnt.r;
    dev->rmap->psc.r   = dev->rtmp.psc.r;
    dev->rmap->arr.r   = dev->rtmp.arr.r;
    dev->rmap->rcr.r   = dev->rtmp.rcr.r;
    dev->rmap->ccr1.r  = dev->rtmp.ccr1.r;
    dev->rmap->ccr2.r  = dev->rtmp.ccr2.r;
    dev->rmap->ccr3.r  = dev->rtmp.ccr3.r;
    dev->rmap->ccr4.r  = dev->rtmp.ccr4.r;
    dev->rmap->bdtr.r  = dev->rtmp.bdtr.r;
    dev->rmap->dcr.r   = dev->rtmp.dcr.r;
    dev->rmap->dmar.r  = dev->rtmp.dmar.r;
    dev->rmap->ccmr3.r = dev->rtmp.ccmr3.r;
    dev->rmap->ccr5.r  = dev->rtmp.ccr5.r;
    dev->rmap->ccr6.r  = dev->rtmp.ccr6.r;

    dev->stat = LL_TIM_STAT_INIT;

    return LL_TIM_RES_OK;
}

ll_tim_res_t ll_tim_adv6_tim18_deinit(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_adv6_tim18_dev *dev = (struct ll_tim_adv6_tim18_dev *)tim;

    if (dev->stat == LL_TIM_STAT_DEINIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.r       = ll_tim_adv6_tim18_por.cr1.r;
    dev->rmap->cr2.r       = ll_tim_adv6_tim18_por.cr2.r;
    dev->rmap->smcr.r      = ll_tim_adv6_tim18_por.smcr.r;
    dev->rmap->dier.r      = ll_tim_adv6_tim18_por.dier.r;
    dev->rmap->sr.r        = ll_tim_adv6_tim18_por.sr.r;
    dev->rmap->egr.r       = ll_tim_adv6_tim18_por.egr.r;
    dev->rmap->ccmr1.out.r = ll_tim_adv6_tim18_por.ccmr1.out.r;
    dev->rmap->ccmr2.out.r = ll_tim_adv6_tim18_por.ccmr2.out.r;
    dev->rmap->ccer.r      = ll_tim_adv6_tim18_por.ccer.r;
    dev->rmap->cnt.r       = ll_tim_adv6_tim18_por.cnt.r;
    dev->rmap->psc.r       = ll_tim_adv6_tim18_por.psc.r;
    dev->rmap->arr.r       = ll_tim_adv6_tim18_por.arr.r;
    dev->rmap->rcr.r       = ll_tim_adv6_tim18_por.rcr.r;
    dev->rmap->ccr1.r      = ll_tim_adv6_tim18_por.ccr1.r;
    dev->rmap->ccr2.r      = ll_tim_adv6_tim18_por.ccr2.r;
    dev->rmap->ccr3.r      = ll_tim_adv6_tim18_por.ccr3.r;
    dev->rmap->ccr4.r      = ll_tim_adv6_tim18_por.ccr4.r;
    dev->rmap->bdtr.r      = ll_tim_adv6_tim18_por.bdtr.r;
    dev->rmap->dcr.r       = ll_tim_adv6_tim18_por.dcr.r;
    dev->rmap->dmar.r      = ll_tim_adv6_tim18_por.dmar.r;
    dev->rmap->ccmr3.r     = ll_tim_adv6_tim18_por.ccmr3.r;
    dev->rmap->ccr5.r      = ll_tim_adv6_tim18_por.ccr5.r;
    dev->rmap->ccr6.r      = ll_tim_adv6_tim18_por.ccr6.r;

    dev->stat = LL_TIM_STAT_DEINIT;

    return LL_TIM_RES_OK;
}

ll_tim_res_t ll_tim_adv6_tim18_enable(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_adv6_tim18_dev *dev = (struct ll_tim_adv6_tim18_dev *)tim;

    if (dev->stat == LL_TIM_STAT_DEINIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.bf.cen = 0x01;

    return LL_TIM_RES_OK;
}

ll_tim_res_t ll_tim_adv6_tim18_disable(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_adv6_tim18_dev *dev = (struct ll_tim_adv6_tim18_dev *)tim;

    if (dev->stat == LL_TIM_STAT_DEINIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.bf.cen = 0x00;

    return LL_TIM_RES_OK;
}
