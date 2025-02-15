#include <gtest/gtest.h>
#include <stdint.h>
#include "dust.h"

///
/// \brief This test creates the packet.
///
TEST(packet, create)
{
    dust_result_t result;
    dust_packet_t packet = { 0 };
    uint16_t expected_crc16 = 0xad8a;

    const dust_header_t header =
    {
        .opcode           = DUST_OPCODE_DISCONNECT,
        .length           = DUST_LENGTH_BYTES64,
        .ack              = DUST_ACK_SET,
        .packet_number    = 1,
        .checksum         = 0xa7fe,
    };

    const dust_payload_t payload =
    {
        .buffer = { 0, 1, 2, 3, 4, 5, 6, 7 },
        .buffer_size = 32
    };

    /* Prepare the crc16 look-up table. */
    dust_crc16_generate_lut(0x1021);

    result = dust_packet_create(&packet, &header, &payload);
    EXPECT_EQ(result, DUST_RESULT_SUCCESS);

    EXPECT_EQ(packet.payload.buffer[0], 0);
    EXPECT_EQ(packet.payload.buffer[1], 1);
    EXPECT_EQ(packet.payload.buffer[2], 2);
    EXPECT_EQ(packet.payload.buffer[3], 3);
    EXPECT_EQ(packet.payload.buffer[4], 4);
    EXPECT_EQ(packet.payload.buffer[5], 5);
    EXPECT_EQ(packet.payload.buffer[6], 6);
    EXPECT_EQ(packet.payload.buffer[7], 7);

    EXPECT_EQ(packet.header.opcode, DUST_OPCODE_DISCONNECT);
    EXPECT_EQ(packet.header.length, DUST_LENGTH_BYTES64);
    EXPECT_EQ(packet.header.ack, DUST_ACK_SET);
    EXPECT_EQ(packet.header.packet_number, 1);
    EXPECT_EQ(packet.header.checksum, 0xa7fe);

    EXPECT_EQ(packet.crc16, expected_crc16);
}

///
/// \brief This test checks the null pointer protection inside create packet function.
///
TEST(packet, null_pointer_protection)
{
    dust_result_t result;
    dust_packet_t packet = { 0 };

    const dust_header_t  header  = { 0 };
    const dust_payload_t payload = { 0 };

    /* Prepare the crc16 look-up table. */
    dust_crc16_generate_lut(0x1021);

    result = dust_packet_create(NULL, &header, &payload);
    EXPECT_EQ(result, DUST_RESULT_ERROR);

    result = dust_packet_create(&packet, NULL, &payload);
    EXPECT_EQ(result, DUST_RESULT_ERROR);

    result = dust_packet_create(&packet, &header, NULL);
    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
