#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

///
/// \brief This test performs the bmi270 accelerometer set z axis procedure.
///
TEST(gtest_bmi270_acc_set_z, procedure)
{
    bmi270_res_t res;
    int16_t z;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_set_z(dev, 0xea5e);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_acc_get_z(dev, &z);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(z, (int16_t)0xea5e);
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        set z function.
///
TEST(gtest_bmi270_acc_set_z, null_pointer_protection)
{
    bmi270_res_t res;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_set_z(NULL, 0xea5e);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
