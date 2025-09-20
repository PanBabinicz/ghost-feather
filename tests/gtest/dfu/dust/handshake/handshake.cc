#include <gtest/gtest.h>
#include <stdint.h>
#include "dust.h"

///
/// \brief This test performs the handshake procedure.
///
TEST(gtest_dust_handshake, procedure)
{
    uint32_t usart = 3;
    uint8_t  expected_ack_frequency     = (1 << 0x00);
    uint32_t expected_number_of_packets = (1 << 0x18) | (1 << 0x10) | (1 << 0x08) | (1 << 0x00);
    uint16_t expected_payload_size      = (1 << 0x08) | (1 << 0x00);

    dust_protocol_instance_t instance = { 0 };
    dust_result_t result;

    /* usart_recv mock function returns always 1. */
    result = dust_handshake(&instance, usart);

    EXPECT_EQ(result, DUST_RESULT_SUCCESS);
    EXPECT_EQ(instance.options.ack_frequency, expected_ack_frequency);
    EXPECT_EQ(instance.options.number_of_packets, expected_number_of_packets);
    EXPECT_EQ(instance.options.payload_size, expected_payload_size);
}

///
/// \brief This test checks the null pointer protection inside handshake function.
///
TEST(gtest_dust_handshake, null_pointer_protection)
{
    uint32_t usart = 3;
    dust_result_t result;

    result = dust_handshake(NULL, usart);

    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
