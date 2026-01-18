#ifndef _LL_USART_H
#define _LL_USART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The USART result type.
///
typedef enum
{
    LL_USART_RESULT_SUCCESS = 0,
    LL_USART_RESULT_ERROR,
} ll_usart_result_t;

///
/// \brief The USART status type.
///
typedef enum
{
    LL_USART_STATUS_DEINIT = 0,
    LL_USART_STATUS_INIT,
} ll_usart_status_t;

///
/// \brief Gets the USART initialized flag.
///
/// \return ll_usart_status_t      Initialize status.
/// \retval LL_USART_STATUS_INIT   When usart has been already initialized.
/// \retval LL_USART_STATUS_DEINIT Otherwise.
///
ll_usart_status_t ll_usart_is_initialized(void);

///
/// \brief Sets the USART status.
///
/// \param[in] status The status to be set.
///
void ll_usart_set_init_status(ll_usart_status_t status);

///
/// \brief Initializes the USART debug interface.
///
void ll_usart_debug_init(void);

///
/// \brief Deinitializes the USART debug interface.
///
void ll_usart_debug_deinit(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_USART_H */
