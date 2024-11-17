#ifndef _USART_PRINTF_H
#define _USART_PRINTF_H

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

///
/// \brief
///
void usart_printf(uint32_t usart, const char *format, ...);

#endif /* _USART_PRINTF_H */
