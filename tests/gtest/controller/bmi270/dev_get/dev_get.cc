#include <gtest/gtest.h>
#include <stdint.h>
#include "bmi270.h"
#include "libopencm3/stm32/spi_common.h"

uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \brief The gtest_bmi270_dev_get test fixture class.
///
class gtest_bmi270_dev_get : public ::testing::Test
{
    protected:
        static void SetUpTestSuite()
        {
        }

        static void TearDownTestSuite()
        {
            bmi270 = nullptr;
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        static struct bmi270_dev *bmi270;
};

struct bmi270_dev *gtest_bmi270_dev_get::bmi270 = nullptr;

///
/// \brief This test performs the bmi270 device get procedure.
///
TEST_F(gtest_bmi270_dev_get, procedure)
{
    gtest_bmi270_dev_get::bmi270 = bmi270_dev_get();

    EXPECT_NE(gtest_bmi270_dev_get::bmi270, nullptr);
}
