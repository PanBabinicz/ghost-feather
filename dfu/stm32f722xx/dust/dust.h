#ifndef _DUST_H
#define _DUST_H

#include <stdint.h>

#define DUST_PACKET_DATA_BUFFER_MAX_SIZE    (0xffu)
#define DUST_PACKET_HEADER_SIZE             (0x04u)
#define DUST_PACKET_CRC16_SIZE              (0x02u)
#define DUST_SERIALIZED_HEADER_POSITION     (0x00u)
#define DUST_SERIALIZED_DATA_POSITION       (0x04u)
#define DUST_CRC16_LUT_SIZE                 (0xffu)

///
/// \breif The dust result type.
///
typedef enum
{
    DUST_RESULT_SUCCESS = 0,
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
void dust_crc16_generate_lut(uint16_t polynomial);

///
/// \brief Calculate the crc16.
///
/// \param[in]  packet      The dust packet structure.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_crc16_calculate(dust_packet_t *packet)

///
/// \brief Create dust header.
///
/// \param[out] header        The dust header structure.
/// \param[in]  opcode        The dust header opcode.
/// \param[in]  length        The dust header length.
/// \param[in]  packet_number The dust header packet number.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_header_create(dust_header_t *header, dust_opcode_t opcode,
                                 dust_length_t length, uint16_t packet_number);

///
/// \brief Create dust packet.
///
/// \param[out] packet               The dust packet structure.
/// \param[in]  header               The dust header structure.
/// \param[in]  data                 The data buffer.
/// \param[in]  initialize_data_size The data buffer size.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_packet_create(dust_packet_t *packet, dust_header_t *header,
                                 uint8_t *data, uint32_t initialize_data_size);

///
/// \brief Transmit the packet.
///
/// \param[in] packet The dust packet.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_transmit(dust_packet_t *packet);

///
/// \brief Receive the packet.
///
/// \param[out] packet The received dust packet.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_receive(dust_packet_t **packet);

#endif  /* _DUST_H */
