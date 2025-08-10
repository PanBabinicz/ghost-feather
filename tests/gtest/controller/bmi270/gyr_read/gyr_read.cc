#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

///
/// \brief This test performs the bmi270 gyroscope read procedure.
///
TEST(gtest_bmi270_gyr_read, procedure)
{
}

///
/// \brief This test checks the null pointer protection inside bmi270 gyroscope
///        read function.
///
TEST(gtest_bmi270_gyr_read, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_gyr_read(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
