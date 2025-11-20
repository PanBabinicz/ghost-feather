#include "tim_ctrl_gpx.h"

///
/// \brief
///
static const tim_ctrl_gpx_tim2345_por =
{
    .cr1 =
    {
        .bit_fields =
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
        .bit_fields =
        {
            .ccds     = 0x00,
            .mms      = 0x00,
            .ti1s     = 0x00,
        },
    },

    .smcr =
    {
        .bit_fields =
        {
            .sms      = 0x00,
            .occs     = 0x00,
            .ts       = 0x00,
            .msm      = 0x00,
            .etf      = 0x00,
            .etps     = 0x00,
            .ece      = 0x00,
            .etp      = 0x00,
            .sms_msb  = 0x00,
        },
    },

    .dier =
    {
        .bit_fields =
        {
            .uie      = 0x00,
            .cc1ie    = 0x00,
            .cc2ie    = 0x00,
            .cc3ie    = 0x00,
            .cc4ie    = 0x00,
            .tie      = 0x00,
            .ude      = 0x00,
            .cc1de    = 0x00,
            .cc2de    = 0x00,
            .cc3de    = 0x00,
            .cc4de    = 0x00,
            .tde      = 0x00,
        },
    },

    .sr =
    {
        .bit_fields =
        {
            .uif      = 0x00,
            .cc1if    = 0x00,
            .cc2if    = 0x00,
            .cc3if    = 0x00,
            .cc4if    = 0x00,
            .tif      = 0x00,
            .cc1of    = 0x00,
            .cc2of    = 0x00,
            .cc3of    = 0x00,
            .cc4of    = 0x00,
        },
    },

    .egr =
    {
        .bit_fields =
        {
            .ug       = 0x00,
            .cc1g     = 0x00,
            .cc2g     = 0x00,
            .cc3g     = 0x00,
            .cc4g     = 0x00,
            .tg       = 0x00,
        },
    },

    .ccmr1 =
    {
        .out =
        {
            .bit_fields =
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
            .bit_fields =
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
        .bit_fields =
        {
            .cc1e     = 0x00,
            .cc1p     = 0x00,
            .cc1np    = 0x00,
            .cc2e     = 0x00,
            .cc2p     = 0x00,
            .cc2np    = 0x00,
            .cc3e     = 0x00,
            .cc3p     = 0x00,
            .cc3np    = 0x00,
            .cc4e     = 0x00,
            .cc4p     = 0x00,
            .cc4np    = 0x00,
        },
    },

    .cnt =
    {
        .bit_fields =
        {
            .cnt      = 0x00,
            .uifcpy   = 0x00,
        },
    },

    .psc =
    {
        .bit_fields =
        {
            .psc      = 0x00,
        },
    },

    .arr =
    {
        .bit_fields =
        {
            .arr      = 0xffff,
        },
    },

    .ccr1 =
    {
        .bit_fields =
        {
            .ccr1     = 0x00,
        },
    },

    .ccr2 =
    {
        .bit_fields =
        {
            .ccr2     = 0x00,
        },
    },

    .ccr3 =
    {
        .bit_fields =
        {
            .ccr3     = 0x00,
        },
    },

    .ccr4 =
    {
        .bit_fields =
        {
            .ccr4     = 0x00,
        },
    },

    .dcr =
    {
        .bit_fields =
        {
            .dba      = 0x00,
            .dbl      = 0x00,
        },
    },

    .dmar =
    {
        .bit_fields =
        {
            .dmab     = 0x00,
        },
    },

    .tim2_or =
    {
        .bit_fields =
        {
            .itr1_rmp = 0x00,
        },
    },

    .tim2_or =
    {
        .bit_fields =
        {
            .ti4_rmp  = 0x00,
        },
    },
};

///
/// \brief
///
struct tim_ctrl_gpx_tim912_regs
{
    union tim_ctrl_gpx_tim912_cr1           cr1;
    union tim_ctrl_gpx_tim912_smcr          smcr;
    union tim_ctrl_gpx_tim912_dier          dier;
    union tim_ctrl_gpx_tim912_sr            sr;
    union tim_ctrl_gpx_tim912_egr           egr;
    union
    {
        union tim_ctrl_gpx_tim912_ccmr1_in  in;
        union tim_ctrl_gpx_tim912_ccmr1_out out;
    } ccmr1;
    uint32_t                                res0[1];
    union tim_ctrl_gpx_tim912_ccer          ccer;
    union tim_ctrl_gpx_tim912_cnt           cnt;
    union tim_ctrl_gpx_tim912_psc           psc;
    union tim_ctrl_gpx_tim912_arr           arr;
    uint32_t                                res1[1];
    union tim_ctrl_gpx_tim912_ccr1          ccr1;
    union tim_ctrl_gpx_tim912_ccr2          ccr2;
};

///
/// \brief
///
static const tim_ctrl_gpx_tim912_por =
{
    .cr1 =
    {
        .bit_fields =
        {
            .cen      = 0x00,
            .udis     = 0x00,
            .urs      = 0x00,
            .opm      = 0x00,
            .arpe     = 0x00,
            .ckd      = 0x00,
            .uifremap = 0x00,
        },
    },

    .smcr =
    {
        .bit_fields =
        {
            .sms      = 0x00,
            .ts       = 0x00,
            .msm      = 0x00,
            .sms_msb  = 0x00,
        },
    },

    .dier =
    {
        .bit_fields =
        {
            .uie      = 0x00,
            .cc1ie    = 0x00,
            .cc2ie    = 0x00,
            .tie      = 0x00,
        },
    },

    .sr =
    {
        .bit_fields =
        {
            .uif      = 0x00,
            .cc1if    = 0x00,
            .cc2if    = 0x00,
            .tif      = 0x00,
            .cc1of    = 0x00,
            .cc2of    = 0x00,
        },
    },

    .egr =
    {
        .bit_fields =
        {
            .ug       = 0x00,
            .cc1g     = 0x00,
            .cc2g     = 0x00,
            .tg       = 0x00,
        },
    },

    .ccmr1 =
    {
        .out =
        {
            .bit_fields =
            {
                .cc1s     = 0x00,
                .oc1fe    = 0x00,
                .oc1pe    = 0x00,
                .oc1m     = 0x00,
                .cc2s     = 0x00,
                .oc2fe    = 0x00,
                .oc2pe    = 0x00,
                .oc2m     = 0x00,
                .oc1m_msb = 0x00,
                .oc2m_msb = 0x00,
            },
        },
    },

    .ccer =
    {
        .bit_fields =
        {
            .cc1e     = 0x00,
            .cc1p     = 0x00,
            .cc1np    = 0x00,
            .cc2e     = 0x00,
            .cc2p     = 0x00,
            .cc2np    = 0x00,
        },
    },

    .cnt =
    {
        .bit_fields =
        {
            .cnt      = 0x00,
            .uifcpy   = 0x00,
        },
    },

    .psc =
    {
        .bit_fields =
        {
            .psc      = 0x00,
        },
    },

    .arr =
    {
        .bit_fields =
        {
            .arr      = 0x0000,
        },
    },

    .ccr1 =
    {
        .bit_fields =
        {
            .ccr1     = 0x00,
        },
    },

    .ccr2 =
    {
        .bit_fields =
        {
            .ccr2     = 0x00,
        },
    },
};

tim_ctrl_res_t tim_ctrl_gpx_tim2345_init(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_gpx_tim2345_dev *dev = (struct tim_ctrl_gpx_tim2345_dev *)tim;

    dev->rmap->cr1.r  = dev->rtmp.cr1.r;
    dev->rmap->cr2.r  = dev->rtmp.cr2.r;
    dev->rmap->smcr.r = dev->rtmp.smcr.r;
    dev->rmap->dier.r = dev->rtmp.dier.r;
    dev->rmap->sr.r   = dev->rtmp.sr.r;
    dev->rmap->egr.r  = dev->rtmp.egr.r;

    if (dev->ccmr1_mode == TIM_CTRL_GPX_TIM2345_MODE_IN_CAP)
    {
        dev->rmap->ccmr1.in.r = dev->rtmp.ccmr1.in.r;
    }
    else
    {
        dev->rmap->ccmr1.out.r = dev->rtmp.ccmr1.out.r;
    }

    if (dev->ccmr2_mode == TIM_CTRL_GPX_TIM2345_MODE_IN_CAP)
    {
        dev->rmap->ccmr2.in.r = dev->rtmp.ccmr2.in.r;
    }
    else
    {
        dev->rmap->ccmr2.out.r = dev->rtmp.ccmr2.out.r;
    }

    dev->rmap->ccer.r = dev->rtmp.ccer.r;
    dev->rmap->cnt.r  = dev->rtmp.cnt.r;
    dev->rmap->psc.r  = dev->rtmp.psc.r;
    dev->rmap->arr.r  = dev->rtmp.arr.r;
    dev->rmap->ccr1.r = dev->rtmp.ccr1.r;
    dev->rmap->ccr2.r = dev->rtmp.ccr2.r;
    dev->rmap->ccr3.r = dev->rtmp.ccr3.r;
    dev->rmap->ccr4.r = dev->rtmp.ccr4.r;
    dev->rmap->dcr.r  = dev->rtmp.dcr.r;
    dev->rmap->dmar.r = dev->rtmp.dmar.r;

    switch(dev->id)
    {
        case TIM_CTRL_GPX_TIM2345_ID_2:
            dev->rmap->tim2_or.r = dev->rtmp.tim2_or.r;
            break;

        case TIM_CTRL_GPX_TIM2345_ID_5:
            dev->rmap->tim5_or.r = dev->rtmp.tim5_or.r;
            break;

        default:
            break;
    }

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim912_init(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_gpx_tim912_dev *dev = (struct tim_ctrl_gpx_tim912_dev *)tim;

    dev->rmap->cr1.r  = dev->rtmp.cr1.r;
    dev->rmap->smcr.r = dev->rtmp.smcr.r;
    dev->rmap->dier.r = dev->rtmp.dier.r;
    dev->rmap->sr.r   = dev->rtmp.sr.r;
    dev->rmap->egr.r  = dev->rtmp.egr.r;

    if (dev->ccmr1_mode == TIM_CTRL_GPX_TIM912_MODE_IN_CAP)
    {
        dev->rmap->ccmr1.in.r = dev->rtmp.ccmr1.in.r;
    }
    else
    {
        dev->rmap->ccmr1.out.r = dev->rtmp.ccmr1.out.r;
    }

    dev->rmap->ccer.r = dev->rtmp.ccer.r;
    dev->rmap->cnt.r  = dev->rtmp.cnt.r;
    dev->rmap->psc.r  = dev->rtmp.psc.r;
    dev->rmap->arr.r  = dev->rtmp.arr.r;
    dev->rmap->ccr1.r = dev->rtmp.ccr1.r;
    dev->rmap->ccr2.r = dev->rtmp.ccr2.r;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim2345_deinit(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_gpx_tim2345_dev *dev = (struct tim_ctrl_gpx_tim2345_dev *)tim;

    dev->rmap->cr1.r       = tim_ctrl_gpx_tim2345_por.cr1.r;
    dev->rmap->cr2.r       = tim_ctrl_gpx_tim2345_por.cr2.r;
    dev->rmap->smcr.r      = tim_ctrl_gpx_tim2345_por.smcr.r;
    dev->rmap->dier.r      = tim_ctrl_gpx_tim2345_por.dier.r;
    dev->rmap->sr.r        = tim_ctrl_gpx_tim2345_por.sr.r;
    dev->rmap->egr.r       = tim_ctrl_gpx_tim2345_por.egr.r;
    dev->rmap->ccmr1.out.r = tim_ctrl_gpx_tim2345_por.ccmr1.out.r;
    dev->rmap->ccmr2.out.r = tim_ctrl_gpx_tim2345_por.ccmr2.out.r;
    dev->rmap->ccer.r      = tim_ctrl_gpx_tim2345_por.ccer.r;
    dev->rmap->cnt.r       = tim_ctrl_gpx_tim2345_por.cnt.r;
    dev->rmap->psc.r       = tim_ctrl_gpx_tim2345_por.psc.r;
    dev->rmap->arr.r       = tim_ctrl_gpx_tim2345_por.arr.r;
    dev->rmap->ccr1.r      = tim_ctrl_gpx_tim2345_por.ccr1.r;
    dev->rmap->ccr2.r      = tim_ctrl_gpx_tim2345_por.ccr2.r;
    dev->rmap->ccr3.r      = tim_ctrl_gpx_tim2345_por.ccr3.r;
    dev->rmap->ccr4.r      = tim_ctrl_gpx_tim2345_por.ccr4.r;
    dev->rmap->dcr.r       = tim_ctrl_gpx_tim2345_por.dcr.r;
    dev->rmap->dmar.r      = tim_ctrl_gpx_tim2345_por.dmar.r;
    dev->rmap->tim2_or.r   = tim_ctrl_gpx_tim2345_por.tim2_or.r;
    dev->rmap->tim5_or.r   = tim_ctrl_gpx_tim2345_por.tim5_or.r;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim912_deinit(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_gpx_tim912_dev *dev = (struct tim_ctrl_gpx_tim912_dev *)tim;

    dev->rmap->cr1.r       = tim_ctrl_gpx_tim912_por.cr1.r;
    dev->rmap->smcr.r      = tim_ctrl_gpx_tim912_por.smcr.r;
    dev->rmap->dier.r      = tim_ctrl_gpx_tim912_por.dier.r;
    dev->rmap->sr.r        = tim_ctrl_gpx_tim912_por.sr.r;
    dev->rmap->egr.r       = tim_ctrl_gpx_tim912_por.egr.r;
    dev->rmap->ccmr1.out.r = tim_ctrl_gpx_tim912_por.ccmr1.out.r;
    dev->rmap->ccer.r      = tim_ctrl_gpx_tim912_por.ccer.r;
    dev->rmap->cnt.r       = tim_ctrl_gpx_tim912_por.cnt.r;
    dev->rmap->psc.r       = tim_ctrl_gpx_tim912_por.psc.r;
    dev->rmap->arr.r       = tim_ctrl_gpx_tim912_por.arr.r;
    dev->rmap->ccr1.r      = tim_ctrl_gpx_tim912_por.ccr1.r;
    dev->rmap->ccr2.r      = tim_ctrl_gpx_tim912_por.ccr2.r;

    return TIM_CTRL_RES_OK;
}
