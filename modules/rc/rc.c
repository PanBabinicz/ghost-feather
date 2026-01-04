#include "rc.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The RC devices array.
///
static struct rc_dev rc_dev_arr[RC_CH_TOTAL];

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief
///
static float32_t norm_asym_f32(const float32_t min, const float32_t max, const float32_t val);

///
/// \brief
///
static float32_t norm_sym_f32(const float32_t min, const float32_t max, const float32_t val);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static float32_t norm_asym_f32(const float32_t min, const float32_t max, const float32_t val)
{
    return ((val - min) / (max - min));
}

static float32_t norm_sym_f32(const float32_t min, const float32_t max, const float32_t val)
{
    return ((2 * ((val - min) / (max - min))) - 1);
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
struct rc_dev* rc_dev_arr_get(void)
{
    return &rc_dev_arr[0];
}

void rc_init(void)
{
    struct tim_dev *tim_dev_arr = tim_dev_arr_get();

    rc_dev_arr[RC_CH_1].tim = &tim_dev_arr[TIM_INST_12];
    rc_dev_arr[RC_CH_2].tim = &tim_dev_arr[TIM_INST_12];
    rc_dev_arr[RC_CH_3].tim = &tim_dev_arr[TIM_INST_8];
    rc_dev_arr[RC_CH_4].tim = &tim_dev_arr[TIM_INST_8];
    rc_dev_arr[RC_CH_5].tim = &tim_dev_arr[TIM_INST_8];
    rc_dev_arr[RC_CH_6].tim = &tim_dev_arr[TIM_INST_8];

    rc_dev_arr[RC_CH_1].ccr_ch = LL_TIM_CCR_CH1;
    rc_dev_arr[RC_CH_2].ccr_ch = LL_TIM_CCR_CH2;
    rc_dev_arr[RC_CH_3].ccr_ch = LL_TIM_CCR_CH1;
    rc_dev_arr[RC_CH_4].ccr_ch = LL_TIM_CCR_CH2;
    rc_dev_arr[RC_CH_5].ccr_ch = LL_TIM_CCR_CH3;
    rc_dev_arr[RC_CH_6].ccr_ch = LL_TIM_CCR_CH4;
}

void rc_sig_raw_gen(rc_ch_t ch)
{
    struct rc_dev *dev = &rc_dev_arr[ch];

    dev->tim->ccr_data_get(dev->tim->tim, dev->ccr_ch, &dev->ccr_data);

    if (dev->ccr_data.curr > dev->ccr_data.prev)
    {
        dev->sig.raw = ((dev->ccr_data.curr - dev->ccr_data.prev) < 2200) ? dev->ccr_data.curr - dev->ccr_data.prev
                     : dev->sig.raw;
    }
}

void rc_sig_norm(rc_ch_t ch)
{
    struct rc_dev *dev = &rc_dev_arr[ch];

    if (dev->sig.raw < 1000)
    {
        dev->sig.norm = 1000.0;
    }
    else if (dev->sig.raw > 2000)
    {
        dev->sig.norm = 2000.0;
    }
    else
    {
        dev->sig.norm = (float32_t)dev->sig.raw;
    }

    switch (ch)
    {
        case RC_CH_1:
            dev->sig.norm = norm_sym_f32(1000.0, 2000.0, dev->sig.norm);
            break;

        case RC_CH_2:
            dev->sig.norm = norm_sym_f32(1000.0, 2000.0, dev->sig.norm);
            break;

        case RC_CH_3:
            dev->sig.norm = norm_asym_f32(1000.0, 2000.0, dev->sig.norm);
            break;

        case RC_CH_4:
            dev->sig.norm = norm_sym_f32(1000.0, 2000.0, dev->sig.norm);
            break;

        case RC_CH_5:
            dev->sig.norm = norm_asym_f32(1000.0, 2000.0, dev->sig.norm);
            break;

        case RC_CH_6:
            dev->sig.norm = norm_asym_f32(1000.0, 2000.0, dev->sig.norm);
            break;
    }
}
