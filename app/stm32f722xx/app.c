#include "bmi270.h"
#include "bmi270_conf.h"
#include "app.h"
#include "memory_map.h"
#include "tim_ctrl.h"
#include "tim_ctrl_advx.h"
#include "tim_ctrl_gpx.h"
#include "timing.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Turns the LED on.
///
static void led_on(void);

///
/// \brief Turns the LED off.
///
static void led_off(void);

///
/// \brief Turns the LED panic mode.
///
static void led_panic(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static void led_on(void)
{
    gpio_set(GPIOA, GPIO2);
}

static void led_off(void)
{
    gpio_clear(GPIOA, GPIO2);
}

static void led_panic(void)
{
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void app_start(void)
{
    led_on();
    tim_ctrl_init();

    struct bmi270_dev *bmi270 = bmi270_dev_get();
    struct tim_ctrl_dev *tim_ctrl_dev_arr = tim_ctrl_dev_arr_get();

    volatile struct tim_ctrl_gpx_tim2345_dev *tim4 =
        (volatile struct tim_ctrl_gpx_tim2345_dev *)tim_ctrl_dev_arr[TIM_CTRL_INST_TIM4].tim;

    volatile struct tim_ctrl_adv6_tim18_dev *tim8 =
        (volatile struct tim_ctrl_adv6_tim18_dev *)tim_ctrl_dev_arr[TIM_CTRL_INST_TIM8].tim;

    volatile struct tim_ctrl_gpx_tim912_dev *tim12 =
        (volatile struct tim_ctrl_gpx_tim912_dev *)tim_ctrl_dev_arr[TIM_CTRL_INST_TIM12].tim;

    uint32_t motor4_pwm  = 0;
    uint32_t motor4_prev = 0;
    uint32_t motor4_curr = 0;

    uint32_t pitch_ch_prev = 0;
    uint32_t pitch_ch_curr = 0;

    uint32_t roll_ch_prev = 0;
    uint32_t roll_ch_curr = 0;

    uint8_t start = 0;

    /* Never return */
    while (1)
    {
        motor4_prev = tim8->ccr_data[TIM_CTRL_INST_CCR1].prev;
        motor4_curr = tim8->ccr_data[TIM_CTRL_INST_CCR1].curr;

        roll_ch_prev = tim12->ccr_data[TIM_CTRL_INST_CCR1].prev;
        roll_ch_curr = tim12->ccr_data[TIM_CTRL_INST_CCR1].curr;

        pitch_ch_prev = tim12->ccr_data[TIM_CTRL_INST_CCR2].prev;
        pitch_ch_curr = tim12->ccr_data[TIM_CTRL_INST_CCR2].curr;


        if ((pitch_ch_curr > pitch_ch_prev) && (pitch_ch_curr - pitch_ch_prev < 2500) && (motor4_curr > motor4_prev))
        {
            if (((pitch_ch_curr - pitch_ch_prev) < 1150) && ((motor4_curr - motor4_prev) < 1100) && (start == 0))
            {
                start = 1;
            }
            else if (((pitch_ch_curr - pitch_ch_prev) > 1450) && ((motor4_curr - motor4_prev) < 1100) && (start == 3))
            {
                start = 4;
            }

            if (((pitch_ch_curr - pitch_ch_prev) < 1150) && ((motor4_curr - motor4_prev) < 1100) && (start == 4))
            {
                start = 5;
            }
            else if (((pitch_ch_curr - pitch_ch_prev) > 1450) && ((motor4_curr - motor4_prev) < 1100) && (start == 7))
            {
                start = 0;
            }
        }

        if ((roll_ch_curr > roll_ch_prev) && (roll_ch_curr - roll_ch_prev < 2500) && (motor4_curr > motor4_prev))
        {
            if (((roll_ch_curr - roll_ch_prev) < 1150) && ((motor4_curr - motor4_prev) < 1100) && (start == 1))
            {
                start = 2;
            }
            else if (((roll_ch_curr - roll_ch_prev) > 1450) && ((motor4_curr - motor4_prev) < 1100) && (start == 2))
            {
                start = 3;
            }

            if (((roll_ch_curr - roll_ch_prev) < 1150) && ((motor4_curr - motor4_prev) < 1100) && (start == 5))
            {
                start = 6;
            }
            else if (((roll_ch_curr - roll_ch_prev) > 1450) && ((motor4_curr - motor4_prev) < 1100) && (start == 6))
            {
                start = 7;
            }
        }

        if (motor4_curr > motor4_prev)
        {
            if (start == 4)
            {
                motor4_pwm = (motor4_curr - motor4_prev) < 2500 ? (motor4_curr - motor4_prev) : motor4_pwm;
                motor4_pwm = (motor4_pwm > 1250) ? 1250 : motor4_pwm;
                motor4_pwm = (motor4_pwm < 1000) ? 1000 : motor4_pwm;

                tim4->rmap->ccr1.bf.ccr1 = motor4_pwm;
                tim4->rmap->ccr2.bf.ccr2 = motor4_pwm;
                tim4->rmap->ccr3.bf.ccr3 = motor4_pwm;
                tim4->rmap->ccr4.bf.ccr4 = motor4_pwm;
            }
        }
    }
}
