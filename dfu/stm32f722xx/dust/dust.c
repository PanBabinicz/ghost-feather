#include "dust.h"
#include "libopencm3/stm32/usart.h"

#if (defined(DEBUG_DUST_PROTOCOL) && (DEBUG_DUST_PROTOCOL == 1))
#include "printf.h"
#endif  /* DEBUG_DUST_PROTOCOL */

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \breif Circular buffer data structure array.
///
static uint16_t dust_crc16_lut[DUST_CRC16_LUT_SIZE];

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
static dust_result_t dust_crc16_check(const uint8_t *const data, const uint8_t data_size);

///
/// \breif Serialize the packet header.
///
/// \param[in]  header                 The dust packet header.
/// \param[out] serialized_header      The serialized header buffer.
/// \param[in]  serialized_header_size The serialized header buffer size.
///
static void dust_serialize_header(const dust_header_t *const header, uint8_t *const serialized_header,
                                  const uint32_t serialized_header_size);

///
/// \breif Serialize the packet data.
///
/// \param[in]  packet               The dust packet.
/// \param[out] serialized_data      The serialized data buffer.
/// \param[in]  serialized_data_size The serialized data buffer size.
///
static void dust_serialize_data(const dust_packet_t *const packet, uint8_t *const serialized_data,
                                const uint32_t serialized_data_size);

///
/// \breif Serialize the packet.
///
/// \param[in]  packet                 The dust packet.
/// \param[out] serialized_packet      The serialized packet buffer.
/// \param[in]  serialized_packet_size The serialized packet buffer size.
///
static void dust_serialize_packet(const dust_packet_t *const packet, uint8_t *const serialized_packet,
                                  const uint32_t serialized_packet_size);

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
/// \breif Deserialize bytes stream into packet data.
///
/// \param[out] packet    The dust packet.
/// \param[out] data      The data buffer.
/// \param[in]  data_size The data buffer size.
///
static void dust_deserialize_data(dust_packet_t *const packet, const uint8_t *const data,
                                  const uint32_t data_size);

///
/// \breif Deserialize bytes stream into packet.
///
/// \param[out] packet    The dust packet.
/// \param[out] data      The data buffer.
/// \param[in]  data_size The data buffer size.
///
static void dust_deserialize_packet(dust_packet_t *const packet, const uint8_t *const data,
                                    const uint32_t data_size);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static void dust_crc16_calculate(dust_packet_t *const packet)
{
    uint32_t position = 0;
    uint8_t  serialized_header[DUST_PACKET_HEADER_SIZE];
    uint8_t  serialized_data[packet->data_size];
    uint8_t  serialized_header_and_data[DUST_PACKET_HEADER_SIZE + packet->data_size];

    /* Get serialized header and data. */
    dust_serialize_header(&packet->header, &serialized_header[0], sizeof(serialized_header));
    dust_serialize_data(packet, &serialized_data[0], sizeof(serialized_data));

    packet->crc16 = 0;
    memcpy(&serialized_header_and_data[0], &serialized_header[0], DUST_PACKET_HEADER_SIZE);
    memcpy(&serialized_header_and_data[DUST_PACKET_HEADER_SIZE], &serialized_data[0],
            packet->data_size);

    for (uint32_t i = 0; i < sizeof(serialized_header_and_data); i++)
    {
        /* Equal to ((packet->crc16 ^ (b << 8)) >> 8) */
        position      = ((packet->crc16 >> 8) ^ serialized_header_and_data[i]);
        packet->crc16 = ((packet->crc16 << 8) ^ dust_crc16_lut[position]);
    }
}

static dust_result_t dust_crc16_check(const uint8_t *const data, const uint8_t data_size)
{
    dust_result_t result;
    uint16_t      crc16    = 0;
    uint32_t      position = 0;

    for (uint32_t i = 0; i < data_size; i++)
    {
        /* Equal to ((crc16 ^ (b << 8)) >> 8) */
        position = ((crc16 >> 8) ^ data[i]);
        crc16    = ((crc16 << 8) ^ dust_crc16_lut[position]);
    }

    if (crc16 == 0)
    {
        result = DUST_RESULT_SUCCESS;
    }
    else
    {
        result = DUST_RESULT_ERROR;
    }

    return result;
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
    serialized_header[0] |= ((header->packet_number & 0x0f00) >> 0x08);
    serialized_header[1] |= ((header->packet_number & 0x00ff) >> 0x00);

    serialized_header[2]  = ((header->checksum & 0xff00) >> 0x08);
    serialized_header[3]  = ((header->checksum & 0x00ff) >> 0x00);
}

static void dust_serialize_data(const dust_packet_t *const packet, uint8_t *const serialized_data,
                                const uint32_t data_size)
{
    for (uint32_t i = 0; i < data_size; i++)
    {
        serialized_data[i] = packet->data[i];
    }
}

static void dust_serialize_packet(const dust_packet_t *const packet, uint8_t *const serialized_packet,
                                  const uint32_t serialized_packet_size)
{
    dust_serialize_header(&packet->header, &serialized_packet[DUST_PACKET_HEADER_POSITION],
                          DUST_PACKET_HEADER_SIZE);
    dust_serialize_data(packet, &serialized_packet[DUST_PACKET_DATA_POSITION], packet->data_size);

    serialized_packet[DUST_PACKET_HEADER_SIZE + packet->data_size]     = ((packet->crc16 & 0xff00) >> 0x08);
    serialized_packet[DUST_PACKET_HEADER_SIZE + packet->data_size + 1] = ((packet->crc16 & 0x00ff) >> 0x00);
}

static void dust_deserialize_header(dust_header_t *const header, const uint8_t *const data,
                                    const uint32_t data_size)
{
    memset(header, 0, sizeof(header));

    header->opcode        |= ((data[0] & 0xc0) >> 0x06);
    header->length        |= ((data[0] & 0x30) >> 0x04);
    header->packet_number |= ((data[0] & 0x0f) << 0x08);
    header->packet_number |= ((data[1] & 0xff) >> 0x00);
    header->checksum      |= ((data[2] & 0xff) << 0x08);
    header->checksum      |= ((data[3] & 0xff) << 0x00);
}

static void dust_deserialize_data(dust_packet_t *const packet, const uint8_t *const data,
                                  const uint32_t data_size)
{
    for (uint32_t i = 0; i < data_size; i++)
    {
        packet->data[i] = data[i];
    }
}

static void dust_deserialize_packet(dust_packet_t *const packet, const uint8_t *const data,
                                    const uint32_t data_size)
{
    dust_deserialize_header(&packet->header, &data[DUST_PACKET_HEADER_POSITION], DUST_PACKET_HEADER_SIZE);
    dust_deserialize_data(packet, &data[DUST_PACKET_DATA_POSITION], data_size);

    packet->data_size = (packet->header.length == DUST_LENGTH_BYTES32)  ? 0x20 :
                        (packet->header.length == DUST_LENGTH_BYTES64)  ? 0x40 :
                        (packet->header.length == DUST_LENGTH_BYTES128) ? 0x80 : 0x100;

    packet->crc16  = 0;
    packet->crc16 |= (data[DUST_PACKET_HEADER_SIZE + packet->data_size]     << 0x08);
    packet->crc16 |= (data[DUST_PACKET_HEADER_SIZE + packet->data_size + 1] << 0x00);
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

dust_result_t dust_header_create(dust_header_t *const header, const dust_opcode_t opcode,
                                 const dust_length_t length, const uint16_t packet_number)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if (header != NULL)
    {
        header->opcode        = opcode;
        header->length        = length;
        header->packet_number = packet_number;
        header->checksum      = ((opcode << 0x0e) | (length << 0x0c) | (packet_number << 0x00));
        header->checksum      = ~(header->checksum);

        result = DUST_RESULT_SUCCESS;
    }

    return result;
}

dust_result_t dust_packet_create(dust_packet_t *const packet, const dust_header_t *const header,
                                 const uint8_t *const data, const uint32_t initialize_data_size)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((packet != NULL) && (header != NULL) && (data != NULL))
    {
        packet->header    = *header;
        packet->data_size = (packet->header.length == DUST_LENGTH_BYTES32)  ? 0x20 :
                            (packet->header.length == DUST_LENGTH_BYTES64)  ? 0x40 :
                            (packet->header.length == DUST_LENGTH_BYTES128) ? 0x80 : 0x100;

        for (uint32_t i = 0; i < initialize_data_size; i++)
        {
            if (i < initialize_data_size)
            {
                packet->data[i] = data[i];
            }
            else
            {
                /* Fill the rest of the packet data buffer with zeros. */
                packet->data[i] = 0;
            }
        }

        dust_crc16_calculate(packet);
        result = DUST_RESULT_SUCCESS;
    }

    return result;
}

dust_result_t dust_serialize(const dust_packet_t *const packet, uint8_t *const serialized_packet,
                             const uint32_t serialized_packet_size)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((packet != NULL) && (serialized_packet != NULL))
    {
        if (serialized_packet_size < (DUST_PACKET_HEADER_SIZE + packet->data_size + DUST_PACKET_CRC16_SIZE))
        {
            result = DUST_RESULT_SIZE_ERROR;
        }
        else
        {
            dust_serialize_packet(packet, serialized_packet, serialized_packet_size);
            result = DUST_RESULT_SUCCESS;
        }
    }

    return result;
}

dust_result_t dust_deserialize(dust_packet_t *const packet, const uint8_t *const data,
                               const uint32_t data_size)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((packet != NULL) && (data != NULL))
    {
        if (data_size < (DUST_PACKET_HEADER_SIZE + packet->data_size + DUST_PACKET_CRC16_SIZE))
        {
            result = DUST_RESULT_SIZE_ERROR;
        }
        else
        {
            result = dust_crc16_check(data, data_size);
            if (result == DUST_RESULT_SUCCESS)
            {
                dust_deserialize_packet(packet, data, data_size);
            }
        }
    }

    return result;
}

dust_result_t dust_transmit(const uint8_t *serialized_packet, const uint32_t serialized_packet_size)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if (serialized_packet != NULL)
    {
        for (uint32_t i = 0; i < serialized_packet_size; i++)
        {
            usart_send(USART3, (uint16_t)serialized_packet[i]);
            usart_wait_send_ready(USART3);
        }

        result = DUST_RESULT_SUCCESS;
    }

    return result;
}

dust_result_t dust_receive(dust_packet_t **packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}

#if (defined(DEBUG_DUST_PROTOCOL) && (DEBUG_DUST_PROTOCOL == 1))
dust_result_t dust_header_printf(const dust_header_t *const header)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if (header != NULL)
    {
        printf("opcode:        0x%02x\n\r", header->opcode);
        printf("length:        0x%02x\n\r", header->length);
        printf("packet_number: 0x%04x\n\r", header->packet_number);
        printf("checksum:      0x%04x\n\r", header->checksum);
    }

    return result;
}

dust_result_t dust_packet_printf(const dust_packet_t *const packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if (packet != NULL)
    {
        printf("header: 0x%08x\n\r", packet->header);
        printf("data:   ");

        for (uint32_t i = 0; i < packet->data_size; i++)
        {
            printf("0x%02x ", packet->data[i]);
        }

        printf("\n\rcrc16:  0x%04x\n\r", packet->crc16);
    }

    return result;
}

#endif  /* DEBUG_DUST_PROTOCOL */
