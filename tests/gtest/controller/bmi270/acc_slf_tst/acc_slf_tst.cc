#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_acc_slf_tst test fixture class.
///
class gtest_bmi270_acc_slf_tst : public ::testing::Test
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

struct bmi270_dev *gtest_bmi270_acc_slf_tst::dev = nullptr;

///
/// \brief This test performs the bmi270 accelerometer self test procedure.
///
TEST(gtest_bmi270_acc_slf_tst, procedure)
{
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        self test function.
///
TEST(gtest_bmi270_acc_slf_tst, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_acc_slf_tst(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
