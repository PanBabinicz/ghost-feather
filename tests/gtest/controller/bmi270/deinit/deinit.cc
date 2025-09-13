#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_deinit test fixture class.
///
class gtest_bmi270_deinit : public ::testing::Test
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
};

struct bmi270_dev *gtest_bmi270_deinit::bmi270 = nullptr;

///
/// \brief This test performs the bmi270 deinit procedure.
///
TEST_F(gtest_bmi270_deinit, procedure)
{
    bmi270_res_t  res;
    bmi270_stat_t stat;

    res = bmi270_stat_get(gtest_bmi270_deinit::bmi270, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_INIT);

    res = bmi270_deinit(gtest_bmi270_deinit::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(gtest_bmi270_deinit::bmi270, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_DEINIT);
}

///
/// \brief This test checks the null pointer protection inside bmi270 deinit function.
///
TEST_F(gtest_bmi270_deinit, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_deinit(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
