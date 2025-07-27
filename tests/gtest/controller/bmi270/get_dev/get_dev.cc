#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "spi_ctrl.h"
#include "libopencm3/stm32/gpio.h"

///
/// \brief This test performs the bmi270 get device procedure.
///
TEST(get_dev, procedure)
{
    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    EXPECT_NE(dev, nullptr);
}
