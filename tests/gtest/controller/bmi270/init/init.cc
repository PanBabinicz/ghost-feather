#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

class gtest_bmi270_init : public ::testing::Test
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
/// \brief This test performs the bmi270 init procedure.
///
TEST_F(gtest_bmi270_init, procedure)
{
}

///
/// \brief This test checks the null pointer protection inside bmi270 init function.
///
TEST_F(gtest_bmi270_init, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_init(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
