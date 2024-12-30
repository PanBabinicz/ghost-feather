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
/// \breif The dust length type.
///
typedef enum
{
    DUST_ACK_UNSET = 0,
    DUST_ACK_SET,
} dust_ack_t;

///
/// \breif The dust packet ACK frequency type.
///
typedef enum
{
    DUST_ACK_FREQUENCY_AFTER_EACH_PACKET = 0,
    DUST_ACK_FREQUENCY_AFTER_8_PACKETS,
    DUST_ACK_FREQUENCY_AFTER_16_PACKETS,
    DUST_ACK_FREQUENCY_AFTER_32_PACKETS,
    DUST_ACK_FREQUENCY_AFTER_64_PACKETS,
    DUST_ACK_FREQUENCY_AFTER_128_PACKETS,
    DUST_ACK_FREQUENCY_AFTER_256_PACKETS,
    DUST_ACK_FREQUENCY_AFTER_512_PACKETS,
} dust_ack_frequency_t;

///
/// \breif The dust header type.
///
typedef struct
{
    uint32_t opcode        : 2;
    uint32_t length        : 2;
    uint32_t ack           : 1;
    uint32_t packet_number : 11;
    uint32_t checksum      : 16;
} dust_header_t;

///
/// \breif The dust payload type.
///
typedef struct
{
    uint8_t  buffer[DUST_PACKET_PAYLOAD_BUFFER_MAX_SIZE];
    uint16_t buffer_size;
} dust_payload_t;

///
/// \breif The dust packet type.
///
typedef struct
{
    dust_header_t  header;
    dust_payload_t payload;
    uint16_t       crc16;
} dust_packet_t;

///
/// \breif The dust handshake options type.
///
typedef struct
{
    uint8_t  ack_frequency;
    uint32_t number_of_packets;
    uint16_t payload_size;
} dust_handshake_options_t;

///
/// \breif The dust protocol instance type.
///
typedef struct
{
    dust_handshake_options_t options;
    dust_packet_t            packet;
} dust_protocol_instance_t;

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
/// \param[in]  ack             The dust header ack flag.
/// \param[in]  packet_number   The dust header packet number.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_header_create(dust_header_t *const header, const dust_opcode_t opcode,
                                 const dust_length_t length, const dust_ack_t ack,
                                 const uint16_t packet_number);

///
/// \brief Create dust payload.
///
/// \param[out] payload                     The dust packet structure.
/// \param[in]  data                        The data buffer.
/// \param[in]  initialize_data_size        The data buffer size.
///
/// \return dust_result_t                   Result of the function.
/// \retval DUST_RESULT_SUCCESS             On success.
/// \retval DUST_RESULT_ERROR               Otherwise.
///
dust_result_t dust_payload_create(dust_payload_t *const payload, const uint8_t *const data,
                                  const uint32_t initialize_data_size);

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
dust_result_t dust_packet_create(dust_protocol_instance_t *const instance, const dust_header_t *const header,
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
                            const uint32_t usart);

///
/// \brief Receive the packet.
///
/// \param[out] instance        The received dust packet.
/// \param[in]  usart           The usart block register address base.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_receive(dust_protocol_instance_t *const instance, const uint32_t usart);

///
/// \brief Dust handshake procedure.
///
/// \param[out] options         The received handshake opitons.
/// \param[out] packet          The received dust packet.
/// \param[in]  usart           The usart block register address base.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_handshake(dust_protocol_instance_t *const instance, const uint32_t usart);

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
