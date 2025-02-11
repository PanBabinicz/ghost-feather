#include <gtest/gtest.h>
#include <stdint.h>
#include "data_structure/circular_buffer.h"

///
/// \brief This test pushes single element.
///
TEST(push, single)
{
    circular_buffer_result_t result;
    uint8_t buffer[CIRCULAR_BUFFER_LENGTH];

    result = circular_buffer_push(CIRCULAR_BUFFER_INSTANCE_0, 0x01);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);

    result = circular_buffer_get_data(CIRCULAR_BUFFER_INSTANCE_0, &buffer[0], CIRCULAR_BUFFER_LENGTH);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);

    EXPECT_EQ(buffer[0], 0x01);
}

///
/// \brief This test pushes elements until the buffer is full.
///
TEST(push, full)
{
    circular_buffer_result_t result;
    uint8_t buffer[CIRCULAR_BUFFER_LENGTH];

    for (size_t i = 0; i < CIRCULAR_BUFFER_LENGTH; i++)
    {
        result = circular_buffer_push(CIRCULAR_BUFFER_INSTANCE_0, i);
        EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);
    }

    result = circular_buffer_get_data(CIRCULAR_BUFFER_INSTANCE_0, &buffer[0], CIRCULAR_BUFFER_LENGTH);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);

    for (size_t i = 0; i < CIRCULAR_BUFFER_LENGTH; i++)
    {
        EXPECT_EQ(buffer[i], i);
    }
}
