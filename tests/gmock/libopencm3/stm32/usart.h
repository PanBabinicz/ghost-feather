#ifndef _GMOCK_LIBOPENCM3_USART_H
#define _GMOCK_LIBOPENCM3_USART_H

#include <stdio.h>
#include <stdint.h>

#define USART_CR1_UE    (1 << 0x00)

#define USART_CR2_UE    (1 << 0x00)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \breif Mock definition of USART control register 1.
///
static inline uint32_t USART_CR1 = 0x00000000;

///
/// \breif Mock definition of USART control register 2.
///
static inline uint32_t USART_CR2 = 0x00000000;

///
/// \breif Mock definition of USART baud rate register.
///
static inline uint32_t USART_BRR = 0x00000000;

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

///
/// \breif Mock implementation of usart_enable function.
///
static inline void usart_enable(uint32_t usart)
{
	USART_CR1 |= USART_CR1_UE;
}

///
/// \breif Mock implementation of usart_disable function.
///
static inline void usart_disable(uint32_t usart)
{
	USART_CR1 &= ~USART_CR1_UE;
}

///
/// \breif Mock implementation of usart_set_baudrate function.
///
static inline void usart_set_baudrate(uint32_t usart, uint32_t baud)
{

}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _GMOCK_LIBOPENCM3_USART */
