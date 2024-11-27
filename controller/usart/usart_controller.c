#include "usart_controller.h"
#include "printf.h"

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void _putchar(char character)
{
    usart_send_blocking(USART_CONTROLLER_DEBUG_INTERFACE, (uint16_t)character);
}

void usart_controller_debug_init(void)
{
    usart_disable(USART_CONTROLLER_DEBUG_INTERFACE);

    usart_set_baudrate(USART_CONTROLLER_DEBUG_INTERFACE, USART_CONTROLLER_DEBUG_BAUDRATE);
    usart_set_databits(USART_CONTROLLER_DEBUG_INTERFACE, 8);

    /* 1 stop bit, refer to manual */
    usart_set_stopbits(USART_CONTROLLER_DEBUG_INTERFACE, 0);

    usart_set_parity(USART_CONTROLLER_DEBUG_INTERFACE, USART_PARITY_NONE);
    usart_set_mode(USART_CONTROLLER_DEBUG_INTERFACE, USART_MODE_TX_RX);

    usart_enable(USART_CONTROLLER_DEBUG_INTERFACE);
}
