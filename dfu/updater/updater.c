#include "dust.h"
#include "ghost_feather_common.h"
#include "printf.h"
#include "updater.h"
#include "ll_usart.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/usart.h"
#include "libopencm3/stm32/flash.h"

#define PSIZE_X8    (0x00u)
#define PSIZE_X16   (0x01u)
#define PSIZE_X32   (0x02u)
#define PSIZE_X64   (0x03u)

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Turns the LED on.
///
static void led_on(void);

///
/// \brief Turn the LED off.
///
static void led_off(void);

///
/// \brief Transmits the packet.
///
static void transmit_ack(dust_packet_t *const packet, dust_serialized_t * serialized,
                         dust_ack_t ack, const uint32_t usart);

///
/// \brief Initializes the system peripherals.
///
/// This function performs the initial setup required for the boot updater to operate.
/// It includes configuring the RCC (Reset and Clock Control), initializing the
/// system tick timer.
///
/// Additionally, it provides a visual indicator of initialization through
/// an LED blinking sequence.
///
static void init(void);

///
/// \brief Deinitializes system peripherals.
///
static void deinit(void);

///
/// \brief Prepares the flash memory for updates.
///
/// This function unlocks the flash erase and program functionality by
/// writing specific keys to the flash key register. It then erases the
/// app sectors (sectors 4 and 5) to ensure a clean state for new data.
///
static void prepare_flash(void);

///
/// \brief Initiates the update process.
///
/// This function begins the update procedure, during which data is received
/// using the dust protocol. It handles the necessary steps to retrieve and
/// process the update data, ensuring that the system is updated correctly.
///
static void update(void);

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

static void transmit_ack(dust_packet_t *const packet, dust_serialized_t *serialized,
                         dust_ack_t ack, const uint32_t usart)
{
    if ((packet == NULL) || (serialized == NULL))
    {
        return;
    }

    (void)dust_header_create(&packet->header, packet->header.opcode, packet->header.length, ack, packet->header.packet_number);

    /* Clear the payload. */
    memset(&packet->payload.buffer[0], 0, packet->payload.buffer_size);

    dust_serialize(packet, &serialized->buffer[0], serialized->buffer_size);
    dust_transmit(serialized, usart);
}


static void init(void)
{
    //usart_controller_debug_init();

    for (uint32_t i = 0; i < 3; i++)
    {
        //led_off();
        //systick_delay_ms(500);
        //led_on();
        //systick_delay_ms(500);
    }
}

static void deinit(void)
{
}

static void prepare_flash(void)
{
    /* Unlock the flash erase/program functionality. */
    FLASH_KEYR = 0x45670123;
    FLASH_KEYR = 0xcdef89ab;

    /* Erase the app 4 and 5 sectors. */
    flash_erase_sector(4, PSIZE_X32);
    flash_erase_sector(5, PSIZE_X32);
}

static void update(void)
{
    /* AXIM interface is used to program the memory.
     * RM0431 3.3.1 Flash memory organization:
     * Write accesses are not supported on ITCM interface. */
    volatile uint32_t app_memory = 0x08010000;
    dust_protocol_instance_t instance = { 0 };
    dust_crc16_generate_lut(0x1021);

    if ((dust_handshake(&instance, USART3) != DUST_RESULT_SUCCESS) ||
        (instance.options.ack_frequency > DUST_ACK_FREQUENCY_TOTAL_SIZE))
    {
        transmit_ack(&instance.packet, &instance.serialized, DUST_ACK_UNSET, USART3);
        return;
    }

    /* Transmit handshake ACK. */
    transmit_ack(&instance.packet, &instance.serialized, DUST_ACK_SET, USART3);

    uint16_t ack_frequency  = dust_get_ack_frequency(instance.options.ack_frequency);
    uint16_t number_of_nack = 0;

    /* How many packet should I receive? Handshake option. */
    for (uint32_t i = 0; i < instance.options.number_of_packets; i++)
    {
        if ((dust_receive(&instance.serialized, USART3) != DUST_RESULT_SUCCESS) &&
            (dust_deserialize(&instance.packet, &instance.serialized.buffer[0], instance.serialized.buffer_size) != DUST_RESULT_SUCCESS))
        {
            number_of_nack++;
        }
        else
        {
            /* Program the app memory. */
            for (uint32_t payload_index = 0; payload_index < instance.packet.payload.buffer_size; payload_index += 4)
            {
                uint32_t word = instance.packet.payload.buffer[payload_index + 0] << 0x00
                              | instance.packet.payload.buffer[payload_index + 1] << 0x08
                              | instance.packet.payload.buffer[payload_index + 2] << 0x10
                              | instance.packet.payload.buffer[payload_index + 3] << 0x18;

                flash_program_word(app_memory, word);
                app_memory += 4;
            }
        }

        if ((((i + 1)  % ack_frequency) == 0) ||
             ((i + 1) == instance.options.number_of_packets))
        {
            if (number_of_nack != 0)
            {
                transmit_ack(&instance.packet, &instance.serialized, DUST_ACK_UNSET, USART3);
                number_of_nack = 0;
                i -= ack_frequency;
            }
            else
            {
                transmit_ack(&instance.packet, &instance.serialized, DUST_ACK_SET, USART3);
            }
        }
    }

    //memset(&instance.serialized.buffer[0], 0, instance.serialized.buffer_size);

    (void)dust_header_create(&instance.packet.header, DUST_OPCODE_DISCONNECT, DUST_LENGTH_BYTES32, DUST_ACK_UNSET, 0x00);
    (void)dust_payload_create(&instance.packet.payload, &instance.serialized.buffer[0], instance.packet.payload.buffer_size);
    (void)dust_serialize(&instance.packet, &instance.serialized.buffer[0], instance.serialized.buffer_size);

    /* Send disconnect packet. */
    (void)dust_transmit(&instance.serialized, USART3);

    /* Wait for the ack packet. */
    while (1)
    {
        if (dust_receive(&instance.serialized, USART3) != DUST_RESULT_SUCCESS)
        {
            transmit_ack(&instance.packet, &instance.serialized, DUST_ACK_UNSET, USART3);
        }
        else
        {
            dust_deserialize(&instance.packet, &instance.serialized.buffer[0], instance.serialized.buffer_size);
            if ((instance.packet.header.opcode == DUST_OPCODE_DISCONNECT) &&
                (instance.packet.header.ack == DUST_ACK_SET))
            {
                transmit_ack(&instance.packet, &instance.serialized, DUST_ACK_SET, USART3);
                break;
            }
            else
            {
                transmit_ack(&instance.packet, &instance.serialized, DUST_ACK_UNSET, USART3);
            }
        }
    }
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************

void updater_start(void)
{
    init();
    prepare_flash();
    update();

    /* Never return */
    while (1);
}
