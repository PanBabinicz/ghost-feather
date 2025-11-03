#ifndef _TIM_CTRL_H
#define _TIM_CTRL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \breif The TIM controller result type.
///
typedef enum tim_ctrl_res
{
    TIM_CTRL_RES_OK = 0,
    TIM_CTRL_RES_ERR,
} tim_ctrl_res_t;

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_dev_init();

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_dev_deinit();

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_H */
