#include "rc.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The RC devices array.
///
static struct rc_dev rc_dev_arr[RC_CH_TOTAL];

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
