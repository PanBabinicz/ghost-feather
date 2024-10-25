#include "CppUTest/TestHarness.h"

extern "C"
{
#include "data_structure/circular_buffer.h"
}

TEST_GROUP(test_circular_buffer_pass_null_element)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(test_circular_buffer_pass_null_element, test_circular_buffer_pass_null_element)
{
    circular_buffer_result_t result;
    uint8_t *pop_data = NULL;

    result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, pop_data);
    CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_NULL_POINTER, result);
}
