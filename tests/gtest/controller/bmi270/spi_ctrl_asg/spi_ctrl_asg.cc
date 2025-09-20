#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_spi_ctrl_asg test fixture class.
///
class gtest_bmi270_spi_ctrl_asg : public ::testing::Test
{
    protected:
        static void SetUpTestSuite()
        {
            bmi270 = bmi270_dev_get();
        }

        static void TearDownTestSuite()
        {
            bmi270= nullptr;
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        static struct bmi270_dev *bmi270;
};

struct bmi270_dev *gtest_bmi270_spi_ctrl_asg::bmi270 = nullptr;

///
/// \brief This test performs the bmi270 spi control assign procedure.
///
TEST_F(gtest_bmi270_spi_ctrl_asg, procedure)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    res = bmi270_spi_ctrl_asg(gtest_bmi270_spi_ctrl_asg::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);
}

///
/// \brief This test checks the null pointer protection inside bmi270 spi
///        control assign function.
///
TEST_F(gtest_bmi270_spi_ctrl_asg, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_spi_ctrl_asg(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
