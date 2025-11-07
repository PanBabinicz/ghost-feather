#include "tim_ctrl.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief
///
union tim_ctrl_adv4_timx_cr1
{
    uint16_t r;
    struct bit_field
    {
        uint16_t cen      : 1;
        uint16_t udis     : 1;
        uint16_t urs      : 1;
        uint16_t opm      : 1;
        uint16_t dir      : 1;
        uint16_t cms      : 1;
        uint16_t arpe     : 1;
        uint16_t ckd      : 2;
        uint16_t          : 1;
        uint16_t uifremap : 1;
        uint16_t          : 4;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_cr2
{
    uint32_t r;
    struct bit_field
    {
        uint32_t ccpc     : 1;
        uint32_t          : 1;
        uint32_t ccus     : 1;
        uint32_t ccds     : 1;
        uint32_t          : 1;
        uint32_t mms      : 3;
        uint32_t ti1s     : 1;
        uint32_t ois1     : 1;
        uint32_t ois1n    : 1;
        uint32_t ois2     : 1;
        uint32_t ois2n    : 1;
        uint32_t ois3     : 1;
        uint32_t ois3n    : 1;
        uint32_t ois4     : 1;
        uint32_t          : 1;
        uint32_t ois5     : 1;
        uint32_t          : 1;
        uint32_t ois6     : 1;
        uint32_t          : 1;
        uint32_t mms2     : 4;
        uint32_t          : 8;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_smcr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t sms      : 3;
        uint32_t          : 1;
        uint32_t ts       : 3;
        uint32_t msm      : 1;
        uint32_t etf      : 4;
        uint32_t etps     : 2;
        uint32_t ece      : 1;
        uint32_t etp      : 1;
        uint32_t sms_msb  : 1;
        uint32_t          : 15;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_dier
{
    uint16_t r;
    struct bit_field
    {
        uint16_t uie      : 1;
        uint16_t cc1ie    : 1;
        uint16_t cc2ie    : 1;
        uint16_t cc3ie    : 1;
        uint16_t cc4ie    : 1;
        uint16_t comie    : 1;
        uint16_t tie      : 1;
        uint16_t bie      : 1;
        uint16_t ude      : 1;
        uint16_t cc1de    : 1;
        uint16_t cc2de    : 1;
        uint16_t cc3de    : 1;
        uint16_t cc4de    : 1;
        uint16_t comde    : 1;
        uint16_t tde      : 1;
        uint16_t          : 1;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_sr
{
    uint32_t r;
    struct bit_field
    {
        uint32_t uif      : 1;
        uint32_t cc1if    : 1;
        uint32_t cc2if    : 1;
        uint32_t cc3if    : 1;
        uint32_t cc4if    : 1;
        uint32_t comif    : 1;
        uint32_t tif      : 1;
        uint32_t bif      : 1;
        uint32_t b2if     : 1;
        uint32_t cc1of    : 1;
        uint32_t cc2of    : 1;
        uint32_t cc3of    : 1;
        uint32_t cc4of    : 1;
        uint32_t sbif     : 1;
        uint32_t          : 2;
        uint32_t cc5if    : 1;
        uint32_t cc6if    : 1;
        uint32_t          : 14;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_egr
{
    uint16_t r;
    struct bit_field
    {
        uint16_t ug       : 1;
        uint16_t cc1g     : 1;
        uint16_t cc2g     : 1;
        uint16_t cc3g     : 1;
        uint16_t cc4g     : 1;
        uint16_t comg     : 1;
        uint16_t tg       : 1;
        uint16_t bg       : 1;
        uint16_t b2g      : 1;
        uint16_t          : 7;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccmr1
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc1s     : 2;
        uint32_t ic1psc   : 2;
        uint32_t ic1f     : 4;
        uint32_t cc2s     : 2;
        uint32_t ic2psc   : 2;
        uint32_t ic2f     : 4;
        uint32_t          : 16;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccmr1_alt
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc1s     : 2;
        uint32_t oc1fe    : 1;
        uint32_t oc1pe    : 1;
        uint32_t oc1m     : 3;
        uint32_t oc1ce    : 1;
        uint32_t cc2s     : 2;
        uint32_t oc2fe    : 1;
        uint32_t oc2pe    : 1;
        uint32_t oc2m     : 3;
        uint32_t oc2ce    : 1;
        uint32_t oc1m_msb : 1;
        uint32_t          : 7;
        uint32_t oc2m_msb : 1;
        uint32_t          : 7;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccmr2
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc3s     : 2;
        uint32_t ic3psc   : 2;
        uint32_t ic3f     : 4;
        uint32_t cc4s     : 2;
        uint32_t ic4psc   : 2;
        uint32_t ic4f     : 4;
        uint32_t          : 16;
    };
};

///
/// \brief
///
union tim_ctrl_adv4_timx_ccmr2_alt
{
    uint32_t r;
    struct bit_field
    {
        uint32_t cc3s     : 2;
        uint32_t oc3fe    : 1;
        uint32_t oc3pe    : 1;
        uint32_t oc3m     : 3;
        uint32_t oc3ce    : 1;
        uint32_t cc4s     : 2;
        uint32_t oc4fe    : 1;
        uint32_t oc4pe    : 1;
        uint32_t oc4m     : 3;
        uint32_t oc4ce    : 1;
        uint32_t oc3m_msb : 1;
        uint32_t          : 7;
        uint32_t oc4m_msb : 1;
        uint32_t          : 7;
    };
};

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
