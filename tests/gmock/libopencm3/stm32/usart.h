#ifndef _GMOCK_LIBOPENCM3_USART_H
#define _GMOCK_LIBOPENCM3_USART_H

#include <stdio.h>
#include <stdint.h>

#define USART3                  (0x00000000)

///
/// \brief USART control register 1.
///
#define USART_CR1_M0            (0x01 << 0x0c)
#define USART_CR1_PCE           (0x01 << 0x0a)
#define USART_CR1_PS            (0x01 << 0x09)
#define USART_CR1_TE            (0x01 << 0x03)
#define USART_CR1_RE            (0x01 << 0x02)
#define USART_CR1_UE            (0x01 << 0x00)

#define USART_PARITY_NONE       (0x00)
#define USART_PARITY_EVEN       (USART_CR1_PCE)
#define USART_PARITY_ODD        (USART_CR1_PS | USART_CR1_PCE)
#define USART_PARITY_MASK       (USART_CR1_PS | USART_CR1_PCE)

#define USART_MODE_RX           (USART_CR1_RE)
#define USART_MODE_TX           (USART_CR1_TE)
#define USART_MODE_TX_RX        (USART_CR1_RE | USART_CR1_TE)
#define USART_MODE_MASK         (USART_CR1_RE | USART_CR1_TE)

///
/// \brief USART control register 2.
///
#define USART_CR2_STOPBITS_1    (0x00 << 0x0c)
#define USART_CR2_STOPBITS_0_5  (0x01 << 0x0c)
#define USART_CR2_STOPBITS_2    (0x02 << 0x0c)
#define USART_CR2_STOPBITS_1_5  (0x03 << 0x0c)
#define USART_CR2_STOPBITS_MASK (0x03 << 0x0c)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \breif Mock definition of USART control register 1.
///
extern uint32_t USART_CR1;

///
/// \breif Mock definition of USART control register 2.
///
extern uint32_t USART_CR2;

///
/// \breif Mock definition of USART baud rate register.
///
extern uint32_t USART_BRR;

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
    /* Lets say that we use HSI as sysclk. */
	uint32_t clock = 16000000U;

	USART_BRR = (clock + baud / 2) / baud;
}

///
/// \breif Mock implementation of usart_set_databits function.
///
static inline void usart_set_databits(uint32_t usart, uint32_t bits)
{
	if (bits == 8)
    {
        /* 8 data bits. */
		USART_CR1 &= ~USART_CR1_M0;
	}
    else
    {
        /* 9 data bits. */
		USART_CR1 |= USART_CR1_M0;
	}
}

///
/// \breif Mock implementation of usart_set_parity function.
///
static inline void usart_set_parity(uint32_t usart, uint32_t parity)
{
	uint32_t reg32;

	reg32 = USART_CR1;
	reg32 = (reg32 & ~USART_PARITY_MASK) | parity;
	USART_CR1 = reg32;
}


///
/// \breif Mock implementation of usart_set_mode function.
///
static inline void usart_set_mode(uint32_t usart, uint32_t mode)
{
	uint32_t reg32;

	reg32 = USART_CR1;
	reg32 = (reg32 & ~USART_MODE_MASK) | mode;
	USART_CR1 = reg32;
}

///
/// \breif Mock implementation of usart_set_stopbits function.
///
static inline void usart_set_stopbits(uint32_t usart, uint32_t stopbits)
{
	uint32_t reg32;

	reg32 = USART_CR2;
	reg32 = (reg32 & ~USART_CR2_STOPBITS_MASK) | stopbits;
	USART_CR2 = reg32;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _GMOCK_LIBOPENCM3_USART */
