#include "rf_ctrl.h"
#include <string.h>

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief
///
static struct rf_ctrl_dev rf_ctrl_dev_arr[RF_CTRL_CH_TOTAL];

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
struct rf_ctrl_dev* rf_ctrl_dev_arr_get(void)
{
    return &rf_ctrl_dev_arr[0];
}

void rf_ctrl_init(void)
{
    struct tim_ctrl_dev *tim_ctrl_dev_arr = tim_ctrl_dev_arr_get();

    rf_ctrl_dev_arr[RF_CTRL_CH_0].tim = &tim_ctrl_dev_arr[TIM_CTRL_INST_TIM12];
    rf_ctrl_dev_arr[RF_CTRL_CH_1].tim = &tim_ctrl_dev_arr[TIM_CTRL_INST_TIM12];
    rf_ctrl_dev_arr[RF_CTRL_CH_2].tim = &tim_ctrl_dev_arr[TIM_CTRL_INST_TIM8];
    rf_ctrl_dev_arr[RF_CTRL_CH_3].tim = &tim_ctrl_dev_arr[TIM_CTRL_INST_TIM8];
    rf_ctrl_dev_arr[RF_CTRL_CH_4].tim = &tim_ctrl_dev_arr[TIM_CTRL_INST_TIM8];
    rf_ctrl_dev_arr[RF_CTRL_CH_5].tim = &tim_ctrl_dev_arr[TIM_CTRL_INST_TIM8];

    rf_ctrl_dev_arr[RF_CTRL_CH_0].ccr_ch = TIM_CTRL_INST_CCR1;
    rf_ctrl_dev_arr[RF_CTRL_CH_1].ccr_ch = TIM_CTRL_INST_CCR2;
    rf_ctrl_dev_arr[RF_CTRL_CH_2].ccr_ch = TIM_CTRL_INST_CCR1;
    rf_ctrl_dev_arr[RF_CTRL_CH_3].ccr_ch = TIM_CTRL_INST_CCR2;
    rf_ctrl_dev_arr[RF_CTRL_CH_4].ccr_ch = TIM_CTRL_INST_CCR3;
    rf_ctrl_dev_arr[RF_CTRL_CH_5].ccr_ch = TIM_CTRL_INST_CCR4;
}

rf_ctrl_res_t rf_ctrl_ccr_data_get(struct rf_ctrl_dev *const dev, struct tim_ctrl_ccr_data *const ccr_data)
{
    if ((dev == NULL) || (ccr_data == NULL))
    {
        return RF_CTRL_RES_ERR;
    }

    dev->tim->ccr_data_get(dev->tim->tim, dev->ccr_ch, ccr_data);

    return RF_CTRL_RES_OK;
}
