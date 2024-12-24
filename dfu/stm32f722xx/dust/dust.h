#ifndef _DUST_H
#define _DUST_H

#include <stdint.h>
#include <string.h>

#define DUST_PACKET_DATA_BUFFER_MAX_SIZE    (0x0100u)
#define DUST_PACKET_HEADER_SIZE             (0x0004u)
#define DUST_PACKET_CRC16_SIZE              (0x0002u)
#define DUST_PACKET_HEADER_POSITION         (0x0000u)
#define DUST_PACKET_DATA_POSITION           (0x0004u)
#define DUST_CRC16_LUT_SIZE                 (0x0100u)

///
/// \breif The dust result type.
///
typedef enum
{
    DUST_RESULT_SUCCESS = 0,
    DUST_RESULT_SERIALIZATION_ERROR,
    DUST_RESULT_SIZE_ERROR,
    DUST_RESULT_ERROR,
} dust_result_t;

///
/// \breif The dust opcode type.
///
typedef enum
{
    DUST_OPCODE_CONNECT = 0,
    DUST_OPCODE_DISCONNECT,
    DUST_OPCODE_DATA,
    DUST_OPCODE_ERROR,
} dust_opcode_t;

///
/// \breif The dust length type.
///
typedef enum
{
    DUST_LENGTH_BYTES32 = 0,
    DUST_LENGTH_BYTES64,
    DUST_LENGTH_BYTES128,
    DUST_LENGTH_BYTES256,
} dust_length_t;

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
    uint16_t      data_size;
} dust_packet_t;

///
/// \brief Generate lookup table for given crc16 generator polynomial.
///
/// \param[in] polynomial The generator polynomial.
///
void dust_crc16_generate_lut(const uint16_t polynomial);

///
/// \brief Create dust header.
///
/// \param[out] header          The dust header structure.
/// \param[in]  opcode          The dust header opcode.
/// \param[in]  length          The dust header length.
/// \param[in]  packet_number   The dust header packet number.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_header_create(dust_header_t *const header, const dust_opcode_t opcode,
                                 const dust_length_t length, const uint16_t packet_number);

///
/// \brief Create dust packet.
///
/// \param[out] packet                      The dust packet structure.
/// \param[in]  header                      The dust header structure.
/// \param[in]  data                        The data buffer.
/// \param[in]  initialize_data_size        The data buffer size.
///
/// \return dust_result_t                   Result of the function.
/// \retval DUST_RESULT_SUCCESS             On success.
/// \retval DUST_RESULT_SERIALIZATION_ERROR On serialization error.
/// \retval DUST_RESULT_ERROR               Otherwise.
///
dust_result_t dust_packet_create(dust_packet_t *const packet, const dust_header_t *const header,
                                 const uint8_t *const data, const uint32_t initialize_data_size);

///
/// \brief Serialize dust packet into bytes stream.
///
/// \param[in]  packet                      The dust packet structure.
/// \param[out] serialized_packet           The serialized packet buffer.
/// \param[in]  serialized_packet_size      The serialized packet buffer size.
///
/// \return dust_result_t                   Result of the function.
/// \retval DUST_RESULT_SUCCESS             On success.
/// \retval DUST_RESULT_SERIALIZATION_ERROR On serialization error.
/// \retval DUST_RESULT_ERROR               Otherwise.
///
dust_result_t dust_serialize(const dust_packet_t *const packet, uint8_t *const serialized_packet,
                             const uint32_t serialized_packet_size);

///
/// \brief Deseralize bytes stream into packet.
///
/// \param[out] packet                      The dust packet structure.
/// \param[in]  data                        The data buffer.
/// \param[in]  data_size                   The data buffer size.
///
/// \return dust_result_t                   Result of the function.
/// \retval DUST_RESULT_SUCCESS             On success.
/// \retval DUST_RESULT_SERIALIZATION_ERROR On serialization error.
/// \retval DUST_RESULT_ERROR               Otherwise.
///
dust_result_t dust_deserialize(dust_packet_t *const packet, const uint8_t *const data,
                               const uint32_t data_size);

///
/// \brief Transmit the serialized packet.
///
/// \param[in] serialized_packet      The serialized packet buffer.
/// \param[in] serialized_packet_size The serialized packet buffer size.
/// \param[in] usart                  The usart block register address base.
///
/// \return dust_result_t             Result of the function.
/// \retval DUST_RESULT_SUCCESS       On success.
/// \retval DUST_RESULT_ERROR         Otherwise.
///
dust_result_t dust_transmit(const uint8_t *serialized_packet, const uint32_t serialized_packet_size,
                            uint32_t usart);

///
/// \brief Receive the packet.
///
/// \param[out] packet          The received dust packet.
/// \param[in]  usart           The usart block register address base.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_receive(uint8_t *const data, uint32_t usart);

#if (defined(DEBUG_DUST_PROTOCOL) && (DEBUG_DUST_PROTOCOL == 1))
///
/// \brief Print the content of the dust header.
///
/// \param[in] packet           The dust header.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_header_printf(const dust_header_t *const header);

///
/// \brief Print the content of the dust packet.
///
/// \param[in] packet           The dust packet.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_packet_printf(const dust_packet_t *const packet);

#endif  /* DEBUG_DUST_PROTOCOL */

#endif  /* _DUST_H */
