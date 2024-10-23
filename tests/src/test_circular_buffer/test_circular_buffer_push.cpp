#include "CppUTest/TestHarness.h"

extern "C"
{
#include "data_structure/circular_buffer.h"
}

TEST_GROUP(test_circular_buffer_push)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(test_circular_buffer_push, test_circular_buffer_push)
{
    uint8_t status = 0;

    CHECK_EQUAL(0, status);
}
