#include "dust.h"

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
/// \breif Serialize the packet header.
///
/// \param[in]  header          The dust packet header.
/// \param[out] serialized      The serialized header.
/// \param[in]  header_size     The header size.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_serialize_header(const dust_header_t *const header,
                                           uint8_t *const serialized_header,
                                           const uint32_t header_size);

///
/// \breif Serialize the packet data.
///
/// \param[in]  paket           The dust packet.
/// \param[out] serialized_data The serialized data.
/// \param[in]  data_size       The data size.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_serialize_data(const dust_packet_t *const packet,
                                         uint8_t *const serialized_data,
                                         const uint32_t data_size);

///
/// \breif Serialize the packet.
///
/// \param[in]  packet                      The dust packet.
/// \param[out] serialized_packet           The serialized dust packet.
/// \param[in]  packet_size                 The dust packet size.
///
/// \return dust_result_t                   Result of the function.
/// \retval DUST_RESULT_SUCCESS             On success.
/// \retval DUST_RESULT_SERIALIZATION_ERROR On serialization error.
/// \retval DUST_RESULT_ERROR               Otherwise.
///
static dust_result_t dust_serialize_packet(const dust_packet_t *const packet,
                                           uint8_t *const serialized_packet,
                                           const uint32_t packet_size);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static dust_result_t dust_serialize_header(const dust_header_t *const header,
                                           uint8_t *const serialized_header,
                                           const uint32_t header_size)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((header != NULL) && (serialized_header != NULL))
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

        result = DUST_RESULT_SUCCESS;
    }

    return result;
}

static dust_result_t dust_serialize_data(const dust_packet_t *const packet,
                                         uint8_t *const serialized_data,
                                         const uint32_t data_size)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((packet != NULL) && (serialized_data != NULL))
    {
        for (uint32_t i = 0; i < data_size; i++)
        {
            serialized_data[i] = packet->data[i];
        }

        result = DUST_RESULT_SUCCESS;
    }

    return result;
}

static dust_result_t dust_serialize_packet(const dust_packet_t *const packet,
                                           uint8_t *const serialized_packet,
                                           const uint32_t packet_size)
{
    dust_result_t result = DUST_RESULT_ERROR;
    uint32_t index       = 0;

    if ((packet != NULL) && (serialized_packet != NULL))
    {
        result = dust_serialize_header(&packet->header, &serialized_packet[DUST_SERIALIZED_HEADER_POSITION],
                                       DUST_PACKET_HEADER_SIZE);
        if (result != DUST_RESULT_ERROR)
        {
            result = dust_serialize_data(packet, &serialized_packet[DUST_SERIALIZED_DATA_POSITION],
                                         packet->data_size);
        }

        if (result != DUST_RESULT_ERROR)
        {
            serialized_packet[DUST_PACKET_HEADER_SIZE + packet->data_size]     = ((packet->crc16 & 0xff00) >> 0x08);
            serialized_packet[DUST_PACKET_HEADER_SIZE + packet->data_size + 1] = ((packet->crc16 & 0x00ff) >> 0x00);

            result = DUST_RESULT_SUCCESS;
        }
        else
        {
            result = DUST_RESULT_SERIALIZATION_ERROR;
        }
    }

    return result;
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

dust_result_t dust_crc16_calculate(dust_packet_t *const packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if (packet != NULL)
    {
        uint32_t position = 0;
        uint8_t  serialized_header[DUST_PACKET_HEADER_SIZE];
        uint8_t  serialized_data[packet->data_size];
        uint8_t  serialized_header_and_data[DUST_PACKET_HEADER_SIZE + packet->data_size];

        /* Get serialized header and data. */
        result = dust_serialize_header(&packet->header, &serialized_header[0], sizeof(serialized_header));

        if (result != DUST_RESULT_ERROR)
        {
            result = dust_serialize_data(packet, &serialized_data[0], sizeof(serialized_data));
        }

        if (result != DUST_RESULT_ERROR)
        {
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
        else
        {
            result = DUST_RESULT_SERIALIZATION_ERROR;
        }
    }

    return result;
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

        result = dust_crc16_calculate(packet);
    }

    return result;
}

dust_result_t dust_serialize(dust_packet_t *const packet, uint8_t *const serialized_packet,
                             const uint32_t packet_size)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((packet != NULL) && (serialized_packet != NULL))
    {
        result = dust_serialize_packet(packet, serialized_packet, packet_size);
    }

    return result;
}

dust_result_t dust_transmit(const dust_packet_t *const packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

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
