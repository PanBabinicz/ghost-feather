#include "tim_ctrl_basex.h"

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
static const struct tim_ctrl_base1_tim67_regs tim_ctrl_base1_tim67_por =
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
tim_ctrl_res_t tim_ctrl_base1_timx_init(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_base1_timx_dev *dev = (struct tim_ctrl_base1_timx_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_INIT)
    {
        return TIM_CTRL_RES_ERR;
    }

    dev->rmap->cr1.r  = dev->rtmp.cr1.r;
    dev->rmap->cr2.r  = dev->rtmp.cr2.r;
    dev->rmap->dier.r = dev->rtmp.dier.r;
    dev->rmap->sr.r   = dev->rtmp.sr.r;
    dev->rmap->egr.r  = dev->rtmp.egr.r;
    dev->rmap->cnt.r  = dev->rtmp.cnt.r;
    dev->rmap->psc.r  = dev->rtmp.psc.r;
    dev->rmap->arr.r  = dev->rtmp.arr.r;

    dev->stat = TIM_CTRL_STAT_INIT;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_base1_timx_deinit(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_base1_timx_dev *dev = (struct tim_ctrl_base1_timx_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_DEINIT)
    {
        return TIM_CTRL_RES_ERR;
    }

    dev->rmap->cr1.r  = tim_ctrl_base1_timx_por.cr1.r;
    dev->rmap->cr2.r  = tim_ctrl_base1_timx_por.cr2.r;
    dev->rmap->dier.r = tim_ctrl_base1_timx_por.dier.r;
    dev->rmap->sr.r   = tim_ctrl_base1_timx_por.sr.r;
    dev->rmap->egr.r  = tim_ctrl_base1_timx_por.egr.r;
    dev->rmap->cnt.r  = tim_ctrl_base1_timx_por.cnt.r;
    dev->rmap->psc.r  = tim_ctrl_base1_timx_por.psc.r;
    dev->rmap->arr.r  = tim_ctrl_base1_timx_por.arr.r;

    dev->stat = TIM_CTRL_STAT_DEINIT;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_base1_timx_enable(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_base1_timx_dev *dev = (struct tim_ctrl_base1_timx_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_DEINIT)
    {
        return TIM_CTRL_RES_ERR;
    }

    dev->rmap->cr1.bf.cen = 0x01;

    return TIM_CTRL_RES_OK;
}

tim_ctrl_res_t tim_ctrl_base1_timx_disable(void *tim)
{
    if (tim == NULL)
    {
        return TIM_CTRL_RES_ERR;
    }

    struct tim_ctrl_base1_timx_dev *dev = (struct tim_ctrl_base1_timx_dev *)tim;

    if (dev->stat == TIM_CTRL_STAT_DEINIT)
    {
        return TIM_CTRL_RES_ERR;
    }

    dev->rmap->cr1.bf.cen = 0x00;

    return TIM_CTRL_RES_OK;
}
