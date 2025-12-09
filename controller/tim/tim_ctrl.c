#include "tim_ctrl.h"
#include "tim_ctrl_advx.h"
#include "tim_ctrl_basex.h"
#include "tim_ctrl_common.h"
#include "tim_ctrl_gpx.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief
///
static struct tim_ctrl_gpx_tim2345_dev tim_ctrl_tim4_dev =
{
    .rmap = (volatile struct tim_ctrl_gpx_tim2345_regs *)(0x40000800),
    .rtmp =
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
                    .oc1m     = TIM_CTRL_GPX_TIM2345_OC_MODE_PWM1,
                    .oc1ce    = 0x00,
                    .cc2s     = 0x00,
                    .oc2fe    = 0x00,
                    .oc2pe    = 0x00,
                    .oc2m     = TIM_CTRL_GPX_TIM2345_OC_MODE_PWM1,
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
                    .oc3m     = TIM_CTRL_GPX_TIM2345_OC_MODE_PWM1,
                    .oc3ce    = 0x00,
                    .cc4s     = 0x00,
                    .oc4fe    = 0x00,
                    .oc4pe    = 0x00,
                    .oc4m     = TIM_CTRL_GPX_TIM2345_OC_MODE_PWM1,
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
                .cc1e  = 0x01,
                .cc1p  = 0x00,
                .cc1np = 0x00,
                .cc2e  = 0x01,
                .cc2p  = 0x00,
                .cc2np = 0x00,
                .cc3e  = 0x01,
                .cc3p  = 0x00,
                .cc3np = 0x00,
                .cc4e  = 0x01,
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
                .psc = 0x6b,
            },
        },

        .arr =
        {
            .bf =
            {
                .arr = 0x4844,
            },
        },

        .ccr1 =
        {
            .bf =
            {
                .ccr1 = 0x05dc,
            },
        },

        .ccr2 =
        {
            .bf =
            {
                .ccr2 = 0x05dc,
            },
        },

        .ccr3 =
        {
            .bf =
            {
                .ccr3 = 0x05dc,
            },
        },

        .ccr4 =
        {
            .bf =
            {
                .ccr4 = 0x05dc,
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
    },
    .id         = TIM_CTRL_GPX_TIM2345_ID_4,
    .ccmr1_mode = TIM_CTRL_GPX_TIM2345_MODE_OUT_COMP,
    .ccmr2_mode = TIM_CTRL_GPX_TIM2345_MODE_OUT_COMP,
    .stat       = false,
};

///
/// \brief
///
static struct tim_ctrl_gpx_tim912_dev tim_ctrl_tim12_dev =
{
    .rmap = (volatile struct tim_ctrl_gpx_tim912_regs *)(0x40001800),
    .rtmp =
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
                .cc1ie = 0x01,
                .cc2ie = 0x01,
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
            .in =
            {
                .bf =
                {
                    .cc1s   = 0x01,
                    .ic1psc = 0x00,
                    .ic1f   = 0x00,
                    .cc2s   = 0x01,
                    .ic2psc = 0x00,
                    .ic2f   = 0x00,
                },
            },
        },

        .ccer =
        {
            .bf =
            {
                .cc1e  = 0x01,
                .cc1p  = 0x01,
                .cc1np = 0x01,
                .cc2e  = 0x01,
                .cc2p  = 0x01,
                .cc2np = 0x01,
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
                .psc = 0x6b,
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
    },
    .id         = TIM_CTRL_GPX_TIM912_ID_12,
    .ccmr1_mode = TIM_CTRL_GPX_TIM912_MODE_IN_CAP,
    .stat       = false,
};

static struct tim_ctrl_adv6_tim18_dev tim_ctrl_tim8_dev =
{
    .rmap = (volatile struct tim_ctrl_adv6_tim18_regs *)(0x40010400),
    .rtmp =
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
                .cc1ie = 0x01,
                .cc2ie = 0x01,
                .cc3ie = 0x01,
                .cc4ie = 0x01,
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
            .in =
            {
                .bf =
                {
                    .cc1s   = 0x01,
                    .ic1psc = 0x00,
                    .ic1f   = 0x00,
                    .cc2s   = 0x01,
                    .ic2psc = 0x00,
                    .ic2f   = 0x00,
                },
            },
        },

        .ccmr2 =
        {
            .in =
            {
                .bf =
                {
                    .cc3s   = 0x01,
                    .ic3psc = 0x00,
                    .ic3f   = 0x00,
                    .cc4s   = 0x01,
                    .ic4psc = 0x00,
                    .ic4f   = 0x00,
                },
            },
        },

        .ccer =
        {
            .bf =
            {
                .cc1e  = 0x01,
                .cc1p  = 0x01,
                .cc1ne = 0x00,
                .cc1np = 0x01,
                .cc2e  = 0x01,
                .cc2p  = 0x01,
                .cc2ne = 0x00,
                .cc2np = 0x01,
                .cc3e  = 0x01,
                .cc3p  = 0x01,
                .cc3ne = 0x00,
                .cc3np = 0x01,
                .cc4e  = 0x01,
                .cc4p  = 0x01,
                .cc4np = 0x01,
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
                .psc = 0xd7,
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
    },
    .id         = TIM_CTRL_ADV6_TIM18_ID_8,
    .ccmr1_mode = TIM_CTRL_ADV6_TIM18_MODE_IN_CAP,
    .ccmr2_mode = TIM_CTRL_ADV6_TIM18_MODE_IN_CAP,
    .stat       = false,
};

///
/// \brief
///
static const struct tim_ctrl_dev tim_ctrl_dev_arr[TIM_CTRL_INST_TOTAL] =
{
    [TIM_CTRL_INST_TIM4] =
    {
        .tim     = &tim_ctrl_tim4_dev,
        .init    = &tim_ctrl_gpx_tim2345_init,
        .deinit  = &tim_ctrl_gpx_tim2345_deinit,
        .enable  = &tim_ctrl_gpx_tim2345_enable,
        .disable = &tim_ctrl_gpx_tim2345_disable,
    },

    [TIM_CTRL_INST_TIM12] =
    {
        .tim      = &tim_ctrl_tim12_dev,
        .init     = &tim_ctrl_gpx_tim912_init,
        .deinit   = &tim_ctrl_gpx_tim912_deinit,
        .enable   = &tim_ctrl_gpx_tim912_enable,
        .disable  = &tim_ctrl_gpx_tim912_disable,
    },

    [TIM_CTRL_INST_TIM8] =
    {
        .tim      = &tim_ctrl_tim8_dev,
        .init     = &tim_ctrl_adv6_tim18_init,
        .deinit   = &tim_ctrl_adv6_tim18_deinit,
        .enable   = &tim_ctrl_adv6_tim18_enable,
        .disable  = &tim_ctrl_adv6_tim18_disable,
    },
};

///
/// Used timers inside ghost feather system:
///
/// MOTOR0 -> TIM4_CH4  (PB9)   gp4_16
/// MOTOR1 -> TIM4_CH3  (PB8)   gp4_16
/// MOTOR2 -> TIM4_CH2  (PB7)   gp4_16
/// MOTOR3 -> TIM4_CH1  (PB6)   gp4_16
///
/// RFCH1  -> TIM12_CH1 (PB14)  gp2
/// RFCH2  -> TIM12_CH2 (PB15)  gp2
/// RFCH3  -> TIM8_CH1  (PC6)   adv4
/// RFCH4  -> TIM8_CH2  (PC7)   adv4
/// RFCH5  -> TIM8_CH3  (PC8)   adv4
/// RFCH6  -> TIM8_CH4  (PC9)   adv4
///
///  ----------------------------
/// |                    BAT |*+-|
/// |                    CH6 |s+-|  --> SWB
/// |                    CH5 |s+-|  --> SWA
/// |   FLYSKY FS-R6B    CH4 |s+-|
/// |                    CH3 |s+-|
/// |                    CH2 |s+-|
/// |                    CH1 |s+-|
///  ----------------------------

struct tim_ctrl_dev* tim_ctrl_dev_get(tim_ctrl_inst_t inst)
{
    if ((inst < TIM_CTRL_INST_BEGIN) || (inst >= TIM_CTRL_INST_TOTAL))
    {
        return NULL;
    }

    return &tim_ctrl_dev_arr[inst];
}

void tim_ctrl_init(void)
{
    for (uint32_t i = 0; i < sizeof(tim_ctrl_dev_arr)/sizeof(tim_ctrl_dev_arr[TIM_CTRL_INST_BEGIN]); i++)
    {
        tim_ctrl_dev_arr[i].init(tim_ctrl_dev_arr[i].tim);
        tim_ctrl_dev_arr[i].enable(tim_ctrl_dev_arr[i].tim);
    }
}
