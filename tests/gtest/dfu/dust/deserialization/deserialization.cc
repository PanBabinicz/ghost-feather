#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "dust.h"

///
/// \brief This test performs packet deserialization.
///
TEST(gtest_dust_deserialization, perform)
{
    dust_result_t result;
    dust_protocol_instance_t instance =
    {
        .options = { 0 },
        .packet  =
        {
            .header  = { 0 },
            .payload =
            {
                .buffer      = { 0 },
                .buffer_size = 32
            },
            .crc16 = 0
        },
        .serialized = { 0 }
    };

    uint8_t serialized_data[] =
    {
        0x58, 0x01, 0xa7, 0xfe,  0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0xad, 0x8a
    };

    /* Generate the crc16 look-up table. */
    dust_crc16_generate_lut(0x1021);

    result = dust_deserialize(&instance.packet, &serialized_data[0], sizeof(serialized_data));
    EXPECT_EQ(result, DUST_RESULT_SUCCESS);

    /* Check header. */
    EXPECT_EQ(instance.packet.header.opcode, DUST_OPCODE_DISCONNECT);
    EXPECT_EQ(instance.packet.header.length, DUST_LENGTH_BYTES64);
    EXPECT_EQ(instance.packet.header.ack, DUST_ACK_SET);
    EXPECT_EQ(instance.packet.header.packet_number, 0x01);
    EXPECT_EQ(instance.packet.header.checksum, 0xa7fe);

    /* Check payload. */
    EXPECT_EQ(instance.packet.payload.buffer[0], 0x00);
    EXPECT_EQ(instance.packet.payload.buffer[1], 0x01);
    EXPECT_EQ(instance.packet.payload.buffer[2], 0x02);
    EXPECT_EQ(instance.packet.payload.buffer[3], 0x03);
    EXPECT_EQ(instance.packet.payload.buffer[4], 0x04);
    EXPECT_EQ(instance.packet.payload.buffer[5], 0x05);
    EXPECT_EQ(instance.packet.payload.buffer[6], 0x06);
    EXPECT_EQ(instance.packet.payload.buffer[7], 0x07);

    /* Check crc16. */
    EXPECT_EQ(instance.packet.crc16, 0xad8a);
}

///
/// \brief This test checks the size protection inside deserialize function.
///
TEST(gtest_dust_deserialization, size_protection)
{
    dust_result_t result;
    dust_protocol_instance_t instance =
    {
        .options = { 0 },
        .packet  =
        {
            .header  = { 0 },
            .payload =
            {
                .buffer      = { 0 },
                .buffer_size = 32
            },
            .crc16 = 0
        },
        .serialized = { 0 }
    };

    uint8_t serialized_data[DUST_PACKET_HEADER_SIZE + 32 + DUST_PACKET_CRC16_SIZE] = { 0 };

    result = dust_deserialize(&instance.packet, &serialized_data[0], sizeof(serialized_data) - 1);
    EXPECT_EQ(result, DUST_RESULT_SIZE_ERROR);
}

///
/// \brief This test checks the null pointer protection inside deserialize function.
///
TEST(gtest_dust_deserialization, null_pointer_protection)
{
    dust_result_t result;
    dust_protocol_instance_t instance = { 0 };

    uint8_t serialized_data[] =
    {
        0x58, 0x01, 0xa7, 0xfe,  0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0xad, 0x8a
    };

    result = dust_deserialize(NULL, &serialized_data[0], sizeof(serialized_data));
    EXPECT_EQ(result, DUST_RESULT_ERROR);

    result = dust_serialize(&instance.packet, NULL, sizeof(serialized_data));
    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
