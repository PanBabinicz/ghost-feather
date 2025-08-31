#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_pwr_mode_set test fixture class.
///
class gtest_bmi270_pwr_mode_set : public ::testing::Test
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
        }

        void TearDown() override
        {
        }

        static bmi270_dev *dev;
};

struct bmi270_dev *gtest_bmi270_pwr_mode_set::dev = nullptr;

///
/// \brief This test performs the bmi270 power mode set procedure.
///
TEST_F(gtest_bmi270_pwr_mode_set, procedure)
{
}

///
/// \brief This test checks the null pointer protection inside bmi270
///        power mode set function.
///
TEST_F(gtest_bmi270_pwr_mode_set, null_pointer_protection)
{
    bmi270_res_t res;

    const struct bmi270_pwr_mode_conf *pwr_mode_conf =
      bmi270_pwr_mode_get_conf(BMI270_PWR_MODE_SUSP);

    /* The bmi270 device is NULL. */
    res = bmi270_pwr_mode_set(NULL, pwr_mode_conf);
    EXPECT_EQ(res, BMI270_RES_ERR);

    /* The spi control device is NULL. */
    res = bmi270_pwr_mode_set(gtest_bmi270_pwr_mode_set::dev, pwr_mode_conf);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_spi_ctrl_asg(gtest_bmi270_pwr_mode_set::dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    /* The pwr_mode_conf is NULL. */
    res = bmi270_pwr_mode_set(gtest_bmi270_pwr_mode_set::dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
