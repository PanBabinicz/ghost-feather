#ifndef _TIM_CTRL_BASE_H
#define _TIM_CTRL_BASE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief
///
union tim_ctrl_base1_timx_cr1
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cen      : 1;
        uint16_t udis     : 1;
        uint16_t urs      : 1;
        uint16_t opm      : 1;
        uint16_t          : 3;
        uint16_t arpe     : 1;
        uint16_t          : 3;
        uint16_t uifremap : 1;
        uint16_t          : 4;
    };
};

///
/// \brief
///
union tim_ctrl_base1_timx_cr2
{
    uint16_t r;
    struct bit_field
    {
        uint16_t          : 4;
        uint16_t mms      : 3;
        uint16_t          : 9;
    };
};

///
/// \brief
///
union tim_ctrl_base1_timx_dier
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uie      : 1;
        uint16_t          : 7;
        uint16_t ude      : 1;
        uint16_t          : 7;
    };
};

///
/// \brief
///
union tim_ctrl_base1_timx_sr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uif      : 1;
        uint16_t          : 15;
    };
};

///
/// \brief
///
union tim_ctrl_base1_timx_egr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ug       : 1;
        uint16_t          : 15;
    };
};

///
/// \brief
///
union tim_ctrl_base1_timx_cnt
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cnt      : 16;
        uint32_t          : 15;
        uint32_t uifcpy   : 1;
    };
};

///
/// \brief
///
union tim_ctrl_base1_timx_psc
{
    uint16_t r;
    struct bit_field
    {
        uint16_t psc      : 16;
    };
};

///
/// \brief
///
union tim_ctrl_base1_timx_arr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t arr      : 16;
    };
};

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_BASE_H */
