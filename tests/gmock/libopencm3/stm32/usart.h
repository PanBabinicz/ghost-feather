#ifndef _GMOCK_LIBOPENCM3_USART_H
#define _GMOCK_LIBOPENCM3_USART_H

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \breif Mock implementation of usart_wait_send_ready function.
///
static inline void usart_wait_send_ready(uint32_t usart)
{
    return;
}

///
/// \breif Mock implementation of usart_wait_recv_ready function.
///
static inline void usart_wait_recv_ready(uint32_t usart)
{
    return;
}

///
/// \breif Mock implementation of usart_send function.
///
static inline void usart_send(uint32_t usart, uint16_t data)
{
    printf("GMOCK: %s(usart = %d, data = 0x%x)\n", __func__, usart, data);
}

///
/// \breif Mock implementation of usart_recv function.
///
static inline uint16_t usart_recv(uint32_t usart)
{
    return 1;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _GMOCK_LIBOPENCM3_USART */
