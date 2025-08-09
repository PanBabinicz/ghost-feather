#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

class gtest_bmi270_deinit : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                struct bmi270_dev *dev = bmi270_get_dev();
                (void)bmi270_stat_set(dev, BMI270_STAT_INIT);
            }
        }
};

///
/// \brief This test performs the bmi270 deinit procedure.
///
TEST_F(gtest_bmi270_deinit, procedure)
{
    bmi270_res_t  res;
    bmi270_stat_t stat;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    /*
    res = bmi270_stat_get(dev, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_INIT);
    */

    res = bmi270_deinit(dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(dev, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_DEINIT);
}

///
/// \brief This test checks the null pointer protection inside bmi270 deinit function.
///
TEST_F(gtest_bmi270_deinit, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_deinit(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
