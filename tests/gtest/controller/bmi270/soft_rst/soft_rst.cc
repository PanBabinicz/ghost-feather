#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief This test performs the bmi270 soft reset procedure.
///
TEST(gtest_bmi270_soft_rst, procedure)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_spi_ctrl_asg(dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_set(dev, BMI270_STAT_INIT);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(dev, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_INIT);

    res = bmi270_soft_rst(dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(dev, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(stat, BMI270_STAT_DEINIT);
}

///
/// \brief This test checks the null pointer protection inside bmi270 soft
///        reset function.
///
TEST(gtest_bmi270_soft_rst, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_soft_rst(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
