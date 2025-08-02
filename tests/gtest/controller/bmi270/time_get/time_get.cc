#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

class gtest_bmi270_time_get : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                struct bmi270_dev *dev = bmi270_get_dev();
                uint32_t time = 0x00dead00;

                (void)bmi270_time_set(dev, time);
            }
        }
};

TEST_F(gtest_bmi270_time_get, procedure)
{
    bmi270_res_t res;
    uint32_t time;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_time_get(dev, &time);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(time, 0x00dead00);
}

///
/// \brief This test checks the null pointer protection inside bmi270 deinit function.
///
TEST_F(gtest_bmi270_time_get, null_pointer_protection)
{
    bmi270_res_t res;
    uint32_t time;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_time_get(NULL, &time);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_time_get(dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
