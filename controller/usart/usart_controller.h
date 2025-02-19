#ifndef _USART_CONTROLLER_H
#define _USART_CONTROLLER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

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
/// \brief Sets the usart controller status.
///
/// \param[in] status The status to be set.
///
void usart_controller_set_init_status(usart_controller_status_t status);

///
/// \brief Initialize the usart controller debug interface.
///
void usart_controller_debug_init(void);

///
/// \brief Deinitialize the usart controller debug interface.
///
void usart_controller_debug_deinit(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _USART_CONTROLLER_H */
