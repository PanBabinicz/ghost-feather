#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

///
/// \brief This test performs the bmi270 accelerometer self test procedure.
///
TEST(gtest_bmi270_acc_slf_tst, procedure)
{
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        self test function.
///
TEST(gtest_bmi270_acc_slf_tst, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_acc_slf_tst(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
