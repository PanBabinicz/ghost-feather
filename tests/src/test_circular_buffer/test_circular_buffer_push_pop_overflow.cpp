#include "CppUTest/TestHarness.h"

extern "C"
{
#include "data_structure/circular_buffer.h"
}

TEST_GROUP(test_circular_buffer_push_pop_overflow)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(test_circular_buffer_push_pop_overflow, test_circular_buffer_push_pop_overflow)
{
    circular_buffer_result_t result;
    uint8_t push_data = 0x00;
    uint8_t pop_data = 0x00;

    for (size_t element = 0; element < CIRCULAR_BUFFER_LENGTH + 1; element++)
    {
        push_data++;
        result = circular_buffer_push(CIRCULAR_BUFFER_INSTANCE_0, push_data);
        CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_SUCCESS, result);
    }

    // buffer -> | 9 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
    push_data = 2;
    for (size_t element = 0; element < CIRCULAR_BUFFER_LENGTH; element++)
    {
        // If last element, change the push data value.
        if (element == CIRCULAR_BUFFER_LENGTH - 1)
        {
            push_data = 1;
        }
        push_data++;
        result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, &pop_data);
        CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_SUCCESS, result);
        CHECK_EQUAL(push_data, pop_data);
    }
}
