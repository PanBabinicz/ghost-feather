#include <gtest/gtest.h>
#include <stdint.h>
#include "usart_controller.h"

#define SYSCLK  (16000000U)

uint32_t USART_CR1 = 0x00000000;
uint32_t USART_CR2 = 0x00000000;
uint32_t USART_BRR = 0x00000000;

///
/// \brief This test performs the usart controller init procedure.
///
TEST(init, procedure)
{
    uint32_t expected_usart_cr1 = 0x0000000d;

    /* Using SYSCLK because of the default value of AHB and APB buses prescalers. */
    uint32_t expected_usart_brr = ((SYSCLK + 115200 / 2 ) / 115200);

    usart_controller_debug_init();

    EXPECT_EQ(USART_CR1, expected_usart_cr1);
    EXPECT_EQ(USART_BRR, expected_usart_brr);
}
