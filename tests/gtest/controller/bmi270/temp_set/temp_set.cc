#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief This test performs the bmi270 temperature set procedure.
///
TEST(gtest_bmi270_temp_set, procedure)
{
    bmi270_res_t res;
    int16_t temp;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_temp_set(dev, 0xbabe);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_temp_get(dev, &temp);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(temp, (int16_t)0xbabe);
}

///
/// \brief This test checks the null pointer protection inside bmi270 temperature set function.
///
TEST(gtest_bmi270_temp_set, null_pointer_protection)
{
    bmi270_res_t res;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_temp_set(NULL, 0xbabe);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
