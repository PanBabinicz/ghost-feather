#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270"
#include "libopencm3/stm32/gpio.h"

///
/// \brief This test performs the bmi270 get device procedure.
///
TEST(get_dev, procedure)
{
    struct bmi270_dev *dev = NULL;

    dev = bmi270_get_dev();

    /* Compare accelerator part. */
    EXPECT_EQ(dev->acc.data.x, 0);
    EXPECT_EQ(dev->acc.data.y, 0);
    EXPECT_EQ(dev->acc.data.z, 0);
    EXPECT_EQ(dev->acc.conf.filt_perf, 0);
    EXPECT_EQ(dev->acc.conf.bwp, 0);
    EXPECT_EQ(dev->acc.conf.odr, 0);
    EXPECT_EQ(dev->acc.rng.reserved, 0);
    EXPECT_EQ(dev->acc.rng.acc_rng, 0);

    /* Compare gyroscope part. */
    EXPECT_EQ(dev->gyr.data.x, 0);
    EXPECT_EQ(dev->gyr.data.y, 0);
    EXPECT_EQ(dev->gyr.data.z, 0);
    EXPECT_EQ(dev->gyr.conf.filt_perf, 0);
    EXPECT_EQ(dev->gyr.conf.noise_perf, 0);
    EXPECT_EQ(dev->gyr.conf.bwp, 0);
    EXPECT_EQ(dev->gyr.conf.odr, 0);
    EXPECT_EQ(dev->gyr.rng.reserved, 0);
    EXPECT_EQ(dev->gyr.rng.ois_rng, 0);
    EXPECT_EQ(dev->gyr.rng.gyr_rng, 0);

    /* Compare temperature sensor part. */
    EXPECT_EQ(dev->temp.data, 0);

    /* Compare sensor time part. */
    EXPECT_EQ(dev->time.reserved, 0);
    EXPECT_EQ(dev->time.data, 0);

    /* Compare gpio part. */
    EXPECT_EQ(dev->gpio.port, GPIOA);
    EXPECT_EQ(dev->gpio.pin, GPIO4);

    /* Compare spi_ctrl part. */
    EXPECT_EQ(dev->spi_ctrl, NULL);

    /* Compare bmi270 status part. */
    EXPECT_EQ(dev->stat, BMI270_STAT_DEINIT);
}
