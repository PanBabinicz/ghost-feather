#ifndef _USART_CONTROLLER_H
#define _USART_CONTROLLER_H

#include <stdint.h>

///
/// \brief
///
typedef enum
{
    USART_CONTROLLER_RESULT_SUCCESS = 0,
    USART_CONTROLLER_RESULT_ERROR,
} usart_controller_result_t;

///
/// \brief
///
void usart_controller_debug_init(const uint32_t instance);

///
/// \brief
///
usart_controller_result_t usart_controller_debug_get_instance(uint32_t * const instance);

#endif /* _USART_CONTROLLER_H */
