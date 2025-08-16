#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

class gtest_bmi270_acc_get_z : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                struct bmi270_dev *dev = bmi270_get_dev();
                int16_t z = 0xc0de;

                (void)bmi270_acc_set_z(dev, z);
            }
        }
};

///
/// \brief This test performs the bmi270 accelerometer get z axis procedure.
///
TEST_F(gtest_bmi270_acc_get_z, procedure)
{
    bmi270_res_t res;
    int16_t z;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_get_z(dev, &z);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(z, (int16_t)0xc0de);
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        get z function.
///
TEST_F(gtest_bmi270_acc_get_z, null_pointer_protection)
{
    bmi270_res_t res;
    int16_t z;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_acc_get_z(NULL, &z);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_acc_get_z(dev, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
