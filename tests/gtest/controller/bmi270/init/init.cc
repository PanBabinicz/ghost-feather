#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "bmi270_conf.h"
#include "libopencm3/stm32/spi_common.h"
#include "spi_ctrl.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_init test fixture class.
///
class gtest_bmi270_init : public ::testing::Test
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
                /* It is not important what data goes inside fifo after that.
                 * For example bmi270_acc_read function will push register address
                 * to fifo during transmission. The fifo has two indexes, rx and tx.
                 * It always starts reading from rx_idx which is 0. */

                /* buf[0] and buf[1] will be discarded. */
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0x00;

                /* Wait previous time. */
                SPI_DR_ARR[SPI1].buf[2] = 0x00;
                SPI_DR_ARR[SPI1].buf[3] = 0x00;
                SPI_DR_ARR[SPI1].buf[4] = 0x00;
                SPI_DR_ARR[SPI1].buf[5] = 0x00;

                /* Wait current time. */
                SPI_DR_ARR[SPI1].buf[6] = 0x00;
                SPI_DR_ARR[SPI1].buf[7] = 0x00;
                SPI_DR_ARR[SPI1].buf[8] = 0x00;
                SPI_DR_ARR[SPI1].buf[9] = 0x0d;

                /* Config file. */
                SPI_DR_ARR[SPI1].buf[10] = 0x00;
                memcpy(&SPI_DR_ARR[SPI1].buf[11], &bmi270_conf_file[0], sizeof(bmi270_conf_file));

                /* Internal status register value. */
                SPI_DR_ARR[SPI1].buf[12 + sizeof(bmi270_conf_file)] = 0x00;
                SPI_DR_ARR[SPI1].buf[13 + sizeof(bmi270_conf_file)] = 0x01;

                /* Set tx_idx to point to first the unoccupied place in the buffer. */
                SPI_DR_ARR[SPI1].tx_idx = 14 + sizeof(bmi270_conf_file);

                (void)bmi270_stat_set(bmi270, BMI270_STAT_DEINIT);
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                memset(&SPI_DR_ARR[SPI1].buf[0], 0, sizeof(SPI_DR_ARR[SPI1].buf));
                (void)bmi270_stat_set(bmi270, BMI270_STAT_DEINIT);
            }
        }

        static struct bmi270_dev *bmi270;
        static struct spi_ctrl_dev *spi_ctrl;
};

struct bmi270_dev   *gtest_bmi270_init::bmi270   = nullptr;
struct spi_ctrl_dev *gtest_bmi270_init::spi_ctrl = nullptr;

///
/// \brief This test performs the bmi270 init procedure.
///
TEST_F(gtest_bmi270_init, procedure)
{
    bmi270_res_t res;
    bmi270_stat_t stat;

    res = bmi270_stat_get(gtest_bmi270_init::bmi270, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_DEINIT);

    res = bmi270_spi_ctrl_asg(gtest_bmi270_init::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_init(gtest_bmi270_init::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_stat_get(gtest_bmi270_init::bmi270, &stat);
    EXPECT_EQ(res, BMI270_RES_OK);
    EXPECT_EQ(stat, BMI270_STAT_INIT);
}

///
/// \brief This test checks the null pointer protection inside bmi270 init function.
///
TEST_F(gtest_bmi270_init, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_init(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
