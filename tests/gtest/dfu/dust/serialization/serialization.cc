#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "dust.h"

///
/// \brief This test performs packet serialization.
///
TEST(serialization, perform)
{
    dust_result_t result;

    /* Create a dust header. */
    const dust_header_t header =
    {
        .opcode           = DUST_OPCODE_DISCONNECT,
        .length           = DUST_LENGTH_BYTES64,
        .ack              = DUST_ACK_SET,
        .packet_number    = 1,
        .checksum         = 0xa7fe,
    };

    /* Create a dust payload. */
    const dust_payload_t payload =
    {
        .buffer      = { 0, 1, 2, 3, 4, 5, 6, 7 },
        .buffer_size = 32
    };

    /* Create a dust packet. */
    dust_packet_t packet =
    {
        .header  = header,
        .payload = payload,
        .crc16   = 0
    };

    /* Create a dust protocol instance. */
    dust_protocol_instance_t instance =
    {
        .options    = { 0 },
        .packet     = packet,
        .serialized =
        {
            .buffer      = { 0 },
            .buffer_size = DUST_PACKET_HEADER_SIZE + payload.buffer_size + DUST_PACKET_CRC16_SIZE
        }
    };

    /* Create an expected buffer. */
    uint8_t expected_buffer[] =
    {
        0x58, 0x01, 0xa7, 0xfe,  0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0xad, 0x8a
    };

    /* Generate the crc16 look-up table. */
    dust_crc16_generate_lut(0x1021);

    result = dust_serialize(&instance.packet, &instance.serialized.buffer[0], instance.serialized.buffer_size);
    EXPECT_EQ(result, DUST_RESULT_SUCCESS);

    EXPECT_TRUE(memcmp(&expected_buffer[0], &instance.serialized.buffer[0], instance.serialized.buffer_size) == 0);
}

///
/// \brief This test checks the size protection inside serialize function.
///
TEST(serialization, size_protection)
{
    dust_result_t result;

    /* Create a dust payload. */
    const dust_payload_t payload =
    {
        .buffer      = { 0, 1, 2, 3, 4, 5, 6, 7 },
        .buffer_size = 32
    };

    /* Create a dust packet. */
    dust_packet_t packet =
    {
        .header  = { 0 },
        .payload = payload,
        .crc16   = 0
    };

    /* Create a dust protocol instance. */
    dust_protocol_instance_t instance =
    {
        .options    = { 0 },
        .packet     = packet,
        .serialized =
        {
            .buffer      = { 0 },
            .buffer_size = DUST_PACKET_HEADER_SIZE + payload.buffer_size + DUST_PACKET_CRC16_SIZE
        }
    };

    result = dust_serialize(&instance.packet, &instance.serialized.buffer[0], instance.serialized.buffer_size - 1);
    EXPECT_EQ(result, DUST_RESULT_SIZE_ERROR);
}

///
/// \brief This test checks the null pointer protection inside serialize function.
///
TEST(serialization, null_pointer_protection)
{
    dust_result_t result;
    dust_protocol_instance_t instance = { 0 };

    result = dust_serialize(NULL, &instance.serialized.buffer[0], instance.serialized.buffer_size);
    EXPECT_EQ(result, DUST_RESULT_ERROR);

    result = dust_serialize(&instance.packet, NULL, instance.serialized.buffer_size);
    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
