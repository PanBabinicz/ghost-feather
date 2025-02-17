#include "dust.h"
#include "libopencm3/stm32/usart.h"

#if (defined(DEBUG_DUST_PROTOCOL) && (DEBUG_DUST_PROTOCOL == 1))
#include "printf.h"
#endif  /* DEBUG_DUST_PROTOCOL */

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \breif Dust protocol crc16 look-up table.
///
static uint16_t dust_crc16_lut[DUST_CRC16_LUT_SIZE];

///
/// \breif Dust handshake ack frequency option hash table.
///
static uint16_t dust_ack_frequency_hash_table[DUST_ACK_FREQUENCY_TOTAL_SIZE] =
{
    0x0001,         /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_EACH_PACKET. */
    0x0008,         /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_8_PACKETS.   */
    0x0010,         /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_16_PACKETS.  */
    0x0020,         /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_32_PACKETS.  */
    0x0040,         /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_64_PACKETS.  */
    0x0080,         /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_128_PACKETS. */
    0x0100,         /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_256_PACKETS. */
    0x0200          /*!< Corresponds to DUST_ACK_FREQUENCY_AFTER_512_PACKETS. */
};

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Calculate the crc16.
///
/// \param[in] packet The dust packet structure.
///
static void dust_crc16_calculate(dust_packet_t *const packet);

///
/// \brief Check the crc16.
///
/// \param[in] data             The data buffer.
/// \param[in] data_size        The data buffer size.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_crc16_check(const uint8_t *const data, const uint32_t data_size);

///
/// \brief Check the handshake options.
///
/// \param[in] instance         The dust protocol instance.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_handshake_options_check(const dust_protocol_instance_t *const instance);

///
/// \brief Calculate the packet payload size from header length field.
///
/// \param[in] packet The dust packet structure.
///
static void dust_packet_calculate_payload_size(dust_packet_t *const packet);

///
/// \brief Calculate the packet header checksum.
///
/// \param[in] packet           The dust packet structure.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_packet_calculate_checksum(dust_packet_t *const packet);

///
/// \breif Serialize the packet header.
///
/// \param[in]  header            The dust packet header.
/// \param[out] serialized_header The serialized header buffer.
/// \param[in]  header_size       The header buffer size.
///
static void dust_serialize_header(const dust_header_t *const header, uint8_t *const serialized_header,
                                  const uint32_t header_size);

///
/// \breif Serialize the packet payload.
///
/// \param[in]  packet             The dust packet.
/// \param[out] serialized_payload The serialized payload buffer.
/// \param[in]  payload_size       The payload buffer size.
///
static void dust_serialize_payload(const dust_packet_t *const packet, uint8_t *const serialized_payload,
                                   const uint32_t payload_size);

///
/// \breif Serialize the packet.
///
/// \param[in]  packet                 The dust packet.
/// \param[out] serialized_packet      The serialized packet buffer.
///
static void dust_serialize_packet(const dust_packet_t *const packet, uint8_t *const serialized_packet);

///
/// \breif Deserialize bytes stream into packet header.
///
/// \param[out] header    The dust packet header.
/// \param[out] data      The data buffer.
/// \param[in]  data_size The data buffer size.
///
static void dust_deserialize_header(dust_header_t *const header, const uint8_t *const data,
                                    const uint32_t data_size);

///
/// \breif Deserialize payload bytes stream into packet data.
///
/// \param[out] packet    The dust packet.
/// \param[out] data      The data buffer.
/// \param[in]  data_size The data buffer size.
///
static void dust_deserialize_payload(dust_packet_t *const packet, const uint8_t *const data,
                                     const uint32_t data_size);

///
/// \breif Deserialize bytes stream into packet.
///
/// \param[out] packet    The dust packet.
/// \param[out] data      The data buffer.
///
static void dust_deserialize_packet(dust_packet_t *const packet, const uint8_t *const data);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static void dust_crc16_calculate(dust_packet_t *const packet)
{
    uint32_t position = 0;
    uint8_t  serialized_header[DUST_PACKET_HEADER_SIZE];
    uint8_t  serialized_data[packet->payload.buffer_size];
    uint8_t  serialized_header_and_data[DUST_PACKET_HEADER_SIZE + packet->payload.buffer_size];

    /* Get serialized header and data. */
    dust_serialize_header(&packet->header, &serialized_header[0], sizeof(serialized_header));
    dust_serialize_payload(packet, &serialized_data[0], sizeof(serialized_data));

    packet->crc16 = 0;
    memcpy(&serialized_header_and_data[0], &serialized_header[0], DUST_PACKET_HEADER_SIZE);
    memcpy(&serialized_header_and_data[DUST_PACKET_HEADER_SIZE], &serialized_data[0],
            packet->payload.buffer_size);

    for (uint32_t i = 0; i < sizeof(serialized_header_and_data); i++)
    {
        /* Equal to ((packet->crc16 ^ (b << 8)) >> 8) */
        position      = ((packet->crc16 >> 8) ^ serialized_header_and_data[i]);
        packet->crc16 = ((packet->crc16 << 8) ^ dust_crc16_lut[position]);
    }
}

const uint16_t* dust_crc16_get_lut_address(void)
{
    return &dust_crc16_lut[0];
}

static dust_result_t dust_crc16_check(const uint8_t *const data, const uint32_t data_size)
{
    uint16_t crc16    = 0;
    uint32_t position = 0;

    for (uint32_t i = 0; i < data_size; i++)
    {
        /* Equal to ((crc16 ^ (b << 8)) >> 8) */
        position = ((crc16 >> 8) ^ data[i]);
        crc16    = ((crc16 << 8) ^ dust_crc16_lut[position]);
    }

    if (crc16 != 0)
    {
        return DUST_RESULT_ERROR;
    }

    return DUST_RESULT_SUCCESS;
}

static dust_result_t dust_handshake_options_check(const dust_protocol_instance_t *const instance)
{
    if (instance->options.ack_frequency > DUST_ACK_FREQUENCY_AFTER_512_PACKETS)
    {
        return DUST_RESULT_ERROR;
    }

    if ((instance->packet.payload.buffer_size % 0x20 != 0x00) ||
        (instance->packet.payload.buffer_size > 0x100))
    {
        return DUST_RESULT_ERROR;
    }

    return DUST_RESULT_SUCCESS;
}

static void dust_packet_calculate_payload_size(dust_packet_t *const packet)
{
    packet->payload.buffer_size = (packet->header.length == DUST_LENGTH_BYTES32)  ? 0x20
                                : (packet->header.length == DUST_LENGTH_BYTES64)  ? 0x40
                                : (packet->header.length == DUST_LENGTH_BYTES128) ? 0x80
                                : 0x100;
}

static dust_result_t dust_packet_calculate_checksum(dust_packet_t *const packet)
{
    uint16_t checksum;

    checksum = 0;
    checksum = (packet->header.opcode        << 0x0e)
             | (packet->header.length        << 0x0c)
             | (packet->header.ack           << 0x0b)
             | (packet->header.packet_number << 0x00);

    checksum = ~checksum;

    if (checksum != packet->header.checksum)
    {
        return DUST_RESULT_ERROR;
    }

    return DUST_RESULT_SUCCESS;
}

static void dust_serialize_header(const dust_header_t *const header, uint8_t *const serialized_header,
                                  const uint32_t header_size)
{
    /* Make sure there is no garbage inside serialized header buffer */
    for (uint32_t i = 0; i < header_size; i++)
    {
        serialized_header[i] = 0;
    }

    serialized_header[0] |= (header->opcode << 0x06);
    serialized_header[0] |= (header->length << 0x04);
    serialized_header[0] |= (header->ack    << 0x03);
    serialized_header[0] |= ((header->packet_number & 0x0700) >> 0x08);
    serialized_header[1] |= ((header->packet_number & 0x00ff) >> 0x00);

    serialized_header[2]  = ((header->checksum & 0xff00) >> 0x08);
    serialized_header[3]  = ((header->checksum & 0x00ff) >> 0x00);
}

static void dust_serialize_payload(const dust_packet_t *const packet, uint8_t *const serialized_payload,
                                   const uint32_t payload_size)
{
    for (uint32_t i = 0; i < payload_size; i++)
    {
        serialized_payload[i] = packet->payload.buffer[i];
    }
}

static void dust_serialize_packet(const dust_packet_t *const packet, uint8_t *const serialized_packet)
{
    dust_serialize_header(&packet->header, &serialized_packet[DUST_PACKET_HEADER_POSITION], DUST_PACKET_HEADER_SIZE);
    dust_serialize_payload(packet, &serialized_packet[DUST_PACKET_DATA_POSITION], packet->payload.buffer_size);

    serialized_packet[DUST_PACKET_HEADER_SIZE + packet->payload.buffer_size]     = ((packet->crc16 & 0xff00) >> 0x08);
    serialized_packet[DUST_PACKET_HEADER_SIZE + packet->payload.buffer_size + 1] = ((packet->crc16 & 0x00ff) >> 0x00);
}

static void dust_deserialize_header(dust_header_t *const header, const uint8_t *const data,
                                    const uint32_t data_size)
{
    memset(header, 0, data_size);

    header->opcode        |= ((data[0] & 0xc0) >> 0x06);
    header->length        |= ((data[0] & 0x30) >> 0x04);
    header->ack           |= ((data[0] & 0x08) >> 0x03);
    header->packet_number |= ((data[0] & 0x07) << 0x04);
    header->packet_number |= ((data[1] & 0xff) >> 0x00);
    header->checksum      |= ((data[2] & 0xff) << 0x08);
    header->checksum      |= ((data[3] & 0xff) << 0x00);
}

static void dust_deserialize_payload(dust_packet_t *const packet, const uint8_t *const data,
                                     const uint32_t data_size)
{
    for (uint32_t i = 0; i < data_size; i++)
    {
        packet->payload.buffer[i] = data[i];
    }
}

static void dust_deserialize_packet(dust_packet_t *const packet, const uint8_t *const data)
{
    dust_deserialize_header(&packet->header, &data[DUST_PACKET_HEADER_POSITION], DUST_PACKET_HEADER_SIZE);
    dust_deserialize_payload(packet, &data[DUST_PACKET_DATA_POSITION], packet->payload.buffer_size);

    packet->crc16  = 0;
    packet->crc16 |= (data[DUST_PACKET_HEADER_SIZE + packet->payload.buffer_size]     << 0x08);
    packet->crc16 |= (data[DUST_PACKET_HEADER_SIZE + packet->payload.buffer_size + 1] << 0x00);
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void dust_crc16_generate_lut(const uint16_t polynomial)
{
    for (uint32_t byte = 0; byte < DUST_CRC16_LUT_SIZE; byte++)
    {
        uint32_t crc16_value = (byte << 8);
        for (uint32_t bit = 0; bit < 8; bit++)
        {
            if (crc16_value & 0x8000)
            {
                crc16_value <<= 1;
                crc16_value  ^= polynomial;
            }
            else
            {
                crc16_value <<= 1;
            }
        }

        dust_crc16_lut[byte] = crc16_value;
    }
}

uint16_t dust_get_ack_frequency(const uint8_t ack_frequency)
{
    return dust_ack_frequency_hash_table[ack_frequency];
}

dust_result_t dust_header_create(dust_header_t *const header, const dust_opcode_t opcode,
                                 const dust_length_t length, const dust_ack_t ack,
                                 const uint16_t packet_number)
{
    if (header == NULL)
    {
        return DUST_RESULT_ERROR;
    }

    header->opcode        = opcode;
    header->length        = length;
    header->ack           = ack;
    header->packet_number = packet_number;
    header->checksum      = ((opcode << 0x0e) | (length << 0x0c) | (ack << 0x0b) | (packet_number << 0x00));
    header->checksum      = ~(header->checksum);

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_payload_create(dust_payload_t *const payload, const uint8_t *const data,
                                  const uint32_t initialize_data_size)
{
    if ((payload == NULL) || (data == NULL))
    {
        return DUST_RESULT_ERROR;
    }

    for (uint32_t i = 0; i < initialize_data_size; i++)
    {
        if (i < initialize_data_size)
        {
            payload->buffer[i] = data[i];
        }
        else
        {
            /* Fill the rest of the packet data buffer with zeros. */
            payload->buffer[i] = 0x00;
        }
    }

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_packet_create(dust_packet_t *const packet, const dust_header_t *const header,
                                 const dust_payload_t *const payload)
{
    if ((packet == NULL) || (header == NULL) || (payload == NULL))
    {
        return DUST_RESULT_ERROR;
    }

    packet->header  = *header;
    packet->payload = *payload;

    dust_crc16_calculate(packet);

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_serialize(dust_packet_t *const packet, uint8_t *const serialized_packet,
                             const uint32_t serialized_packet_size)
{
    if ((packet == NULL) || (serialized_packet == NULL))
    {
        return DUST_RESULT_ERROR;
    }

    if (serialized_packet_size < (DUST_PACKET_HEADER_SIZE + packet->payload.buffer_size + DUST_PACKET_CRC16_SIZE))
    {
        return DUST_RESULT_SIZE_ERROR;
    }

    dust_crc16_calculate(packet);
    dust_serialize_packet(packet, serialized_packet);

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_deserialize(dust_packet_t *const packet, const uint8_t *const data,
                               const uint32_t data_size)
{
    if ((packet == NULL) || (data == NULL))
    {
        return DUST_RESULT_ERROR;
    }

    if (data_size < (DUST_PACKET_HEADER_SIZE + packet->payload.buffer_size + DUST_PACKET_CRC16_SIZE))
    {
        return DUST_RESULT_SIZE_ERROR;
    }

    if (dust_crc16_check(data, data_size) != DUST_RESULT_SUCCESS)
    {
        return DUST_RESULT_ERROR;
    }

    dust_deserialize_packet(packet, data);

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_transmit(const dust_serialized_t *const serialized, const uint32_t usart)
{
    if (serialized == NULL)
    {
        return DUST_RESULT_ERROR;
    }

    for (uint32_t i = 0; i < serialized->buffer_size; i++)
    {
        usart_wait_send_ready(usart);
        usart_send(usart, (uint16_t)serialized->buffer[i]);
    }

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_receive(dust_serialized_t *const serialized, const uint32_t usart)
{
    if (serialized == NULL)
    {
        return DUST_RESULT_ERROR;
    }

    for (uint32_t i = 0; i < serialized->buffer_size; i++)
    {
        usart_wait_recv_ready(usart);
        serialized->buffer[i] = usart_recv(usart);
    }

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_handshake(dust_protocol_instance_t *const instance, const uint32_t usart)
{
    if (instance == NULL)
    {
        return DUST_RESULT_ERROR;
    }

    /* Handshake packet payload has fixed size equal to 32 bytes. */
    instance->packet.payload.buffer_size = 0x20;
    instance->serialized.buffer_size     = DUST_PACKET_HEADER_SIZE + instance->packet.payload.buffer_size +
                                           DUST_PACKET_CRC16_SIZE;

    /* Receive the handshake packet. */
    if (dust_receive(&instance->serialized, usart) != DUST_RESULT_SUCCESS)
    {
        return DUST_RESULT_ERROR;
    }

    /* Deserialize the received data. */
    if (dust_deserialize(&instance->packet, &instance->serialized.buffer[0], instance->serialized.buffer_size) != DUST_RESULT_SUCCESS)
    {
        return DUST_RESULT_ERROR;
    }

    instance->options.ack_frequency      = instance->packet.payload.buffer[0];

    instance->options.number_of_packets  = 0;
    instance->options.number_of_packets |= instance->packet.payload.buffer[1] << 0x18;
    instance->options.number_of_packets |= instance->packet.payload.buffer[2] << 0x10;
    instance->options.number_of_packets |= instance->packet.payload.buffer[3] << 0x08;
    instance->options.number_of_packets |= instance->packet.payload.buffer[4] << 0x00;

    instance->options.payload_size       = 0;
    instance->options.payload_size      |= instance->packet.payload.buffer[5] << 0x08;
    instance->options.payload_size      |= instance->packet.payload.buffer[6] << 0x00;

    /* Update the payload size with the received one. */
    instance->packet.payload.buffer_size = instance->options.payload_size;

    instance->serialized.buffer_size     = DUST_PACKET_HEADER_SIZE + instance->packet.payload.buffer_size +
                                           DUST_PACKET_CRC16_SIZE;

    return DUST_RESULT_SUCCESS;
}

#if (defined(DEBUG_DUST_PROTOCOL) && (DEBUG_DUST_PROTOCOL == 1))
dust_result_t dust_header_printf(const dust_header_t *const header)
{
    if (header == NULL)
    {
        return DUST_RESULT_ERROR;
    }

    printf("opcode:        0x%02x\n\r", header->opcode);
    printf("length:        0x%02x\n\r", header->length);
    printf("packet_number: 0x%04x\n\r", header->packet_number);
    printf("checksum:      0x%04x\n\r", header->checksum);

    return DUST_RESULT_SUCCESS;
}

dust_result_t dust_packet_printf(const dust_packet_t *const packet)
{
    if (packet == NULL)
    {
        return DUST_RESULT_ERROR;
    }

    printf("header: 0x%08x\n\r", packet->header);
    printf("data:   ");

    for (uint32_t i = 0; i < packet->payload.buffer_size; i++)
    {
        printf("0x%02x ", packet->payload.buffer[i]);
    }

    printf("\n\rcrc16:  0x%04x\n\r", packet->crc16);

    return DUST_RESULT_SUCCESS;
}

#endif  /* DEBUG_DUST_PROTOCOL */
