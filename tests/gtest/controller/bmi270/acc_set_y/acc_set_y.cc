#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_acc_set_y test fixture class.
///
class gtest_bmi270_acc_set_y : public ::testing::Test
{
    protected:
        static void SetUpTestSuite()
        {
            bmi270 = bmi270_dev_get();
        }

        static void TearDownTestSuite()
        {
            bmi270 = nullptr;
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        static struct bmi270_dev *bmi270;
};

struct bmi270_dev *gtest_bmi270_acc_set_y::bmi270 = nullptr;

///
/// \brief This test performs the bmi270 accelerometer set y axis procedure.
///
TEST_F(gtest_bmi270_acc_set_y, procedure)
{
    bmi270_res_t res;
    int16_t y;

    res = bmi270_acc_set_y(gtest_bmi270_acc_set_y::bmi270, 0xdabb);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_acc_get_y(gtest_bmi270_acc_set_y::bmi270, &y);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(y, (int16_t)0xdabb);
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        set y function.
///
TEST_F(gtest_bmi270_acc_set_y, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_acc_set_y(NULL, 0xdabb);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
