#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_pwr_mode_get_conf test fixture class.
///
class gtest_bmi270_pwr_mode_get_conf : public ::testing::Test
{
    protected:
        static void SetUpTestSuite()
        {
            dev = bmi270_dev_get();
        }

        static void TearDownTestSuite()
        {
            dev = nullptr;
        }

        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                (void)bmi270_stat_set(dev, BMI270_STAT_INIT);
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                (void)bmi270_stat_set(dev, BMI270_STAT_DEINIT);
            }
        }

        static bmi270_dev *dev;
};

struct bmi270_dev *gtest_bmi270_pwr_mode_get_conf::dev = nullptr;

///
/// \brief This test performs the bmi270 power mode get config procedure.
///
TEST(gtest_bmi270_pwr_mode_get_conf, procedure)
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
            bmi270_pwr_mode_get_conf(pwr_mode_array[i]);

        if (pwr_mode_conf == NULL)
        {
            test_stat = false;
            break;
        }
    }

    EXPECT_EQ(test_stat, true);
}

///
/// \brief This test checks the invalid power mode protection inside bmi270 power
///        mode get config function.
///
TEST(gtest_bmi270_pwr_mode_get_conf, inv_pwr_mode)
{
    bool test_stat = true;
    int32_t inv_pwr_mode = BMI270_PWR_MODE_BEGIN - 1;

    for (uint32_t i = 0; i < 2; i++)
    {
        const struct bmi270_pwr_mode_conf *pwr_mode_conf =
            bmi270_pwr_mode_get_conf((const bmi270_pwr_mode_t)(inv_pwr_mode));

        if (pwr_mode_conf != NULL)
        {
            test_stat = false;
            break;
        }

        inv_pwr_mode = BMI270_PWR_MODE_TOTAL + 1;
    }

    EXPECT_EQ(test_stat, true);
}
