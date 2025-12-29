#ifndef _RF_CTRL_H
#define _RF_CTRL_H

#include <stdint.h>
#include "tim_ctrl.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
typedef enum rf_ctrl_res
{
    RF_CTRL_RES_OK = 0,
    RF_CTRL_RES_ERR,
} rf_ctrl_res_t;

///
/// \brief
///
typedef enum rf_ctrl_ch
{
    RF_CTRL_CH_BEGIN = 0,
    RF_CTRL_CH_0 = 0,
    RF_CTRL_CH_1,
    RF_CTRL_CH_2,
    RF_CTRL_CH_3,
    RF_CTRL_CH_4,
    RF_CTRL_CH_5,
    RF_CTRL_CH_TOTAL,
} rf_ctrl_ch_t;

///
/// \brief
///
struct rf_ctrl_dev
{
    struct tim_ctrl_dev *tim;
    tim_ctrl_inst_ccr_t ccr_ch;
};

///
/// \brief
///
struct rf_ctrl_dev* rf_ctrl_dev_arr_get(void);

///
/// \brief
///
void rf_ctrl_init(void);

///
/// \brief
///
rf_ctrl_res_t rf_ctrl_ccr_data_get(struct rf_ctrl_dev *const dev, struct tim_ctrl_ccr_data *const ccr_data);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _RF_CTRL_H */
