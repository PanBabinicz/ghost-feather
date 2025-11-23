#ifndef _TIM_CTRL_COMMON_H
#define _TIM_CTRL_COMMON_H

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
/// \breif The TIM controller status type.
///
typedef enum tim_ctrl_stat
{
    TIM_CTRL_STAT_DEINIT = 0,
    TIM_CTRL_STAT_INIT,
} tim_ctrl_stat_t;

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_COMMON_H */
