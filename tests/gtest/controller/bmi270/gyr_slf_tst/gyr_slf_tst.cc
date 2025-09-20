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
/// \brief The gtest_bmi270_gyr_slf_tst test fixture class.
///
class gtest_bmi270_gyr_slf_tst : public ::testing::Test
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

                /* It is not important what data goes inside fifo after that.
                 * For example bmi270_acc_read function will push register address
                 * to fifo during transmission. The fifo has two indexes, rx and tx.
                 * It always starts reading from rx_idx which is 0. */

                /* buf[0] and buf[1] will be discarded. */
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0x00;

                /* Wait previous time (450us). */
                SPI_DR_ARR[SPI1].buf[2] = 0x00;
                SPI_DR_ARR[SPI1].buf[3] = 0x00;
                SPI_DR_ARR[SPI1].buf[4] = 0x00;
                SPI_DR_ARR[SPI1].buf[5] = 0x00;

                /* Wait current time (450us). */
                SPI_DR_ARR[SPI1].buf[6] = 0x00;
                SPI_DR_ARR[SPI1].buf[7] = 0x00;
                SPI_DR_ARR[SPI1].buf[8] = 0x00;
                SPI_DR_ARR[SPI1].buf[9] = 0x0d;

                /* Internal status register value. */
                SPI_DR_ARR[SPI1].buf[10] = 0x00;
                SPI_DR_ARR[SPI1].buf[11] = 0x01;

                /* Wait previous time (450us). */
                SPI_DR_ARR[SPI1].buf[12] = 0x00;
                SPI_DR_ARR[SPI1].buf[13] = 0x00;
                SPI_DR_ARR[SPI1].buf[14] = 0x00;
                SPI_DR_ARR[SPI1].buf[15] = 0x00;

                /* Wait current time (450us). */
                SPI_DR_ARR[SPI1].buf[16] = 0x00;
                SPI_DR_ARR[SPI1].buf[17] = 0x00;
                SPI_DR_ARR[SPI1].buf[18] = 0x00;
                SPI_DR_ARR[SPI1].buf[19] = 0x0d;

                /* GYR_GAIN_STATUS.g_trig_status reports of a
                 * successful self-test or execution errors. */
                SPI_DR_ARR[SPI1].buf[20] = 0x00;
                SPI_DR_ARR[SPI1].buf[21] = 0x00;

                /* Self test is not complete, after the device sets
                 * GYR_SELF_TEST_AXES.gyr_st_axes_done = 0x00. */
                SPI_DR_ARR[SPI1].buf[22] = 0x00;
                SPI_DR_ARR[SPI1].buf[23] = 0x00;

                /* Self test is complete, after the device sets
                 * GYR_SELF_TEST_AXES.gyr_st_axes_done = 0x01. */
                SPI_DR_ARR[SPI1].buf[24] = 0x00;
                SPI_DR_ARR[SPI1].buf[25] = 0x01;

                /* Set tx_idx to point to first the unoccupied place in the buffer. */
                SPI_DR_ARR[SPI1].tx_idx = 26;

                /*
                 * Bytes after write operations inside bmi270_gyr_slf_tst,
                 * buf[26] = 0x7e
                 * buf[27] = 0xb6
                 * buf[28] = 0x80
                 * buf[29] = 0x7c
                 * buf[30] = 0x00
                 * buf[31] = 0x98
                 * buf[32] = 0x98
                 * buf[33] = 0x59
                 * buf[34] = 0x00
                 * buf[35] = 0x5e
                 * buf[36 + sizeof(bmi270_conf_file)] = 0x59
                 * buf[37 + sizeof(bmi270_conf_file)] = 0x01
                 * buf[38 + sizeof(bmi270_conf_file)] = 0xa1
                 * buf[39 + sizeof(bmi270_conf_file)] = 0x7c
                 * buf[40 + sizeof(bmi270_conf_file)] = 0x00
                 * buf[41 + sizeof(bmi270_conf_file)] = 0x98
                 * buf[42 + sizeof(bmi270_conf_file)] = 0x98
                 * buf[43 + sizeof(bmi270_conf_file)] = 0x7d
                 * buf[44 + sizeof(bmi270_conf_file)] = 0x04
                 * buf[45 + sizeof(bmi270_conf_file)] = 0x7e
                 * buf[46 + sizeof(bmi270_conf_file)] = 0x02
                 * buf[47 + sizeof(bmi270_conf_file)] = 0xb8
                 * buf[48 + sizeof(bmi270_conf_file)] = 0xee
                 * buf[49 + sizeof(bmi270_conf_file)] = 0xee */
            }
        }

        void TearDown() override
        {
            if (::testing::UnitTest::GetInstance()->current_test_info()->name() ==
                std::string("procedure"))
            {
                (void)bmi270_stat_set(bmi270, BMI270_STAT_DEINIT);
                memset(&SPI_DR_ARR[SPI1].buf[0], 0, sizeof(SPI_DR_ARR[SPI1].buf));
            }
        }

        static struct bmi270_dev *bmi270;
        static struct spi_ctrl_dev *spi_ctrl;
};

struct bmi270_dev   *gtest_bmi270_gyr_slf_tst::bmi270   = nullptr;
struct spi_ctrl_dev *gtest_bmi270_gyr_slf_tst::spi_ctrl = nullptr;

///
/// \brief This test performs the bmi270 gyroscope self test procedure.
///
TEST_F(gtest_bmi270_gyr_slf_tst, procedure)
{
    bmi270_res_t res;

    res = bmi270_spi_ctrl_asg(gtest_bmi270_gyr_slf_tst::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_gyr_slf_tst(gtest_bmi270_gyr_slf_tst::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[26], 0x7e);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[27], 0xb6);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[28], 0x80);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[29], 0x7c);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[30], 0x00);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[31], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[32], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[33], 0x59);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[34], 0x00);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[35], 0x5e);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[36 + sizeof(bmi270_conf_file)], 0x59);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[37 + sizeof(bmi270_conf_file)], 0x01);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[38 + sizeof(bmi270_conf_file)], 0xa1);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[39 + sizeof(bmi270_conf_file)], 0x7c);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[40 + sizeof(bmi270_conf_file)], 0x00);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[41 + sizeof(bmi270_conf_file)], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[42 + sizeof(bmi270_conf_file)], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[43 + sizeof(bmi270_conf_file)], 0x7d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[44 + sizeof(bmi270_conf_file)], 0x04);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[45 + sizeof(bmi270_conf_file)], 0x7e);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[46 + sizeof(bmi270_conf_file)], 0x02);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[47 + sizeof(bmi270_conf_file)], 0xb8);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[48 + sizeof(bmi270_conf_file)], 0xee);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[49 + sizeof(bmi270_conf_file)], 0xee);
}

///
/// \brief This test checks the null pointer protection inside bmi270 gyroscope
///        self test function.
///
TEST_F(gtest_bmi270_gyr_slf_tst, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_gyr_slf_tst(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
