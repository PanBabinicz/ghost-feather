#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_gyr_set_x test fixture class.
///
class gtest_bmi270_gyr_set_x : public ::testing::Test
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

struct bmi270_dev *gtest_bmi270_gyr_set_x::dev = nullptr;

///
/// \brief This test performs the bmi270 gyroscope set x axis procedure.
///
TEST_F(gtest_bmi270_gyr_set_x, procedure)
{
    bmi270_res_t res;
    int16_t x;

    res = bmi270_gyr_set_x(gtest_bmi270_gyr_set_x::dev, 0xd00d);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_gyr_get_x(gtest_bmi270_gyr_set_x::dev, &x);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(x, (int16_t)0xd00d);
}

///
/// \brief This test checks the null pointer protection inside bmi270 gyroscope
///        set x function.
///
TEST_F(gtest_bmi270_gyr_set_x, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_gyr_set_x(NULL, 0xd00d);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
