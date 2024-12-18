#include "dust.h"

#define DUST_CRC16_LUT_SIZE             (0xffu)
#define DUST_SERIALIZED_HEADER_POSITION (0x00u)
#define DUST_SERIALIZED_DATA_POSITION   (0x04u)

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
/// \param[in] header     The dust packet header.
/// \param[in] serialized The serialized data.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_serialize_header(dust_header_t *header, uint8_t *serialized);

///
/// \breif Serialize the packet data.
///
/// \param[in] paket      The dust packet.
/// \param[in] serialized The serialized data.
/// \param[in] index      The serialized data buffer index.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_serialize_data(dust_packet_t *packet, uint8_t *serialized, uint32_t *index);

///
/// \breif Serialize the packet.
///
/// \param[in] packet The dust packet.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
static dust_result_t dust_serialize(dust_packet_t *packet);

///
/// \breif The dust header type.
///
typedef struct
{
    uint32_t opcode        : 2;
    uint32_t length        : 2;
    uint32_t packet_number : 12;
    uint32_t checksum      : 16;
} dust_header_t;

///
/// \breif The dust packet type.
///
typedef struct
{
    dust_header_t header;
    uint8_t       data[DUST_PACKET_DATA_BUFFER_MAX_SIZE];
    uint16_t      crc16;
} dust_packet_t;

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static dust_result_t dust_serialize_header(dust_header_t *header, uint8_t *serialized)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((header != NULL) && (serialized != NULL))
    {
        /* Make sure there is no garbage inside serialized buffer */
        for (uint32_t i = 0; i < DUST_PACKET_HEADER_SIZE; i++)
        {
            serialized[i] = 0;
        }

        serialized[0] |= (header->opcode << 0x06);
        serialized[0] |= (header->length << 0x04);
        serialized[0] |= ((header->packet_number & 0x0f00) >> 0x08);
        serialized[1] |= ((header->packet_number & 0x00ff) >> 0x00);

        serialized[2] = ((header->checksum & 0xff00) >> 0x08);
        serialized[3] = ((header->checksum & 0x00ff) >> 0x00);

        result = DUST_RESULT_SUCCESS;
    }

    return result;
}

static dust_result_t dust_serialize_data(dust_packet_t *packet, uint8_t *serialized, uint32_t *index)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if ((packet != NULL) && (serialized != NULL) && (index != NULL))
    {
        uint32_t i;
        uint32_t size = (packet->header.length == DUST_LENGTH_BYTE32)  ?  32 :
                        (packet->header.length == DUST_LENGTH_BYTE64)  ?  64 :
                        (packet->header.length == DUST_LENGTH_BYTE128) ? 128 : 256;

        for (i = 0; i < size; i++)
        {
            serialized[*index + i] = packet->data[i];
        }

        *index += i;
        result = DUST_RESULT_SUCCESS;
    }

    return result
}

static dust_result_t dust_serialize(dust_packet_t *packet, uint8_t *serialized)
{
    dust_result_t result = DUST_RESULT_ERROR;
    uint32_t index       = 0;

    if ((packet != NULL) && (serialized != NULL))
    {
        dust_serialize_header(&packet->header, &serialized[DUST_SERIALIZED_HEADER_POSITION]);
        dust_serialize_data(&packet->header, &serialized[DUST_SERIALIZED_DATA_POSITION], &index);

        result = DUST_RESULT_SUCCESS;
    }

    return result;
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void dust_crc16_generate_lut(uint16_t polynomial)
{
    for (uint32_t byte = 0; byte < DUST_CRC16_LUT_SIZE; byte++)
    {
        uint32_t crc16_value = (byte << 8);
        for (uint32_t bit = 0; bit < 8; bit++)
        {
            if (crc16_value & 0x8000)
            {
                crc16_value <<= 1;
                crc16_value ^= polynomial;
            }
            else
            {
                crc16_value <<= 1;
            }
        }

        dust_crc16_lut[byte] = crc16_value;
    }
}

dust_result_t dust_crc16_calculate(dust_packet_t *packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    if (packet != NULL)
    {
        uint32_t data_size = (packet->header.length == DUST_LENGTH_BYTE32)  ?  32 :
                             (packet->header.length == DUST_LENGTH_BYTE64)  ?  64 :
                             (packet->header.length == DUST_LENGTH_BYTE128) ? 128 : 256;
        uint8_t  serialized[DUST_PACKET_HEADER_SIZE + data_size + DUST_PACKET_CRC16_SIZE] = { 0 };
        uint32_t position = 0;

        result = dust_serialize(packet, &serialized);
        if (result == DUST_RESULT_SUCCESS)
        {
            packet->crc16 = 0;
            for (uint32_t i = 0; i < (DUST_PACKET_HEADER_SIZE + data_size); i++)
            {
                /* Equal to ((packet->crc16 ^ (b << 8)) >> 8) */
                position      = ((packet->crc16 >> 8) ^ serialized[i]);
                packet->crc16 = ((packet->crc16 << 8) ^ dust_crc16_lut[position]);
            }

            /* Serialize crc16 value. */
            serialized[DUST_SERIALIZED_DATA_POSITION + index]     = ((packet->crc16 & 0xff00) >> 0x08);
            serialized[DUST_SERIALIZED_DATA_POSITION + index + 1] = ((packet->crc16 & 0x00ff) >> 0x00);
        }

    }

    return result;
}

dust_result_t dust_transmit(dust_packet_t *packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}

dust_result_t dust_receive(dust_packet_t **packet)
{
    dust_result_t result = DUST_RESULT_ERROR;

    return result;
}
