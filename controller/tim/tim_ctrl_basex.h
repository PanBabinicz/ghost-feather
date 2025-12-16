#ifndef _TIM_CTRL_BASEX_H
#define _TIM_CTRL_BASEX_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "tim_ctrl_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief Identifier for general-purpose timers TIM6 and TIM7.
///
/// This enum selects which base timer instance is being referenced.
///
typedef enum tim_ctrl_base1_tim67_id
{
    TIM_CTRL_BASE1_TIMX_ID_6 = 0,
    TIM_CTRL_BASE1_TIMX_ID_7,
} tim_ctrl_base1_timx_id_t;

///
/// \brief Control Register 1 (CR1) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_cr1
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
/// \brief Control Register 2 (CR2) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_cr2
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
/// \brief DMA/Interrupt Enable Register (DIER) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_dier
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
/// \brief Status Register (SR) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_sr
{
    uint32_t r;
    struct
    {
        uint32_t uif : 1;
        uint32_t     : 31;
    } bf;
};

///
/// \brief Event Generation Register (EGR) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_egr
{
    uint32_t r;
    struct
    {
        uint32_t ug : 1;
        uint32_t    : 31;
    } bf;
};

///
/// \brief Counter Register (CNT) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_cnt
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
/// \brief Prescaler Register (PSC) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_psc
{
    uint32_t r;
    struct
    {
        uint32_t psc : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Auto-Reload Register (ARR) for base timers TIM6 and TIM7.
///
union tim_ctrl_base1_tim67_arr
{
    uint32_t r;
    struct
    {
        uint32_t arr : 16;
        uint32_t     : 16;
    } bf;
};

///
/// \brief Register map for timers TIM6 and TIM7.
///
/// This structure defines the memory-mapped register layout for TIM6 and
/// TIM7. The register order and reserved fields are aligned with the
/// device reference manual to allow direct access via a peripheral base address.
///
struct tim_ctrl_base1_tim67_regs
{
    union tim_ctrl_base1_tim67_cr1  cr1;
    union tim_ctrl_base1_tim67_cr2  cr2;
    uint32_t res0[1];
    union tim_ctrl_base1_tim67_dier dier;
    union tim_ctrl_base1_tim67_sr   sr;
    union tim_ctrl_base1_tim67_egr  egr;
    uint32_t res1[3];
    union tim_ctrl_base1_tim67_cnt  cnt;
    union tim_ctrl_base1_tim67_psc  psc;
    union tim_ctrl_base1_tim67_arr  arr;
};

///
/// \brief Runtime device context for base timers TIM6 and TIM7.
///
/// This structure holds all runtime state required to control a TIM6 and TIM7
/// instance. It includes a pointer to the memory-mapped registers, a temporary
/// shadow copy for safe modification, configuration modes, and initialization status.
///
struct tim_ctrl_base1_tim67_dev
{
    volatile struct tim_ctrl_base1_tim67_regs *rmap;
    struct tim_ctrl_base1_tim67_regs rtmp;
    tim_ctrl_base1_tim67_id_t id;
    tim_ctrl_stat_t stat;
};

///
/// \brief Initializes the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_base1_tim67_init(void *tim);

///
/// \brief Deinitializes the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_base1_tim67_deinit(void *tim);

///
/// \brief Enables the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_base1_tim67_enable(void *tim);

///
/// \brief Disables the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return tim_ctrl_res_t   The tim controller result.
/// \retval TIM_CTRL_RES_OK  On success.
/// \retval TIM_CTRL_RES_ERR Otherwise.
///
tim_ctrl_res_t tim_ctrl_base1_tim67_disable(void *tim);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_BASEX_H */
