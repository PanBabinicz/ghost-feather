#include "tim_ctrl.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief
///
struct tim_ctrl_ch32
{
    uint32_t ar;
    uint32_t cnt;
    uint32_t ccr;
    uint16_t psc;
};

///
/// \brief
///
struct tim_ctrl_ch16
{
    uint16_t ar;
    uint16_t cnt;
    uint16_t ccr;
    uint16_t psc;
};

///
/// \brief
///
struct tim_ctrl_adv4
{
    tim_ctrl_ch16 ch_arr[4];
};

///
/// \brief
///
struct tim_ctrl_gp1
{
    tim_ctrl_ch16 ch_arr[1];
};

///
/// \brief
///
struct tim_ctrl_gp2
{
    tim_ctrl_ch16 ch_arr[2];
};

///
/// \brief
///
struct tim_ctrl_gp4_32
{
    tim_ctrl_ch32 ch_arr[4];
};

///
/// \brief
///
struct tim_ctrl_gp4_16
{
    tim_ctrl_ch16 ch_arr[4];
};

///
/// \brief
///
struct tim_ctrl_base1
{
    tim_ctrl_ch16 ch_arr[1];
};

