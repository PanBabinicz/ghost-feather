#include "stm32f722xx_boot_updater.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/usart.h"

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
///
/// \brief
///
static void rcc_setup(void);

///
/// \brief
///
static void gpio_setup(void);

///
/// \brief
///
static void usart_setup(void);

///
/// \brief
///
static void led_on(void);

///
/// \brief
///
static void led_off(void);

///
/// \brief
///
static void delay(uint32_t ms);

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
static void rcc_setup(void)
{
    /* USART3 uses PD8 and PD9 pins */
    rcc_periph_clock_enable(RCC_GPIOD);
    rcc_periph_clock_enable(RCC_USART3);

    /* Enable clock for red led */
    rcc_periph_clock_enable(RCC_GPIOB);
}

static void gpio_setup(void)
{
    /* USART3 gpio setup */
    gpio_mode_setup(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, (GPIO8 | GPIO9));
    gpio_set_af(GPIOD, GPIO_AF7, (GPIO8 | GPIO9));

    /* LED gpio setup */
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);
}

static void usart_setup(void)
{
    usart_disable(USART3);

    usart_set_baudrate(USART3, 115200);
    usart_set_databits(USART3, 8);

    /* 1 stop bit, refer to manual */
    usart_set_stopbits(USART3, 0);

    usart_set_parity(USART3, USART_PARITY_NONE);
    usart_set_mode(USART3, USART_MODE_TX_RX);

    usart_enable(USART3);
}

static void led_on(void)
{
    gpio_set(GPIOB, GPIO14);
}

static void led_off(void)
{
    gpio_clear(GPIOB, GPIO14);
}

static void delay(uint32_t ms)
{
    uint32_t ns = (ms * 1000000);
    ns /= 4;

    for (volatile uint32_t i = 0; i < ns; i++)
    {
        __asm("nop");
    }
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
boot_updater_result_t boot_updater_init(void)
{
    rcc_setup();
    gpio_setup();
    usart_setup();

    for (uint32_t i = 0; i < 5; i++)
    {
        led_off();
        delay(1000);
        led_on();
        delay(1000);
    }

    /* Send A */
    usart_send(USART3, 0x41);

    return BOOT_UPDATER_RESULT_SUCCESS;
}

/*
boot_updater_result_t boot_updater_deinit(void)
{
}
*/

void boot_updater_start(void)
{
    boot_updater_init();
    volatile uint32_t x = 0;
    ++x;
    ++x;

    /* Never return */
    //while (1);
}