#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_stat_set test fixture class.
///
class gtest_bmi270_stat_set : public ::testing::Test
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

struct bmi270_dev *gtest_bmi270_stat_set::dev = nullptr;

///
/// \brief This test performs the bmi270 status set procedure.
///
TEST_F(gtest_bmi270_stat_set, procedure)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    res = bmi270_stat_set(gtest_bmi270_stat_set::dev, BMI270_STAT_INIT);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(gtest_bmi270_stat_set::dev, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(stat, BMI270_STAT_INIT);
}

///
/// \brief This test checks the range of status argument inside bmi270
///        status set procedure.
///
TEST_F(gtest_bmi270_stat_set, range)
{
    bmi270_res_t res;

    res = bmi270_stat_set(gtest_bmi270_stat_set::dev, (bmi270_stat_t)(BMI270_STAT_BEGIN - 1));
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_stat_set(gtest_bmi270_stat_set::dev, BMI270_STAT_TOTAL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}

///
/// \brief This test checks the null pointer protection inside bmi270 status
///        set function.
///
TEST_F(gtest_bmi270_stat_set, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_stat_set(NULL, BMI270_STAT_INIT);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
