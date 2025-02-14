#include <gtest/gtest.h>
#include <stdint.h>
#include "data_structure/circular_buffer.h"

class pop : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("single"))
            {
                uint8_t buffer[CIRCULAR_BUFFER_LENGTH];

                buffer[0] = 0x01;

                (void)circular_buffer_set_data(CIRCULAR_BUFFER_INSTANCE_0, &buffer[0],
                                               CIRCULAR_BUFFER_LENGTH);

                /* rear = 0; front = 1; overflow = 0; */
                (void)circular_buffer_set_state(CIRCULAR_BUFFER_INSTANCE_0, 0, 1, 0);
            }
            else if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                     std::string("all"))
            {
                uint8_t buffer[CIRCULAR_BUFFER_LENGTH];

                for (size_t i = 0; i < CIRCULAR_BUFFER_LENGTH; i++)
                {
                    buffer[i] = i;
                }

                (void)circular_buffer_set_data(CIRCULAR_BUFFER_INSTANCE_0, &buffer[0],
                                               CIRCULAR_BUFFER_LENGTH);

                /* rear = 0; front = 0; overflow = 1; */
                (void)circular_buffer_set_state(CIRCULAR_BUFFER_INSTANCE_0, 0, 0, 1);
            }
            else if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                     std::string("overflow"))
            {
                uint8_t buffer[CIRCULAR_BUFFER_LENGTH];

                for (size_t i = 0; i < CIRCULAR_BUFFER_LENGTH; i++)
                {
                    buffer[i] = i;
                }

                (void)circular_buffer_set_data(CIRCULAR_BUFFER_INSTANCE_0, &buffer[0],
                                               CIRCULAR_BUFFER_LENGTH);

                /* rear = 4; front = 3; overflow = 1; */
                (void)circular_buffer_set_state(CIRCULAR_BUFFER_INSTANCE_0, 4, 3, 1);
            }
        }
};

///
/// \brief This test pops single element.
///
TEST_F(pop, single)
{
    circular_buffer_result_t result;
    uint8_t element;

    result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, &element);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);

    EXPECT_EQ(element, 0x01);
}

///
/// \brief This test pops every element from full circular buffer.
///
TEST_F(pop, all)
{
    circular_buffer_result_t result;
    uint8_t element;

    for (size_t i = 0; i < CIRCULAR_BUFFER_LENGTH; i++)
    {
        result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, &element);
        EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);

        EXPECT_EQ(element, i);
    }
}

///
/// \brief This test pops element from empty circular buffer.
///
TEST_F(pop, empty)
{
    circular_buffer_result_t result;
    uint8_t element = 0xff;

    result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, &element);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_EMPTY);

    EXPECT_EQ(element, 0xff);
}

///
/// \brief This test pops element from overflowed circular buffer.
///
TEST_F(pop, overflow)
{
    circular_buffer_result_t result;
    uint8_t element;

    for (size_t i = 0; i < CIRCULAR_BUFFER_LENGTH; i++)
    {
        result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, &element);
        EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_SUCCESS);

        /* rear starts from fifth element in this scenario. */
        EXPECT_EQ(element, (i + 4) % CIRCULAR_BUFFER_LENGTH);
    }
}

///
/// \brief This test checks the null pointer protection inside pop function.
///
TEST_F(pop, null_pointer_protection)
{
    circular_buffer_result_t result;

    result = circular_buffer_pop(CIRCULAR_BUFFER_INSTANCE_0, NULL);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_NULL_POINTER);
}

///
/// \brief This test checks the invalid instance protection inside pop function.
///
TEST_F(pop, invalid_instance)
{
    circular_buffer_result_t result;
    uint8_t element;

    result = circular_buffer_pop((circular_buffer_instance_t)0xff, &element);
    EXPECT_EQ(result, CIRCULAR_BUFFER_RESULT_INVALID_INSTANCE);
}
