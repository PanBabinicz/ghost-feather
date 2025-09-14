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

                /* buf[0] and buf[1] will be discarded. */
                SPI_DR_ARR[SPI1].buf[0] = 0x00;
                SPI_DR_ARR[SPI1].buf[1] = 0x00;
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
