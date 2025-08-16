#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief This test performs the bmi270 get device procedure.
///
TEST(gtest_bmi270_get_dev, procedure)
{
    struct bmi270_dev *dev = NULL;
    dev = bmi270_get_dev();

    EXPECT_NE(dev, nullptr);
}
