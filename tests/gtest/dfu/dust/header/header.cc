#include <gtest/gtest.h>
#include <stdint.h>
#include "dust.h"

///
/// \brief This test creates the header.
///
TEST(header, create)
{
    dust_result_t result;
    dust_header_t header = { 0 };

    uint16_t expected_checksum;

    expected_checksum = (DUST_OPCODE_DATA << 0x0e)
                      | (DUST_LENGTH_BYTES256 << 0x0c)
                      | (DUST_ACK_SET << 0x0b)
                      | (5 << 0x00);

    expected_checksum = ~expected_checksum;

    result = dust_header_create(&header, DUST_OPCODE_DATA, DUST_LENGTH_BYTES256,
                                DUST_ACK_SET, 5);

    EXPECT_EQ(result, DUST_RESULT_SUCCESS);
    EXPECT_EQ(header.opcode, DUST_OPCODE_DATA);
    EXPECT_EQ(header.length, DUST_LENGTH_BYTES256);
    EXPECT_EQ(header.ack, DUST_ACK_SET);
    EXPECT_EQ(header.packet_number, 5);
    EXPECT_EQ(header.checksum, expected_checksum);
}

///
/// \brief This test checks the null pointer protection inside header function.
///
TEST(header, null_pointer_protection)
{
    dust_result_t result;

    result = dust_header_create(NULL, DUST_OPCODE_DATA, DUST_LENGTH_BYTES256,
                                DUST_ACK_SET, 5);

    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
