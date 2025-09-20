#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "dust.h"

///
/// \brief This test transmits the serialized data.
///
TEST(gtest_dust_transmission, serialized_data)
{
    dust_result_t result;
    dust_serialized_t serialized =
    {
        .buffer =
        {
            0x58, 0x01, 0xa7, 0xfe,  0x00, 0x01, 0x02, 0x03,
            0x04, 0x05, 0x06, 0x07,  0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00,  0xad, 0x8a
        },
        .buffer_size = DUST_PACKET_HEADER_SIZE + 32 + DUST_PACKET_CRC16_SIZE
    };

    uint32_t usart = 3;

    result = dust_transmit(&serialized, usart);
    EXPECT_EQ(result, DUST_RESULT_SUCCESS);
}

///
/// \brief This test checks the null pointer protection inside transmit function.
///
TEST(gtest_dust_transmission, null_pointer_protection)
{
    dust_result_t result;

    uint32_t usart = 3;

    result = dust_transmit(NULL, usart);
    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
