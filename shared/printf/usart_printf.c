#include "usart_printf.h"
#include "libopencm3/stm32/usart.h"

#define USART_PRINTF_BUFFER_MAX (256u)

void usart_printf(uint32_t usart, const char *format, ...)
{
    uint8_t buffer[USART_PRINTF_BUFFER_MAX];
    uint8_t i = 0;
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, USART_PRINTF_BUFFER_MAX, format, args);
    va_end(args);

    while ((buffer[i] != '\0') && (i < USART_PRINTF_BUFFER_MAX))
    {
        usart_send_blocking(usart, buffer[i]);
        i++;
    }
}
