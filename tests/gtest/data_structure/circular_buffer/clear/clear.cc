#include <gtest/gtest.h>
#include <stdint.h>
#include "data_structure/circular_buffer.h"

///
/// \brief This test performs the single circular buffer instance clear procedure.
///
TEST(gtest_circ_buf_clear, single)
{
    circular_buffer_result_t result;

    result = circular_buffer_clear(CIRCULAR_BUFFER_INSTANCE_0);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);
}

///
/// \brief This test performs all circular buffer instances clear procedure.
///
TEST(gtest_circ_buf_clear, all)
{
    circular_buffer_result_t result;

    result = circular_buffer_clear_all();
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);
}

///
/// \brief This test checks the invalid instance protection inside clear function.
///
TEST(gtest_circ_buf_clear, invalid_instance)
{
    circular_buffer_result_t result;

    result = circular_buffer_clear((circular_buffer_instance_t)0xff);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE);
}
