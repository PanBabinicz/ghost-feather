#include "tim_ctrl_gpx.h"

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
