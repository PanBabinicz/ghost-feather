#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_time_read test fixture class.
///
class gtest_bmi270_time_read : public ::testing::Test
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
                /* It is not important what data goes inside fifo after that.
                 * For example bmi270_acc_read function will push register address
                 * to fifo during transmission. The fifo has two indexes, rx and tx.
                 * It always starts reading from rx_idx which is 0. */
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0xb0;
                SPI_DR_ARR[SPI1].buf[2] = 0x0b;
                SPI_DR_ARR[SPI1].buf[3] = 0xed;
                SPI_DR_ARR[SPI1].tx_idx = 0x04;
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0x00;
                SPI_DR_ARR[SPI1].buf[2] = 0x00;
                SPI_DR_ARR[SPI1].buf[3] = 0x00;
                SPI_DR_ARR[SPI1].tx_idx = 0x00;
            }
        }

        static bmi270_dev *dev;
};

struct bmi270_dev *gtest_bmi270_time_read::dev = nullptr;

///
/// \brief This test performs the bmi270 time read procedure.
///
TEST_F(gtest_bmi270_time_read, procedure)
{
    bmi270_res_t res;
    uint32_t time;

    res = bmi270_spi_ctrl_asg(gtest_bmi270_time_read::dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_time_read(gtest_bmi270_time_read::dev);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_time_get(gtest_bmi270_time_read::dev, &time);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(time, 0xb00bed);
}

///
/// \brief This test checks the null pointer protection inside bmi270 time read function.
///
TEST_F(gtest_bmi270_time_read, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_time_read(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
