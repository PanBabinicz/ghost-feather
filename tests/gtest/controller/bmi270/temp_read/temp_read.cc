#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

class gtest_bmi270_temp_read : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                /* It is not important what data goes inside fifo after that.
                 * For example bmi270_acc_read function will push register address
                 * to fifo during transmission. The fifo has two indexes, rx and tx.
                 * It always starts reading from rx_idx which is 0. */
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0xad;
                SPI_DR_ARR[SPI1].buf[2] = 0xde;
            }
        }
};

///
/// \brief This test performs the bmi270 temp read procedure.
///
TEST_F(gtest_bmi270_temp_read, procedure)
{
    bmi270_res_t res;
    /* TODO: Check the variable type in struct. */
    int16_t temp;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_spi_ctrl_asg(dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_temp_read(dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_temp_get(dev, &temp);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(temp, (int16_t)(0xdead));
}

///
/// \brief This test checks the null pointer protection inside bmi270 temp read function.
///
TEST_F(gtest_bmi270_temp_read, null_pointer_protection)
{
    bmi270_res_t res;

    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    res = bmi270_temp_read(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
