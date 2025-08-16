#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

class gtest_bmi270_stat_get : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                struct bmi270_dev *dev = bmi270_get_dev();
                bmi270_stat_t stat = BMI270_STAT_INIT;

                (void)bmi270_stat_set(dev, stat);
            }
        }
};

///
/// \brief This test performs the bmi270 status get procedure.
///
TEST_F(gtest_bmi270_stat_get, procedure)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_stat_get(dev, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(stat, BMI270_STAT_INIT);
}

///
/// \brief This test checks the null pointer protection inside bmi270 status
///        get function.
///
TEST_F(gtest_bmi270_stat_get, null_pointer_protection)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_stat_get(NULL, &stat);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_stat_get(dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
