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
