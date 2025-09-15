#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"
#include "spi_ctrl.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_pwr_mode_set test fixture class.
///
class gtest_bmi270_pwr_mode_set : public ::testing::Test
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

                /* Read the PWR_CONF and PWR_CTRL registers value
                 * The buf[0] is dummy byte and will be discarded.
                 * The buf[1] corresponds to PWR_CONF, reset value is 0x03.
                 * The buf[2] corresponds to PWR_CTRL, reset value is 0x00. */
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0x03;
                SPI_DR_ARR[SPI1].buf[2] = 0x00;

                /* Read the ACC_CONF register value.
                 * The buf[3] is dummy byte and will be discarded.
                 * The buf[4] corresponds to ACC_CONF, reset value is 0xa8. */
                SPI_DR_ARR[SPI1].buf[3] = 0x00;
                SPI_DR_ARR[SPI1].buf[4] = 0xa8;

                /* Read the GYR_CONF register value.
                 * The buf[5] is dummy byte and will be discarded.
                 * The buf[6] corresponds to GYR_CONF, reset value is 0xa9. */
                SPI_DR_ARR[SPI1].buf[5] = 0x00;
                SPI_DR_ARR[SPI1].buf[6] = 0xa9;

                /* Set tx_idx to point to first the unoccupied place in the buffer. */
                SPI_DR_ARR[SPI1].tx_idx = 7;

                /* Bytes after write operations inside bmi270_pwr_mode_set,
                 * And for this scenario, buf[7], buf[8] and buf[9] are dummy bytes
                 * buf[7]  = BMI270_REG_PWR_CONF | BMI270_OP_READ
                 * buf[8]  = BMI270_REG_ACC_CONF | BMI270_OP_READ
                 * buf[9]  = BMI270_REG_GYR_CONF | BMI270_OP_READ
                 * buf[10] = BMI270_REG_PWR_CONF
                 * buf[11] = 0x03
                 * buf[12] = 0x00
                 * buf[13] = BMI270_REG_ACC_CONF
                 * buf[14] = 0xa8
                 * buf[15] = BMI270_REG_GYR_CONF
                 * buf[16] = 0xa9 */
        }

        void TearDown() override
        {
        }

        static struct bmi270_dev *bmi270;
        static struct spi_ctrl_dev *spi_ctrl;
};

struct bmi270_dev   *gtest_bmi270_pwr_mode_set::bmi270   = nullptr;
struct spi_ctrl_dev *gtest_bmi270_pwr_mode_set::spi_ctrl = nullptr;

///
/// \brief This test performs the bmi270 power mode set procedure.
///
TEST_F(gtest_bmi270_pwr_mode_set, procedure)
{
    bmi270_res_t res;

    const struct bmi270_pwr_mode_conf *pwr_mode_conf =
      bmi270_pwr_mode_get_conf(BMI270_PWR_MODE_SUSP);

    res = bmi270_spi_ctrl_asg(gtest_bmi270_pwr_mode_set::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    res = bmi270_pwr_mode_set(gtest_bmi270_pwr_mode_set::bmi270, pwr_mode_conf);
    EXPECT_EQ(res, BMI270_RES_OK);

    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[10], BMI270_REG_PWR_CONF);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[11], 0x03);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[12], 0x00);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[13], BMI270_REG_ACC_CONF);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[14], 0xa8);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[15], BMI270_REG_GYR_CONF);
    EXPECT_EQ(SPI_DR_ARR[SPI1].buf[16], 0xa9);
}

///
/// \brief This test checks the null pointer protection inside bmi270
///        power mode set function.
///
TEST_F(gtest_bmi270_pwr_mode_set, null_pointer_protection)
{
    bmi270_res_t res;

    const struct bmi270_pwr_mode_conf *pwr_mode_conf =
      bmi270_pwr_mode_get_conf(BMI270_PWR_MODE_SUSP);

    /* The bmi270 device is NULL. */
    res = bmi270_pwr_mode_set(NULL, pwr_mode_conf);
    EXPECT_EQ(res, BMI270_RES_ERR);

    /* The spi control device is NULL. */
    res = bmi270_pwr_mode_set(gtest_bmi270_pwr_mode_set::bmi270, pwr_mode_conf);
    EXPECT_EQ(res, BMI270_RES_ERR);

    res = bmi270_spi_ctrl_asg(gtest_bmi270_pwr_mode_set::bmi270);
    EXPECT_EQ(res, BMI270_RES_OK);

    /* The pwr_mode_conf is NULL. */
    res = bmi270_pwr_mode_set(gtest_bmi270_pwr_mode_set::bmi270, NULL);
    EXPECT_EQ(res, BMI270_RES_ERR);
}
