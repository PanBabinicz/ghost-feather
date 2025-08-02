#include <gtest/gtest.h>
#include <stdint.h>
#include "dust.h"

///
/// \brief This test creates the payload.
///
TEST(gtest_dust_payload, create)
{
    dust_result_t result;
    dust_payload_t payload = { 0 };

    const uint8_t data[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    result = dust_payload_create(&payload, &data[0], 8);

    EXPECT_EQ(result, DUST_RESULT_SUCCESS);
    EXPECT_EQ(payload.buffer[0], 0);
    EXPECT_EQ(payload.buffer[1], 1);
    EXPECT_EQ(payload.buffer[2], 2);
    EXPECT_EQ(payload.buffer[3], 3);
    EXPECT_EQ(payload.buffer[4], 4);
    EXPECT_EQ(payload.buffer[5], 5);
    EXPECT_EQ(payload.buffer[6], 6);
    EXPECT_EQ(payload.buffer[7], 7);
}

///
/// \brief This test checks the null pointer protection inside create payload function.
///
TEST(gtest_dust_payload, null_pointer_protection)
{
    dust_result_t result;
    dust_payload_t payload = { 0 };

    const uint8_t data[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    result = dust_payload_create(NULL, &data[0], 8);
    EXPECT_EQ(result, DUST_RESULT_ERROR);

    result = dust_payload_create(&payload, NULL, 8);
    EXPECT_EQ(result, DUST_RESULT_ERROR);
}
