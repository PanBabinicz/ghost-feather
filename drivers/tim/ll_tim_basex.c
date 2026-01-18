#include "ll_tim_basex.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief Default register configuration for TIM6 and TIM7 after power-on reset.
///
/// This constant structure represents the expected reset (POR) state of the
/// base timer registers TIM6 and TIM7. It is used as a known-good baseline
/// for initialization and for restoring registers to their default values
/// before applying custom configuration.
///
static const struct ll_tim_base1_tim67_regs ll_tim_base1_tim67_por =
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
            .uifremap = 0x00,
        },
    },

    .cr2 =
    {
        .bf =
        {
            .mms  = 0x00,
        },
    },

    .dier =
    {
        .bf =
        {
            .uie   = 0x00,
            .ude   = 0x00,
        },
    },

    .sr =
    {
        .bf =
        {
            .uif   = 0x00,
        },
    },

    .egr =
    {
        .bf =
        {
            .ug   = 0x00,
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
};

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ll_tim_res_t ll_tim_base1_tim67_init(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_base1_tim67_dev *dev = (struct ll_tim_base1_tim67_dev *)tim;

    if (dev->stat == LL_TIM_STAT_INIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.r  = dev->rtmp.cr1.r;
    dev->rmap->cr2.r  = dev->rtmp.cr2.r;
    dev->rmap->dier.r = dev->rtmp.dier.r;
    dev->rmap->sr.r   = dev->rtmp.sr.r;
    dev->rmap->egr.r  = dev->rtmp.egr.r;
    dev->rmap->cnt.r  = dev->rtmp.cnt.r;
    dev->rmap->psc.r  = dev->rtmp.psc.r;
    dev->rmap->arr.r  = dev->rtmp.arr.r;

    dev->stat = LL_TIM_STAT_INIT;

    return LL_TIM_RES_OK;
}

ll_tim_res_t ll_tim_base1_tim67_deinit(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_base1_tim67_dev *dev = (struct ll_tim_base1_tim67_dev *)tim;

    if (dev->stat == LL_TIM_STAT_DEINIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.r  = ll_tim_base1_tim67_por.cr1.r;
    dev->rmap->cr2.r  = ll_tim_base1_tim67_por.cr2.r;
    dev->rmap->dier.r = ll_tim_base1_tim67_por.dier.r;
    dev->rmap->sr.r   = ll_tim_base1_tim67_por.sr.r;
    dev->rmap->egr.r  = ll_tim_base1_tim67_por.egr.r;
    dev->rmap->cnt.r  = ll_tim_base1_tim67_por.cnt.r;
    dev->rmap->psc.r  = ll_tim_base1_tim67_por.psc.r;
    dev->rmap->arr.r  = ll_tim_base1_tim67_por.arr.r;

    dev->stat = LL_TIM_STAT_DEINIT;

    return LL_TIM_RES_OK;
}

ll_tim_res_t ll_tim_base1_tim67_enable(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_base1_tim67_dev *dev = (struct ll_tim_base1_tim67_dev *)tim;

    if (dev->stat == LL_TIM_STAT_DEINIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.bf.cen = 0x01;

    return LL_TIM_RES_OK;
}

ll_tim_res_t ll_tim_base1_tim67_disable(void *tim)
{
    if (tim == NULL)
    {
        return LL_TIM_RES_ERR;
    }

    struct ll_tim_base1_tim67_dev *dev = (struct ll_tim_base1_tim67_dev *)tim;

    if (dev->stat == LL_TIM_STAT_DEINIT)
    {
        return LL_TIM_RES_ERR;
    }

    dev->rmap->cr1.bf.cen = 0x00;

    return LL_TIM_RES_OK;
}
