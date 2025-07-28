#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"

///
/// \brief This test performs the bmi270 get power mode config procedure.
///
TEST(get_pwr_mode_conf, procedure)
{
    bool test_stat = true;
    const bmi270_pwr_mode_t pwr_mode_array[BMI270_PWR_MODE_TOTAL] =
    {
        BMI270_PWR_MODE_SUSP,
        BMI270_PWR_MODE_CONF,
        BMI270_PWR_MODE_LOW_ACC_ONLY,
        BMI270_PWR_MODE_LOW_GYR_ONLY,
        BMI270_PWR_MODE_LOW_IMU,
        BMI270_PWR_MODE_NORM_ACC_ONLY,
        BMI270_PWR_MODE_NORM_GYR_ONLY,
        BMI270_PWR_MODE_NORM_IMU,
        BMI270_PWR_MODE_PERF_ACC_ONLY,
        BMI270_PWR_MODE_PERF_GYR_ONLY,
        BMI270_PWR_MODE_PERF_IMU,
    };

    for (uint32_t i = BMI270_PWR_MODE_BEGIN; i < BMI270_PWR_MODE_TOTAL; i++)
    {
        const struct bmi270_pwr_mode_conf *pwr_mode_conf =
            bmi270_get_pwr_mode_conf(pwr_mode_array[i]);

        if (pwr_mode_conf == NULL)
        {
            test_stat = false;
            break;
        }
    }

    EXPECT_EQ(test_stat, true);
}

///
/// \brief This test checks the invalid power mode protection insdie bmi270 get power mode
///        config function.
///
TEST(get_pwr_mode_conf, inv_pwr_mode)
{
    bool test_stat = true;
    int32_t inv_pwr_mode = BMI270_PWR_MODE_BEGIN - 1;

    for (uint32_t i = 0; i < 2; i++)
    {
        const struct bmi270_pwr_mode_conf *pwr_mode_conf =
            bmi270_get_pwr_mode_conf((const bmi270_pwr_mode_t)(inv_pwr_mode));

        if (pwr_mode_conf != NULL)
        {
            test_stat = false;
            break;
        }

        inv_pwr_mode = BMI270_PWR_MODE_TOTAL + 1;
    }

    EXPECT_EQ(test_stat, true);
}
