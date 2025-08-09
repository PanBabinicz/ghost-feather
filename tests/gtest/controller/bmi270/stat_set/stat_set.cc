#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

///
/// \brief This test performs the bmi270 status set procedure.
///
TEST(gtest_bmi270_stat_set, procedure)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_stat_set(dev, BMI270_STAT_INIT);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(dev, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(stat, BMI270_STAT_INIT);
}

///
/// \brief This test checks the range of status argument inside bmi270
///        status set procedure.
///
TEST(gtest_bmi270_stat_set, range)
{
    bmi270_res_t res;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_stat_set(dev, (bmi270_stat_t)(BMI270_STAT_BEGIN - 1));
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_stat_set(dev, BMI270_STAT_TOTAL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}

///
/// \brief This test checks the null pointer protection inside bmi270 status
///        set function.
///
TEST(gtest_bmi270_stat_set, null_pointer_protection)
{
    bmi270_res_t res;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_stat_set(NULL, BMI270_STAT_INIT);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
