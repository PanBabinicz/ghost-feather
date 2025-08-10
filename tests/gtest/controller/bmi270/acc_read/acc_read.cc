#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

///
/// \brief This test performs the bmi270 accelerometer read procedure.
///
TEST(gtest_bmi270_acc_read, procedure)
{
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        read function.
///
TEST(gtest_bmi270_acc_read, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_acc_read(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
