#include "bmi270.h"
#include "bmi270_conf.h"
#include "app.h"
#include "memory_map.h"
#include "tim_ctrl.h"
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

    /* Never return */
    while (1);
}
