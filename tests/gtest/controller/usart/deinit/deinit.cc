#include <gtest/gtest.h>
#include <stdint.h>
#include "usart_controller.h"

#define SYSCLK  (16000000U)

uint32_t USART_CR1 = 0x0000000d;
uint32_t USART_CR2 = 0x00000000;
uint32_t USART_BRR = ((SYSCLK + 115200 / 2 ) / 115200);

///
/// \brief This test performs the usart controller deinit procedure.
///
TEST(deinit, procedure)
{
    usart_controller_status_t status;
    uint32_t expected_usart_cr1 = 0x0000000c;

    usart_controller_set_init_status(USART_CONTROLLER_STATUS_INIT);
    usart_controller_debug_deinit();
    status = usart_controller_is_initialized();

    EXPECT_EQ(status, USART_CONTROLLER_STATUS_DEINIT);
    EXPECT_EQ(USART_CR1, expected_usart_cr1);
}
