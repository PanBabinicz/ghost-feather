#include "CppUTest/TestHarness.h"

extern "C"
{
#include "data_structure/circular_buffer.h"
}

TEST_GROUP(test_circular_buffer_single_push_pop)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(test_circular_buffer_single_push_pop, test_circular_buffer_single_push_pop)
{
    circular_buffer_result_t result;
    uint8_t push_data = 0xff;
    uint8_t pop_data = 0x00;

    result = circular_buffer_push(CIRCULAR_BUFFER_INSTANCE_0, push_data);
    CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_SUCCESS, result);

    result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, &pop_data);
    CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_SUCCESS, result);
    CHECK_EQUAL(push_data, pop_data);
}
