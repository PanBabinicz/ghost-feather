#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"
#include "spi_ctrl.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_soft_rst test fixture class.
///
class gtest_bmi270_soft_rst : public ::testing::Test
{
    protected:
        static void SetUpTestSuite()
        {
            spi_ctrl = spi_ctrl_dev_get();
            (void)spi_ctrl_dev_init(spi_ctrl);

            bmi270 = bmi270_dev_get();
        }

        static void TearDownTestSuite()
        {
            spi_ctrl = spi_ctrl_dev_get();
            (void)spi_ctrl_dev_deinit(spi_ctrl);

            bmi270 = nullptr;
            spi_ctrl = nullptr;
        }

        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                (void)bmi270_stat_set(bmi270, BMI270_STAT_INIT);
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                (void)bmi270_stat_set(bmi270, BMI270_STAT_DEINIT);
            }
        }

        static struct bmi270_dev *bmi270;
        static struct spi_ctrl_dev *spi_ctrl;
};

struct bmi270_dev   *gtest_bmi270_soft_rst::bmi270   = nullptr;
struct spi_ctrl_dev *gtest_bmi270_soft_rst::spi_ctrl = nullptr;

///
/// \brief This test performs the bmi270 soft reset procedure.
///
TEST_F(gtest_bmi270_soft_rst, procedure)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    res = bmi270_spi_ctrl_asg(gtest_bmi270_soft_rst::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(gtest_bmi270_soft_rst::bmi270, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_INIT);

    res = bmi270_soft_rst(gtest_bmi270_soft_rst::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(gtest_bmi270_soft_rst::bmi270, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_DEINIT);
}

///
/// \brief This test checks the null pointer protection inside bmi270 soft
///        reset function.
///
TEST_F(gtest_bmi270_soft_rst, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_soft_rst(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
