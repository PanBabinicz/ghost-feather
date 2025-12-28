#include "tim_ctrl_gpx.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief Default register configuration for TIM2–TIM5 after power-on reset.
///
/// This constant structure represents the expected reset (POR) state of the
/// general-purpose timer registers TIM2, TIM3, TIM4, and TIM5. It is used as a
/// known-good baseline for initialization and for restoring registers to their
/// default values before applying custom configuration.
///
static const struct tim_ctrl_gpx_tim2345_regs tim_ctrl_gpx_tim2345_por =
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
            .ccds = 0x00,
            .mms  = 0x00,
            .ti1s = 0x00,
        },
    },

    .smcr =
    {
        .bf =
        {
            .sms     = 0x00,
            .occs    = 0x00,
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
            .tie   = 0x00,
            .ude   = 0x00,
            .cc1de = 0x00,
            .cc2de = 0x00,
            .cc3de = 0x00,
            .cc4de = 0x00,
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
            .tif   = 0x00,
            .cc1of = 0x00,
            .cc2of = 0x00,
            .cc3of = 0x00,
            .cc4of = 0x00,
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
            .tg   = 0x00,
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
            .cc1np = 0x00,
            .cc2e  = 0x00,
            .cc2p  = 0x00,
            .cc2np = 0x00,
            .cc3e  = 0x00,
            .cc3p  = 0x00,
            .cc3np = 0x00,
            .cc4e  = 0x00,
            .cc4p  = 0x00,
            .cc4np = 0x00,
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

    .tim2_or =
    {
        .bf =
        {
            .itr1_rmp = 0x00,
        },
    },

    .tim5_or =
    {
        .bf =
        {
            .ti4_rmp = 0x00,
        },
    },
};

///
/// \brief Default register configuration for TIM9 and TIM12 after power-on reset.
///
/// This constant structure represents the expected reset (POR) state of the
/// general-purpose timer registers TIM9 and TIM12. It is used as a known-good
/// baseline for initialization and for restoring registers to their
/// default values before applying custom configuration.
///
static const struct tim_ctrl_gpx_tim912_regs tim_ctrl_gpx_tim912_por =
{
    .cr1 =
    {
        .bf =
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
        .bf =
        {
            .sms     = 0x00,
            .ts      = 0x00,
            .msm     = 0x00,
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
            .tie   = 0x00,
        },
    },

    .sr =
    {
        .bf =
        {
            .uif   = 0x00,
            .cc1if = 0x00,
            .cc2if = 0x00,
            .tif   = 0x00,
            .cc1of = 0x00,
            .cc2of = 0x00,
        },
    },

    .egr =
    {
        .bf =
        {
            .ug   = 0x00,
            .cc1g = 0x00,
            .cc2g = 0x00,
            .tg   = 0x00,
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
        .bf =
        {
            .cc1e  = 0x00,
            .cc1p  = 0x00,
            .cc1np = 0x00,
            .cc2e  = 0x00,
            .cc2p  = 0x00,
            .cc2np = 0x00,
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
            .arr = 0x00,
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
};


///
/// \brief Default register configuration for TIM10–TIM14 after power-on reset.
///
/// This constant structure represents the expected reset (POR) state of the
/// general-purpose timer registers TIM10, TIM11, TIM13, and TIM14. It is used as a
/// known-good baseline for initialization and for restoring registers to their
/// default values before applying custom configuration.
///
static const struct tim_ctrl_gpx_tim10111314_regs tim_ctrl_gpx_tim10111314_por =
{
    .cr1 =
    {
        .bf =
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

    .dier =
    {
        .bf =
        {
            .uie   = 0x00,
            .cc1ie = 0x00,
        },
    },

    .sr =
    {
        .bf =
        {
            .uif   = 0x00,
            .cc1if = 0x00,
            .cc1of = 0x00,
        },
    },

    .egr =
    {
        .bf =
        {
            .ug   = 0x00,
            .cc1g = 0x00,
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
                .oc1m_msb = 0x00,
            },
        },
    },

    .ccer =
    {
        .bf =
        {
            .cc1e  = 0x00,
            .cc1p  = 0x00,
            .cc1np = 0x00,
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
            .arr = 0x00,
        },
    },

    .ccr1 =
    {
        .bf =
        {
            .ccr1 = 0x00,
        },
    },

    .tim11_or =
    {
        .bf =
        {
            .ti1_rmp = 0x00,
        }
    }
};

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
/// TODO
/// \brief Initializes the general-purpose timer (TIM2-TIM5).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim2345_init(void *tim);

/// TODO
/// \brief Initializes the general-purpose timer (TIM9 and TIM12).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim912_init(void *tim);

/// TODO
/// \brief Initializes the general-purpose timer (TIM10-TIM14).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim10111314_init(void *tim);

/// TODO
/// \brief Deinitializes the general-purpose timer (TIM2-TIM5).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim2345_deinit(void *tim);

/// TODO
/// \brief Deinitializes the general-purpose timer (TIM9 and TIM12).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim912_deinit(void *tim);

/// TODO
/// \brief Deinitializes the general-purpose timer (TIM10-TIM14).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_gpx_tim10111314_deinit(void *tim);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
tim_ctrl_res_t tim_ctrl_gpx_tim2345_init(void *tim)
{
    struct tim_ctrl_gpx_tim2345_dev *dev = (struct tim_ctrl_gpx_tim2345_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_INIT)
    {
        return TIM_CTRL_RES_ERR;
    }

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

    switch (dev->id)
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

    dev->stat = TIM_CTRL_STAT_INIT;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim912_init(void *tim)
{
    struct tim_ctrl_gpx_tim912_dev *dev = (struct tim_ctrl_gpx_tim912_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_INIT)
    {
        return TIM_CTRL_RES_ERR;
    }

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

    dev->stat = TIM_CTRL_STAT_INIT;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim10111314_init(void *tim)
{
    struct tim_ctrl_gpx_tim10111314_dev *dev = (struct tim_ctrl_gpx_tim10111314_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_INIT)
    {
        return TIM_CTRL_RES_ERR;
    }

    dev->rmap->cr1.r  = dev->rtmp.cr1.r;
    dev->rmap->dier.r = dev->rtmp.dier.r;
    dev->rmap->sr.r   = dev->rtmp.sr.r;
    dev->rmap->egr.r  = dev->rtmp.egr.r;

    if (dev->ccmr1_mode == TIM_CTRL_GPX_TIM10111314_MODE_IN_CAP)
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

    switch (dev->id)
    {
        case TIM_CTRL_GPX_TIM10111314_ID_11:
            dev->rmap->tim11_or.r = dev->rtmp.tim11_or.r;
            break;

        default:
            break;
    }

    dev->stat = TIM_CTRL_STAT_INIT;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim2345_deinit(void *tim)
{
    struct tim_ctrl_gpx_tim2345_dev *dev = (struct tim_ctrl_gpx_tim2345_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_DEINIT)
    {
        return TIM_CTRL_RES_ERR;
    }

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

    dev->stat = TIM_CTRL_STAT_DEINIT;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim912_deinit(void *tim)
{
    struct tim_ctrl_gpx_tim912_dev *dev = (struct tim_ctrl_gpx_tim912_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_DEINIT)
    {
        return TIM_CTRL_RES_ERR;
    }

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

    dev->stat = TIM_CTRL_STAT_DEINIT;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_tim10111314_deinit(void *tim)
{
    struct tim_ctrl_gpx_tim10111314_dev *dev = (struct tim_ctrl_gpx_tim10111314_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_DEINIT)
    {
        return TIM_CTRL_RES_ERR;
    }

    dev->rmap->cr1.r       = tim_ctrl_gpx_tim10111314_por.cr1.r;
    dev->rmap->dier.r      = tim_ctrl_gpx_tim10111314_por.dier.r;
    dev->rmap->sr.r        = tim_ctrl_gpx_tim10111314_por.sr.r;
    dev->rmap->egr.r       = tim_ctrl_gpx_tim10111314_por.egr.r;
    dev->rmap->ccmr1.out.r = tim_ctrl_gpx_tim10111314_por.ccmr1.out.r;
    dev->rmap->ccer.r      = tim_ctrl_gpx_tim10111314_por.ccer.r;
    dev->rmap->cnt.r       = tim_ctrl_gpx_tim10111314_por.cnt.r;
    dev->rmap->psc.r       = tim_ctrl_gpx_tim10111314_por.psc.r;
    dev->rmap->arr.r       = tim_ctrl_gpx_tim10111314_por.arr.r;
    dev->rmap->ccr1.r      = tim_ctrl_gpx_tim10111314_por.ccr1.r;

    switch(dev->id)
    {
        case TIM_CTRL_GPX_TIM10111314_ID_11:
            dev->rmap->tim11_or.r = tim_ctrl_gpx_tim10111314_por.tim11_or.r;
            break;

        default:
            break;
    }

    dev->stat = TIM_CTRL_STAT_DEINIT;

    return TIM_CTRL_RES_OK;
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
tim_ctrl_res_t tim_ctrl_gpx_timx_init(void *tim, void *inst)
{
    if ((tim == NULL) || (inst == NULL))
    {
        return TIM_CTRL_RES_ERR;
    }

    switch (*(tim_ctrl_gpx_tim_inst_t *)inst)
    {
        case TIM_CTRL_GPX_TIM2345:
            return tim_ctrl_gpx_tim2345_init(tim);

        case TIM_CTRL_GPX_TIM912:
            return tim_ctrl_gpx_tim912_init(tim);

        case TIM_CTRL_GPX_TIM10111314:
            return tim_ctrl_gpx_tim10111314_init(tim);

        default:
            return TIM_CTRL_RES_ERR;
    }
}

tim_ctrl_res_t tim_ctrl_gpx_timx_deinit(void *tim, void *inst)
{
    if ((tim == NULL) || (inst == NULL))
    {
        return TIM_CTRL_RES_ERR;
    }

    switch (*(tim_ctrl_gpx_tim_inst_t *)inst)
    {
        case TIM_CTRL_GPX_TIM2345:
            return tim_ctrl_gpx_tim2345_deinit(tim);

        case TIM_CTRL_GPX_TIM912:
            return tim_ctrl_gpx_tim912_deinit(tim);

        case TIM_CTRL_GPX_TIM10111314:
            return tim_ctrl_gpx_tim10111314_deinit(tim);

        default:
            return TIM_CTRL_RES_ERR;
    }
}

tim_ctrl_res_t tim_ctrl_gpx_timx_enable(void *tim, void *inst)
{
    if ((tim == NULL) || (inst == NULL))
    {
        return TIM_CTRL_RES_ERR;
    }

    switch (*(tim_ctrl_gpx_tim_inst_t *)inst)
    {
        case TIM_CTRL_GPX_TIM2345:
            struct tim_ctrl_gpx_tim2345_dev *tim2345 = (struct tim_ctrl_gpx_tim2345_dev *)tim;
            tim2345->rmap->cr1.bf.cen = 0x01;
            break;

        case TIM_CTRL_GPX_TIM912:
            struct tim_ctrl_gpx_tim912_dev *tim912 = (struct tim_ctrl_gpx_tim912_dev *)tim;
            tim912->rmap->cr1.bf.cen = 0x01;
            break;

        case TIM_CTRL_GPX_TIM10111314:
            struct tim_ctrl_gpx_tim10111314_dev *tim10111314 = (struct tim_ctrl_gpx_tim10111314_dev *)tim;
            tim10111314->rmap->cr1.bf.cen = 0x01;
            break;

        default:
            return TIM_CTRL_RES_ERR;
    }

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_timx_disable(void *tim, void *inst)
{
    if ((tim == NULL) || (inst == NULL))
    {
        return TIM_CTRL_RES_ERR;
    }

    switch (*(tim_ctrl_gpx_tim_inst_t *)inst)
    {
        case TIM_CTRL_GPX_TIM2345:
            struct tim_ctrl_gpx_tim2345_dev *tim2345 = (struct tim_ctrl_gpx_tim2345_dev *)tim;
            tim2345->rmap->cr1.bf.cen = 0x00;
            break;

        case TIM_CTRL_GPX_TIM912:
            struct tim_ctrl_gpx_tim912_dev *tim912 = (struct tim_ctrl_gpx_tim912_dev *)tim;
            tim912->rmap->cr1.bf.cen = 0x00;
            break;

        case TIM_CTRL_GPX_TIM10111314:
            struct tim_ctrl_gpx_tim10111314_dev *tim10111314 = (struct tim_ctrl_gpx_tim10111314_dev *)tim;
            tim10111314->rmap->cr1.bf.cen = 0x00;
            break;

        default:
            return TIM_CTRL_RES_ERR;
    }

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_timx_ccr_data_get(void *tim, void *inst, struct tim_ctrl_ccr_data **ccr_data)
{
    if ((tim == NULL) || (inst == NULL) || (ccr_data == NULL))
    {
        return TIM_CTRL_RES_ERR;
    }

    switch (*(tim_ctrl_gpx_tim_inst_t *)inst)
    {
        case TIM_CTRL_GPX_TIM2345:
            struct tim_ctrl_gpx_tim2345_dev *tim2345 = (struct tim_ctrl_gpx_tim2345_dev *)tim;
            *ccr_data = &tim2345->ccr_data[0];
            break;

        case TIM_CTRL_GPX_TIM912:
            struct tim_ctrl_gpx_tim912_dev *tim912 = (struct tim_ctrl_gpx_tim912_dev *)tim;
            *ccr_data = &tim912->ccr_data[0];
            break;

        case TIM_CTRL_GPX_TIM10111314:
            struct tim_ctrl_gpx_tim10111314_dev *tim10111314 = (struct tim_ctrl_gpx_tim10111314_dev *)tim;
            *ccr_data = &tim10111314->ccr_data[0];
            break;

        default:
            return TIM_CTRL_RES_ERR;
    }

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_gpx_timx_ccr_set(void *tim, void *inst, tim_ctrl_inst_ccr_t ch, uint32_t ccr)
{
    if ((tim == NULL) || (inst == NULL))
    {
        return TIM_CTRL_RES_ERR;
    }

    switch (*(tim_ctrl_gpx_tim_inst_t *)inst)
    {
        case TIM_CTRL_GPX_TIM2345:
            struct tim_ctrl_gpx_tim2345_dev *tim2345 = (struct tim_ctrl_gpx_tim2345_dev *)tim;
            volatile uint32_t *ccr2345 = (ch == TIM_CTRL_INST_CCR1) ? &tim2345->rmap->ccr1.r
                                       : (ch == TIM_CTRL_INST_CCR2) ? &tim2345->rmap->ccr2.r
                                       : (ch == TIM_CTRL_INST_CCR3) ? &tim2345->rmap->ccr3.r
                                       : (ch == TIM_CTRL_INST_CCR4) ? &tim2345->rmap->ccr4.r : NULL;

            if (ccr2345 == NULL)
            {
                return  TIM_CTRL_RES_ERR;
            }

            *ccr2345 = ccr;
            break;

        case TIM_CTRL_GPX_TIM912:
            struct tim_ctrl_gpx_tim912_dev *tim912 = (struct tim_ctrl_gpx_tim912_dev *)tim;
            volatile uint32_t *ccr912 = (ch == TIM_CTRL_INST_CCR1) ? &tim912->rmap->ccr1.r
                                      : (ch == TIM_CTRL_INST_CCR2) ? &tim912->rmap->ccr2.r : NULL;

            if (ccr912 == NULL)
            {
                return  TIM_CTRL_RES_ERR;
            }

            *ccr912 = (ccr & 0x0000ffff);
            break;

        case TIM_CTRL_GPX_TIM10111314:
            struct tim_ctrl_gpx_tim10111314_dev *tim10111314 = (struct tim_ctrl_gpx_tim10111314_dev *)tim;
            volatile uint32_t *ccr10111314 = (ch == TIM_CTRL_INST_CCR1) ? &tim10111314->rmap->ccr1.r : NULL;

            if (ccr10111314 == NULL)
            {
                return  TIM_CTRL_RES_ERR;
            }

            *ccr10111314 = (ccr & 0x0000ffff);
            break;

        default:
            return TIM_CTRL_RES_ERR;
    }

    return TIM_CTRL_RES_OK;
}
