#ifndef _LL_TIM_BASEX_H
#define _LL_TIM_BASEX_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ll_tim_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief Identifier for base timers TIM6 and TIM7.
///
/// This enum selects which base timer instance is being referenced.
///
typedef enum ll_tim_base1_tim67_id
{
    LL_TIM_BASE1_TIM67_ID_6 = 0,
    LL_TIM_BASE1_TIM67_ID_7,
} ll_tim_base1_tim67_id_t;

///
/// \brief Control Register 1 (CR1) for base timers TIM6 and TIM7.
///
union ll_tim_base1_tim67_cr1
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
union ll_tim_base1_tim67_cr2
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
union ll_tim_base1_tim67_dier
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
union ll_tim_base1_tim67_sr
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
union ll_tim_base1_tim67_egr
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
union ll_tim_base1_tim67_cnt
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
union ll_tim_base1_tim67_psc
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
union ll_tim_base1_tim67_arr
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
struct ll_tim_base1_tim67_regs
{
    union ll_tim_base1_tim67_cr1  cr1;
    union ll_tim_base1_tim67_cr2  cr2;
    uint32_t res0[1];
    union ll_tim_base1_tim67_dier dier;
    union ll_tim_base1_tim67_sr   sr;
    union ll_tim_base1_tim67_egr  egr;
    uint32_t res1[3];
    union ll_tim_base1_tim67_cnt  cnt;
    union ll_tim_base1_tim67_psc  psc;
    union ll_tim_base1_tim67_arr  arr;
};

///
/// \brief Runtime device context for base timers TIM6 and TIM7.
///
/// This structure holds all runtime state required to control a TIM6 and TIM7
/// instance. It includes a pointer to the memory-mapped registers, a temporary
/// shadow copy for safe modification, configuration modes, and initialization status.
///
struct ll_tim_base1_tim67_dev
{
    volatile struct ll_tim_base1_tim67_regs *rmap;
    struct ll_tim_base1_tim67_regs rtmp;
    ll_tim_base1_tim67_id_t id;
    ll_tim_stat_t stat;
};

///
/// \brief Initializes the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_base1_tim67_init(void *tim);

///
/// \brief Deinitializes the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_base1_tim67_deinit(void *tim);

///
/// \brief Enables the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_base1_tim67_enable(void *tim);

///
/// \brief Disables the base timer (TIM6 and TIM7).
///
/// \param[in] tim The pointer to timer device.
///
/// \return ll_tim_res_t   The TIM result.
/// \retval LL_TIM_RES_OK  On success.
/// \retval LL_TIM_RES_ERR Otherwise.
///
ll_tim_res_t ll_tim_base1_tim67_disable(void *tim);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_TIM_BASEX_H */
