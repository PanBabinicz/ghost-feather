#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

class gtest_bmi270_gyr_get_x : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                struct bmi270_dev *dev = bmi270_get_dev();
                int16_t x = 0xabcd;

                (void)bmi270_gyr_set_x(dev, x);
            }
        }
};

///
/// \brief This test performs the bmi270 gyroscope get x axis procedure.
///
TEST_F(gtest_bmi270_gyr_get_x, procedure)
{
    bmi270_res_t res;
    int16_t x;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_gyr_get_x(dev, &x);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(x, (int16_t)0xabcd);
}

///
/// \brief This test checks the null pointer protection inside bmi270 gyroscope
///        get x function.
///
TEST_F(gtest_bmi270_gyr_get_x, null_pointer_protection)
{
    bmi270_res_t res;
    int16_t x;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_gyr_get_x(NULL, &x);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_gyr_get_x(dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
