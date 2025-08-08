#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

class gtest_bmi270_acc_get_y : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                struct bmi270_dev *dev = bmi270_get_dev();
                int16_t y = 0xf00d;

                (void)bmi270_acc_set_y(dev, y);
            }
        }
};

///
/// \brief This test performs the bmi270 accelerometer get y axis procedure.
///
TEST_F(gtest_bmi270_acc_get_y, procedure)
{
    bmi270_res_t res;
    int16_t y;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_get_y(dev, &y);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(y, (int16_t)0xf00d);
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        get y function.
///
TEST_F(gtest_bmi270_acc_get_y, null_pointer_protection)
{
    bmi270_res_t res;
    int16_t y;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_get_y(NULL, &y);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_acc_get_y(dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
