#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"
#include "spi_ctrl.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_acc_slf_tst test fixture class.
///
class gtest_bmi270_acc_slf_tst : public ::testing::Test
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
                /* It is not important what data goes inside fifo after that.
                 * For example bmi270_acc_read function will push register address
                 * to fifo during transmission. The fifo has two indexes, rx and tx.
                 * It always starts reading from rx_idx which is 0. */

                /* Wait previous time (2ms). */
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0x00;
                SPI_DR_ARR[SPI1].buf[2] = 0x00;
                SPI_DR_ARR[SPI1].buf[3] = 0x00;

                /* Wait current time (2ms). */
                SPI_DR_ARR[SPI1].buf[4] = 0x00;
                SPI_DR_ARR[SPI1].buf[5] = 0x00;
                SPI_DR_ARR[SPI1].buf[6] = 0x00;
                SPI_DR_ARR[SPI1].buf[7] = 0x35;

                /* Wait previous time (50ms). */
                SPI_DR_ARR[SPI1].buf[8]  = 0x00;
                SPI_DR_ARR[SPI1].buf[9]  = 0x00;
                SPI_DR_ARR[SPI1].buf[10] = 0x00;
                SPI_DR_ARR[SPI1].buf[11] = 0x00;

                /* Wait current time (50ms). */
                SPI_DR_ARR[SPI1].buf[12] = 0x00;
                SPI_DR_ARR[SPI1].buf[13] = 0x00;
                SPI_DR_ARR[SPI1].buf[14] = 0x05;
                SPI_DR_ARR[SPI1].buf[15] = 0x02;

                /* acc_read. */
                SPI_DR_ARR[SPI1].buf[16] = 0x00;
                SPI_DR_ARR[SPI1].buf[17] = 0x12;
                SPI_DR_ARR[SPI1].buf[18] = 0x34;
                SPI_DR_ARR[SPI1].buf[19] = 0x56;
                SPI_DR_ARR[SPI1].buf[20] = 0x78;
                SPI_DR_ARR[SPI1].buf[21] = 0x9a;
                SPI_DR_ARR[SPI1].buf[22] = 0xbc;
                SPI_DR_ARR[SPI1].buf[23] = 0xde;
                SPI_DR_ARR[SPI1].buf[24] = 0xff;

                /* Wait previous time (50ms). */
                SPI_DR_ARR[SPI1].buf[25] = 0x00;
                SPI_DR_ARR[SPI1].buf[26] = 0x00;
                SPI_DR_ARR[SPI1].buf[27] = 0x00;
                SPI_DR_ARR[SPI1].buf[28] = 0x00;

                /* Wait current time (50ms). */
                SPI_DR_ARR[SPI1].buf[29] = 0x00;
                SPI_DR_ARR[SPI1].buf[30] = 0x00;
                SPI_DR_ARR[SPI1].buf[31] = 0x05;
                SPI_DR_ARR[SPI1].buf[32] = 0x02;

                /* Set tx_idx to point to first the unoccupied place in the buffer. */
                SPI_DR_ARR[SPI1].tx_idx = 33;

                /*
                 * 1.  bmi270_reg_write(dev, adr = 0x7d, buf[0] = 0x01, sz = 1)
                 * 2.  bmi270_reg_write(dev, adr = 0x41, buf[0] = 0x03, sz = 1)
                 * 3.  bmi270_reg_write(dev, adr = 0x6d, buf[0] = 0x08, sz = 1)
                 * 4.  buf[0] = 0x98
                 * 5.  buf[0] = 0x98
                 * 6.  bmi270_reg_write(dev, adr = 0x6d, buf[0] = 0x0c, sz = 1)
                 * 7.  bmi270_reg_write(dev, adr = 0x6d, buf[0] = 0x0d, sz = 1)
                 * 8.  buf[0] = 0x98
                 * 9.  buf[0] = 0x98
                 * 10. buf[0] = 0x8c
                 * 11. bmi270_reg_write(dev, adr = 0x6d, buf[0] = 0x08, sz = 1)
                 * 12. bmi270_reg_write(dev, adr = 0x6d, buf[0] = 0x09, sz = 1)
                 * 13. buf[0] = 0x98
                 * 14. buf[0] = 0x98
                 * 15. buf[0] = 0x8c
                 * 16. bmi270_reg_write(dev, adr = 0x6d, buf[0] = 0x00, sz = 1)
                 *
                 * Bytes after write operations inside bmi270_acc_slf_tst,
                 * buf[33] = 0x7d
                 * buf[34] = 0x01
                 * buf[35] = 0x41
                 * buf[36] = 0x03
                 * buf[37] = 0x6d
                 * buf[38] = 0x08
                 * buf[39] = 0x98
                 * buf[40] = 0x98
                 * buf[41] = 0x6d
                 * buf[42] = 0x0c
                 * buf[43] = 0x6d
                 * buf[44] = 0x0d
                 * buf[45] = 0x98
                 * buf[46] = 0x98
                 * buf[47] = 0x8c
                 * buf[48] = 0x6d
                 * buf[49] = 0x08
                 * buf[50] = 0x6d
                 * buf[51] = 0x09
                 * buf[52] = 0x98
                 * buf[53] = 0x98
                 * buf[54] = 0x8c
                 * buf[55] = 0x6d
                 * buf[56] = 0x00 */
        }

        void TearDown() override
        {
            memset(&SPI_DR_ARR[SPI1].buf[0], 0, sizeof(SPI_DR_ARR[SPI1].buf));
        }


        static struct bmi270_dev *bmi270;
        static struct spi_ctrl_dev *spi_ctrl;
};

struct bmi270_dev   *gtest_bmi270_acc_slf_tst::bmi270   = nullptr;
struct spi_ctrl_dev *gtest_bmi270_acc_slf_tst::spi_ctrl = nullptr;

///
/// \brief This test performs the bmi270 accelerometer self test procedure.
///
TEST_F(gtest_bmi270_acc_slf_tst, procedure)
{
    bmi270_res_t res;

    res = bmi270_spi_ctrl_asg(gtest_bmi270_acc_slf_tst::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_acc_slf_tst(gtest_bmi270_acc_slf_tst::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[33], 0x7d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[34], 0x01);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[35], 0x41);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[36], 0x03);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[37], 0x6d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[38], 0x08);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[39], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[40], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[41], 0x6d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[42], 0x0c);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[43], 0x6d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[44], 0x0d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[45], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[46], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[47], 0x8c);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[48], 0x6d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[49], 0x08);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[50], 0x6d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[51], 0x09);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[52], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[53], 0x98);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[54], 0x8c);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[55], 0x6d);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[56], 0x00);
}

///
/// \brief This test checks the null pointer protection inside bmi270 accelerometer
///        self test function.
///
TEST_F(gtest_bmi270_acc_slf_tst, null_pointer_protection)
{
    bmi270_res_t res;

    res = bmi270_acc_slf_tst(NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
