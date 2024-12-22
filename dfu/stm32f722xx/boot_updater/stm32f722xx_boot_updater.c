#include "stm32f722xx_boot_updater.h"
#include "usart_controller.h"
#include "dust.h"
#include "printf.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/usart.h"
#include "libopencm3/cm3/systick.h"

#define PROCESSOR_FREQUENCY (216000000u)
#define CYCLE_TIME          (((1.0f / PROCESSOR_FREQUENCY) * 1000000000.0f))

///*************************************************************************************************
/// Private functions - declaration.
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
static void systick_init(void);

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
static void systick_delay_ms(uint32_t ms);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static void rcc_setup(void)
{
    rcc_clock_setup_hsi(&rcc_3v3[RCC_CLOCK_3V3_216MHZ]);

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

static void systick_init(void)
{
    /* Prescaled processor clock */
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    systick_counter_enable();
}

static void led_on(void)
{
    gpio_set(GPIOB, GPIO14);
}

static void led_off(void)
{
    gpio_clear(GPIOB, GPIO14);
}

static void systick_delay_ms(uint32_t ms)
{
    uint32_t reload_value;
    uint32_t ns = ms * 1000000;

    reload_value = (uint32_t)((float)ns / CYCLE_TIME);

    systick_set_reload(reload_value);
    systick_clear();

    /* Wait for the count flag to be set */
    while (!systick_get_countflag());
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void boot_updater_init(void)
{
    uint32_t *usart_instance;

    rcc_setup();
    systick_init();
    gpio_setup();
    usart_controller_debug_init();

    for (uint32_t i = 0; i < 3; i++)
    {
        led_off();
        systick_delay_ms(500);
        led_on();
        systick_delay_ms(500);
    }

    printf("Boot updater %d initialized...\n\r", 1);

    dust_result_t result = DUST_RESULT_ERROR;

    dust_packet_t deserialized_packet = { 0 };
    dust_packet_t packet              = { 0 };
    dust_header_t header              = { 0 };

    uint8_t data[6] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36 };

    dust_crc16_generate_lut(0x1021);

    result = dust_header_create(&header, DUST_OPCODE_DATA, DUST_LENGTH_BYTES32, 13);
    if (result != DUST_RESULT_ERROR)
    {
        result = dust_packet_create(&packet, &header, &data[0], 6);
    }

    if (result != DUST_RESULT_ERROR)
    {
        uint8_t serialized_packet[DUST_PACKET_HEADER_SIZE + packet.data_size + DUST_PACKET_CRC16_SIZE];
        memset(&serialized_packet[0], 0, sizeof(serialized_packet));
        result = dust_serialize(&packet, &serialized_packet[0], sizeof(serialized_packet));

        dust_header_printf(&header);
        dust_packet_printf(&packet);

        printf("serialized: ");
        for (uint32_t i = 0; i < sizeof(serialized_packet); i++)
        {
            printf("0x%02x ", serialized_packet[i]);
        }

        result = dust_deserialize(&deserialized_packet, serialized_packet, sizeof(serialized_packet));
        if (result == DUST_RESULT_SUCCESS)
        {
            dust_packet_printf(&deserialized_packet);
        }
    }
}

/*
boot_updater_result_t boot_updater_deinit(void)
{
}
*/

void boot_updater_start(void)
{
    boot_updater_init();

    /* Never return */
    while (1);
}
