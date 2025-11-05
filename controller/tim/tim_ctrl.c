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
    bool is_init;
};

///
/// \brief
///
struct tim_ctrl_gp1
{
    tim_ctrl_ch16 ch_arr[1];
    bool is_init;
};

///
/// \brief
///
struct tim_ctrl_gp2
{
    tim_ctrl_ch16 ch_arr[2];
    bool is_init;
};

///
/// \brief
///
struct tim_ctrl_gp4_32
{
    tim_ctrl_ch32 ch_arr[4];
    bool is_init;
};

///
/// \brief
///
struct tim_ctrl_gp4_16
{
    tim_ctrl_ch16 ch_arr[4];
    bool is_init;
};

///
/// \brief
///
struct tim_ctrl_base1
{
    tim_ctrl_ch16 ch_arr[1];
    bool is_init;
};

///
/// Used timers inside ghost feather system:
///
/// MOTOR0 -> TIM4_CH4  (PB9)   gp4_16
/// MOTOR1 -> TIM4_CH3  (PB8)   gp4_16
/// MOTOR2 -> TIM4_CH2  (PB7)   gp4_16
/// MOTOR3 -> TIM4_CH1  (PB6)   gp4_16
///
/// RFCH0  -> TIM8_CH4  (PC9)   adv4
/// RFCH1  -> TIM8_CH3  (PC8)   adv4
/// RFCH2  -> TIM8_CH2  (PC7)   adv4
/// RFCH3  -> TIM8_CH1  (PC6)   adv4
/// RFCH4  -> TIM12_CH2 (PB15)  gp2
/// RFCH5  -> TIM12_CH1 (PB14)  gp2
///
