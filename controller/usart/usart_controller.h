#ifndef _USART_CONTROLLER_H
#define _USART_CONTROLLER_H

#include <stdint.h>
#include "libopencm3/stm32/usart.h"

#define USART_CONTROLLER_DEBUG_BAUDRATE  (115200u)
#define USART_CONTROLLER_DEBUG_INTERFACE (USART3)

///
/// \brief The usart controller result type.
///
typedef enum
{
    USART_CONTROLLER_RESULT_SUCCESS = 0,
    USART_CONTROLLER_RESULT_ERROR,
} usart_controller_result_t;

///
/// \brief Initialize the usart controller debug interface.
///
void usart_controller_debug_init(void);

#endif /* _USART_CONTROLLER_H */
