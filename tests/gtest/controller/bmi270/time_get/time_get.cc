#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_time_get test fixture class.
///
class gtest_bmi270_time_get : public ::testing::Test
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
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                uint32_t time = 0x00dead00;
                (void)bmi270_time_set(dev, time);
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                uint32_t time = 0x00000000;
                (void)bmi270_time_set(dev, time);
            }
        }

        static bmi270_dev *dev;
};

struct bmi270_dev *gtest_bmi270_time_get::dev = nullptr;

///
/// \brief This test performs the bmi270 time get procedure.
///
TEST_F(gtest_bmi270_time_get, procedure)
{
    bmi270_res_t res;
    uint32_t time;

    res = bmi270_time_get(gtest_bmi270_time_get::dev, &time);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(time, 0x00dead00);
}

///
/// \brief This test checks the null pointer protection inside bmi270 time get function.
///
TEST_F(gtest_bmi270_time_get, null_pointer_protection)
{
    bmi270_res_t res;
    uint32_t time;

    res = bmi270_time_get(NULL, &time);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_time_get(gtest_bmi270_time_get::dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
