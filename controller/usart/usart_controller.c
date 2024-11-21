#include "usart_controller.h"
#include "libopencm3/stm32/usart.h"

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
///
/// \breif
///
typedef struct
{
    uint32_t instance;
} usart_controller_t;

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
usart_controller_t usart_controller_debug = { 0 };

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \breif
///
void usart_controller_debug_set(const uint32_t instance);

///
/// \breif
///
uint32_t usart_controller_debug_get(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
void usart_controller_debug_set(const uint32_t instance)
{
    usart_controller_debug.instance = instance;
}

uint32_t usart_controller_debug_get(void)
{
    return usart_controller_debug.instance;
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
void usart_controller_debug_init(const uint32_t instance)
{
    usart_controller_debug_set(instance);

    usart_disable(instance);

    usart_set_baudrate(instance, 115200);
    usart_set_databits(instance, 8);

    /* 1 stop bit, refer to manual */
    usart_set_stopbits(instance, 0);

    usart_set_parity(instance, USART_PARITY_NONE);
    usart_set_mode(instance, USART_MODE_TX_RX);

    usart_enable(instance);
}

usart_controller_result_t usart_controller_debug_get_instance(uint32_t * const instance)
{
    usart_controller_result_t result = USART_CONTROLLER_RESULT_ERROR;

    if (instance != NULL)
    {
        *instance = usart_controller_debug_get();
        result    = USART_CONTROLLER_RESULT_SUCCESS;
    }

    return result;
}
