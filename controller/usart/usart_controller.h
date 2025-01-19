#ifndef _USART_CONTROLLER_H
#define _USART_CONTROLLER_H

#include <stdint.h>
#include "libopencm3/stm32/usart.h"

///
/// \brief The usart controller result type.
///
typedef enum
{
    USART_CONTROLLER_RESULT_SUCCESS = 0,
    USART_CONTROLLER_RESULT_ERROR,
} usart_controller_result_t;

///
/// \brief The usart controller status type.
///
typedef enum
{
    USART_CONTROLLER_STATUS_DEINIT = 0,
    USART_CONTROLLER_STATUS_INIT,
} usart_controller_status_t;

///
/// \brief Get the usart controller initialized flag.
///
/// \return usart_controller_status_t      Init status.
/// \retval USART_CONTROLLER_STATUS_INIT   When usart controller has been already initialized.
/// \retval USART_CONTROLLER_STATUS_DEINIT Otherwise.
///
usart_controller_status_t usart_controller_is_initialized(void);

///
/// \brief Initialize the usart controller debug interface.
///
void usart_controller_debug_init(void);

///
/// \brief Deinitialize the usart controller debug interface.
///
void usart_controller_debug_deinit(void);

#endif /* _USART_CONTROLLER_H */
