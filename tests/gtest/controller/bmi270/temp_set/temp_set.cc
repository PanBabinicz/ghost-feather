#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_temp_set test fixture class.
///
class gtest_bmi270_temp_set : public ::testing::Test
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

struct bmi270_dev *gtest_bmi270_temp_set::bmi270 = nullptr;

///
/// \brief This test performs the bmi270 temperature set procedure.
///
TEST_F(gtest_bmi270_temp_set, procedure)
{
    bmi270_res_t res;
    int16_t temp;

    res = bmi270_temp_set(gtest_bmi270_temp_set::bmi270, 0xbabe);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_temp_get(gtest_bmi270_temp_set::bmi270, &temp);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(temp, (int16_t)0xbabe);
}

///
/// \brief This test checks the null pointer protection inside bmi270 temperature set function.
///
TEST_F(gtest_bmi270_temp_set, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_temp_set(NULL, 0xbabe);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
