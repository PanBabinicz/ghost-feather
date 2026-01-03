#include "ll_usart.h"
#include "libopencm3/stm32/usart.h"
#if (defined(DEBUG) && (DEBUG == 1))
#include "printf.h"
#endif  /* DEBUG */

#define LL_USART_DEBUG_BAUDRATE  (115200u)
#define LL_USART_DEBUG_INTERFACE (USART3)

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
///
/// \brief The usart controller structure.
///
typedef struct
{
    uint32_t baud;
    uint32_t intf;
    ll_usart_status_t stat;
} ll_usart_t;

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \brief The usart controller.
///
static ll_usart_t ll_usart;

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
#if (defined(DEBUG) && (DEBUG == 1))
void _putchar(char character)
{
    usart_send_blocking(LL_USART_DEBUG_INTERFACE, (uint16_t)character);
}
#else
void _putchar(char character)
{
}
#endif  /* DEBUG */

ll_usart_status_t ll_usart_is_initialized(void)
{
    return ll_usart.stat;
}

void ll_usart_set_init_status(ll_usart_status_t status)
{
    ll_usart.stat = status;
}

void ll_usart_debug_init(void)
{
    if (ll_usart.stat != LL_USART_STATUS_INIT)
    {
        ll_usart.baud = LL_USART_DEBUG_BAUDRATE;
        ll_usart.intf = LL_USART_DEBUG_INTERFACE;

        usart_disable(ll_usart.intf);

        usart_set_baudrate(ll_usart.intf, ll_usart.baud);
        usart_set_databits(ll_usart.intf, 8);

        /* 1 stop bit, refer to manual */
        usart_set_stopbits(ll_usart.intf, 0);

        usart_set_parity(ll_usart.intf, USART_PARITY_NONE);
        usart_set_mode(ll_usart.intf, USART_MODE_TX_RX);

        usart_enable(ll_usart.intf);

        ll_usart.stat = LL_USART_STATUS_INIT;
    }
}

void ll_usart_debug_deinit(void)
{
    if (ll_usart.stat != LL_USART_STATUS_DEINIT)
    {
        usart_disable(ll_usart.intf);

        ll_usart.baud = 0;
        ll_usart.intf = 0;
        ll_usart.stat = LL_USART_STATUS_DEINIT;
    }
}
