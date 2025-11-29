#include "tim_ctrl.h"
#include "tim_ctrl_advx.h"
#include "tim_ctrl_basex.h"
#include "tim_ctrl_common.h"
#include "tim_ctrl_gpx.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief
///
struct tim_ctrl_dev
{
    void *tim;
    tim_ctrl_res_t (*init)(void *tim);
    tim_ctrl_res_t (*deinit)(void *tim);
    tim_ctrl_res_t (*enable)(void *tim);
    tim_ctrl_res_t (*disable)(void *tim);
};

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
    },
    .id         = TIM_CTRL_GPX_TIM912_ID_12,
    .ccmr1_mode = TIM_CTRL_GPX_TIM912_MODE_OUT_COMP,
    .stat       = false,
};

///
/// \brief
///
const struct tim_ctrl_dev tim_ctrl_dev_arr[] =
{
    [0] =
    {
        .tim     = &tim_ctrl_tim4_dev,
        .init    = &tim_ctrl_gpx_tim2345_init,
        .deinit  = &tim_ctrl_gpx_tim2345_deinit,
        .enable  = &tim_ctrl_gpx_tim2345_enable,
        .disable = &tim_ctrl_gpx_tim2345_disable,
    },

    [1] =
    {
        .tim     = &tim_ctrl_tim12_dev,
        .init    = &tim_ctrl_gpx_tim912_init,
        .deinit  = &tim_ctrl_gpx_tim912_deinit,
        .enable  = &tim_ctrl_gpx_tim912_enable,
        .disable = &tim_ctrl_gpx_tim912_disable,
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
/// RFCH1  -> TIM8_CH4  (PC9)   adv4
/// RFCH2  -> TIM8_CH3  (PC8)   adv4
/// RFCH3  -> TIM8_CH2  (PC7)   adv4
/// RFCH4  -> TIM8_CH1  (PC6)   adv4
/// RFCH5  -> TIM12_CH2 (PB15)  gp2
/// RFCH6  -> TIM12_CH1 (PB14)  gp2
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
///

void tim_ctrl_init(void)
{
    for (uint32_t i = 0; i < sizeof(tim_ctrl_dev_arr)/sizeof(tim_ctrl_dev_arr[0]); i++)
    {
        tim_ctrl_dev_arr[i].init(tim_ctrl_dev_arr[i].tim);
        tim_ctrl_dev_arr[i].enable(tim_ctrl_dev_arr[i].tim);
    }
}
