#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_gyr_set_y test fixture class.
///
class gtest_bmi270_gyr_set_y : public ::testing::Test
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

struct bmi270_dev *gtest_bmi270_gyr_set_y::dev = nullptr;

///
/// \brief This test performs the bmi270 gyroscope set y axis procedure.
///
TEST_F(gtest_bmi270_gyr_set_y, procedure)
{
    bmi270_res_t res;
    int16_t y;

    res = bmi270_gyr_set_y(gtest_bmi270_gyr_set_y::dev, 0xf00d);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_gyr_get_y(gtest_bmi270_gyr_set_y::dev, &y);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(y, (int16_t)0xf00d);
}

///
/// \brief This test checks the null pointer protection inside bmi270 gyroscope
///        set y function.
///
TEST_F(gtest_bmi270_gyr_set_y, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_gyr_set_y(NULL, 0xf00d);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
