#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_acc_get_x test fixture class.
///
class gtest_bmi270_acc_get_x : public ::testing::Test
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
                int16_t x = 0xcaca;
                (void)bmi270_acc_set_x(dev, x);
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                int16_t x = 0x0000;
                (void)bmi270_acc_set_x(dev, x);
            }
        }

        static bmi270_dev *dev;
};

struct bmi270_dev *gtest_bmi270_acc_get_x::dev = nullptr;

///
/// \brief This test performs the bmi270 accelerometer get x axis procedure.
///
TEST_F(gtest_bmi270_acc_get_x, procedure)
{
    bmi270_res_t res;
    int16_t x;

    res = bmi270_acc_get_x(gtest_bmi270_acc_get_x::dev, &x);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(x, (int16_t)0xcaca);
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        get x function.
///
TEST_F(gtest_bmi270_acc_get_x, null_pointer_protection)
{
    bmi270_res_t res;
    int16_t x;

    res = bmi270_acc_get_x(NULL, &x);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_acc_get_x(gtest_bmi270_acc_get_x::dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
