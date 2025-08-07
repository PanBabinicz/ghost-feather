#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

///
/// \brief This test performs the bmi270 accelerometer set x axis procedure.
///
TEST(gtest_bmi270_acc_set_x, procedure)
{
    bmi270_res_t res;
    int16_t x;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_set_x(dev, 0xea5e);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_acc_get_x(dev, &x);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(x, (int16_t)0xea5e);
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        set x function.
///
TEST(gtest_bmi270_acc_set_x, null_pointer_protection)
{
    bmi270_res_t res;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_set_x(NULL, 0xea5e);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
