#ifndef _DUST_H
#define _DUST_H

#include <stdint.h>

#define DUST_PACKET_DATA_BUFFER_MAX_SIZE    (256u)

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
} dust_packet_t;

///
/// \brief Generate lookup table for given crc16 generator polynomial.
///
/// \param[in] polynomial The generator polynomial.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_crc16_generate_lut(uint16_t polynomial);

///
/// \brief Calculate the crc16.
///
/// \param[in] packet The dust packet structure.
///
/// \return dust_result_t       Result of the function.
/// \retval DUST_RESULT_SUCCESS On success.
/// \retval DUST_RESULT_ERROR   Otherwise.
///
dust_result_t dust_crc16_calculate(dust_packet_t *packet);

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
