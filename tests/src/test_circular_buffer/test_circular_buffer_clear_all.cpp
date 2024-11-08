#include "CppUTest/TestHarness.h"

extern "C"
{
#include "data_structure/circular_buffer.h"
}

TEST_GROUP(test_circular_buffer_clear_all)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(test_circular_buffer_clear_all, test_circular_buffer_clear_all)
{
    circular_buffer_result_t result;
    uint8_t push_data = 0xff;
    uint8_t pop_data = 0x00;

    for (uint8_t instance = CIRCULAR_BUFFER_INSTANCE_0;
         instance < CIRCULAR_BUFFER_INSTANCE_TOTAL; instance++)
    {
        result = circular_buffer_push((circular_buffer_instance_t)instance, push_data);
        CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_SUCCESS, result);
    }

    result = circular_buffer_clear_all();
    CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_SUCCESS, result);

    for (uint8_t instance = CIRCULAR_BUFFER_INSTANCE_0;
         instance < CIRCULAR_BUFFER_INSTANCE_TOTAL; instance++)
    {
        result = circular_buffer_pop((circular_buffer_instance_t)instance, &pop_data);
        CHECK_EQUAL(CIRCULAR_BUFFER_RESULT_EMPTY, result);
    }

    CHECK_EQUAL(0x00, pop_data);
}
