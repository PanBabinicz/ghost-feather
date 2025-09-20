#include <gtest/gtest.h>
#include <stdint.h>
#include <string.h>
#include "dust.h"

///
/// \brief This test receives the serialized data.
///
TEST(gtest_dust_reception, serialized_data)
{
    dust_result_t result;
    dust_serialized_t serialized =
    {
        .buffer = { 0 },
        .buffer_size = DUST_PACKET_HEADER_SIZE + 32 + DUST_PACKET_CRC16_SIZE
    };

    uint32_t usart = 3;

    result = dust_receive(&serialized, usart);
    EXPECT_EQ(result, DUST_RESULT_SUCCESS);

    for (size_t i = 0; i < serialized.buffer_size; i++)
    {
        /* The usart_receive always returns 0x01. */
        EXPECT_EQ(serialized.buffer[i], 0x01);
    }
}

///
/// \brief This test checks the null pointer protection inside receive function.
///
TEST(gtest_dust_reception, null_pointer_protection)
{
    dust_result_t result;

    uint32_t usart = 3;

    result = dust_receive(NULL, usart);
    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
