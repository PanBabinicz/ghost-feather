#ifndef _TIM_CTRL_BASE_H
#define _TIM_CTRL_BASE_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "tim_ctrl_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
typedef enum tim_ctrl_base1_timx_id
{
    TIM_CTRL_BASE1_TIMX_ID_6 = 0,
    TIM_CTRL_BASE1_TIMX_ID_7,
} tim_ctrl_base1_timx_id_t;

///
/// \brief
///
union tim_ctrl_base1_timx_cr1
{
    uint32_t r;
    struct
    {
        uint32_t cen      : 1;
        uint32_t udis     : 1;
        uint32_t urs      : 1;
        uint32_t opm      : 1;
        uint32_t          : 3;
        uint32_t arpe     : 1;
        uint32_t          : 3;
        uint32_t uifremap : 1;
        uint32_t          : 20;
    } bf;
};

///
/// \brief
///
union tim_ctrl_base1_timx_cr2
{
    uint32_t r;
    struct
    {
        uint32_t     : 4;
        uint32_t mms : 3;
        uint32_t     : 25;
    } bf;
};

///
/// \brief
///
union tim_ctrl_base1_timx_dier
{
    uint32_t r;
    struct
    {
        uint32_t uie : 1;
        uint32_t     : 7;
        uint32_t ude : 1;
        uint32_t     : 23;
    } bf;
};

///
/// \brief
///
union tim_ctrl_base1_timx_sr
{
    uint32_t r;
    struct
    {
        uint32_t uif : 1;
        uint32_t     : 31;
    } bf;
};

///
/// \brief
///
union tim_ctrl_base1_timx_egr
{
    uint32_t r;
    struct
    {
        uint32_t ug : 1;
        uint32_t    : 31;
    } bf;
};

///
/// \brief
///
union tim_ctrl_base1_timx_cnt
{
    uint32_t r;
    struct
    {
        uint32_t cnt    : 16;
        uint32_t        : 15;
        uint32_t uifcpy : 1;
    } bf;
};

///
/// \brief
///
union tim_ctrl_base1_timx_psc
{
    uint32_t r;
    struct
    {
        uint32_t psc : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief
///
union tim_ctrl_base1_timx_arr
{
    uint32_t r;
    struct
    {
        uint32_t arr : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief
///
struct tim_ctrl_base1_timx_regs
{
    union tim_ctrl_base1_timx_cr1  cr1;
    union tim_ctrl_base1_timx_cr2  cr2;
    uint32_t                       res0[1];
    union tim_ctrl_base1_timx_dier dier;
    union tim_ctrl_base1_timx_sr   sr;
    union tim_ctrl_base1_timx_egr  egr;
    uint32_t                       res1[3];
    union tim_ctrl_base1_timx_cnt  cnt;
    union tim_ctrl_base1_timx_psc  psc;
    union tim_ctrl_base1_timx_arr  arr;
};

///
/// \brief
///
struct tim_ctrl_base1_timx_dev
{
    volatile struct tim_ctrl_base1_timx_regs *rmap;
    struct tim_ctrl_base1_timx_regs rtmp;
    tim_ctrl_base1_timx_id_t id;
    tim_ctrl_stat_t stat;
};

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_base1_timx_init(void *tim);

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_base1_timx_deinit(void *tim);

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_base1_timx_enable(void *tim);

///
/// \brief
///
tim_ctrl_res_t tim_ctrl_base1_timx_disable(void *tim);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_BASE_H */
