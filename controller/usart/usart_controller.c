#include "usart_controller.h"
#include "libopencm3/stm32/usart.h"
#if (defined(DEBUG) && (DEBUG == 1))
#include "printf.h"
#endif  /* DEBUG */

#define USART_CONTROLLER_DEBUG_BAUDRATE  (115200u)
#define USART_CONTROLLER_DEBUG_INTERFACE (USART3)

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
///
/// \brief The usart controller structure.
///
typedef struct
{
    uint32_t baudrate;
    uint32_t interface;
    usart_controller_status_t is_initialized;
} usart_controller_t;

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \breif The usart controller.
///
static usart_controller_t usart_controller;

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
#if (defined(DEBUG) && (DEBUG == 1))
void _putchar(char character)
{
    usart_send_blocking(USART_CONTROLLER_DEBUG_INTERFACE, (uint16_t)character);
}
#endif  /* DEBUG */

usart_controller_status_t usart_controller_is_initialized(void)
{
    return usart_controller.is_initialized;
}

void usart_controller_set_init_status(usart_controller_status_t status)
{
    usart_controller.is_initialized = status;
}

void usart_controller_debug_init(void)
{
    if (usart_controller.is_initialized != USART_CONTROLLER_STATUS_INIT)
    {
        usart_controller.baudrate  = USART_CONTROLLER_DEBUG_BAUDRATE;
        usart_controller.interface = USART_CONTROLLER_DEBUG_INTERFACE;

        usart_disable(usart_controller.interface);

        usart_set_baudrate(usart_controller.interface, usart_controller.baudrate);
        usart_set_databits(usart_controller.interface, 8);

        /* 1 stop bit, refer to manual */
        usart_set_stopbits(usart_controller.interface, 0);

        usart_set_parity(usart_controller.interface, USART_PARITY_NONE);
        usart_set_mode(usart_controller.interface, USART_MODE_TX_RX);

        usart_enable(usart_controller.interface);

        usart_controller.is_initialized = USART_CONTROLLER_STATUS_INIT;
    }
}

void usart_controller_debug_deinit(void)
{
    if (usart_controller.is_initialized != USART_CONTROLLER_STATUS_DEINIT)
    {
        usart_disable(usart_controller.interface);

        usart_controller.baudrate       = 0;
        usart_controller.interface      = 0;
        usart_controller.is_initialized = USART_CONTROLLER_STATUS_DEINIT;
    }
}
