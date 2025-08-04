#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

class gtest_bmi270_temp_get : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                struct bmi270_dev *dev = bmi270_get_dev();
                int16_t temp = 0xcafe;

                (void)bmi270_temp_set(dev, temp);
            }
        }
};

///
/// \brief This test performs the bmi270 temperature get procedure.
///
TEST_F(gtest_bmi270_temp_get, procedure)
{
    bmi270_res_t res;
    int16_t temp;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_temp_get(dev, &temp);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(temp, (int16_t)0xcafe);
}

///
/// \brief This test checks the null pointer protection inside bmi270 temperature get function.
///
TEST_F(gtest_bmi270_temp_get, null_pointer_protection)
{
    bmi270_res_t res;
    int16_t temp;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_temp_get(NULL, &temp);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_temp_get(dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
