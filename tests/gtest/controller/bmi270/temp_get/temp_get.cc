#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_temp_get test fixture class.
///
class gtest_bmi270_temp_get : public ::testing::Test
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
                int16_t temp = 0xcafe;
                (void)bmi270_temp_set(dev, temp);
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                int16_t temp = 0x0000;
                (void)bmi270_temp_set(dev, temp);
            }
        }

        static bmi270_dev *dev;
};

struct bmi270_dev *gtest_bmi270_temp_get::dev = nullptr;

///
/// \brief This test performs the bmi270 temperature get procedure.
///
TEST_F(gtest_bmi270_temp_get, procedure)
{
    bmi270_res_t res;
    int16_t temp;

    res = bmi270_temp_get(gtest_bmi270_temp_get::dev, &temp);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(temp, (int16_t)0xcafe);
}

///
/// \brief This test checks the null pointer protection inside bmi270 temperature get function.
///
TEST_F(gtest_bmi270_temp_get, null_pointer_protection)
{
    bmi270_res_t res;
    int16_t temp;

    res = bmi270_temp_get(NULL, &temp);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_temp_get(gtest_bmi270_temp_get::dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
