#include <sys/stat.h>
#include "usart_controller.h"
#include "libopencm3/stm32/usart.h"

extern uint32_t _end;

///
/// \brief Status of an open file.
///
int _fstat(int file, struct stat *st) 
{
    st->st_mode = S_IFCHR;
    return 0;
}

///
/// \brief Set position in a file.
///
int _lseek(int file, int ptr, int dir)
{
    return 0;
}

///
/// \brief Close a file.
///
int _close(int file)
{
    return -1;
}

///
/// \brief Write using USART.
///
int _write(int file, char *ptr, int len)
{
    int todo;
    uint32_t usart_instance;

    /* Get debug usart instance */
    (void)usart_controller_debug_get_instance(&usart_instance);

    for (todo = 0; todo < len; todo++)
    {
        usart_send_blocking(usart_instance, ((uint16_t)*ptr++));
    }

    return len;
}

///
/// \brief Read using USART.
///
int _read(int file, char *ptr, int len)
{
    int todo;
    uint32_t usart_instance;

    /* Get debug usart instance */
    (void)usart_controller_debug_get_instance(&usart_instance);

    for (todo = 0; todo < len; todo++)
    {
        *ptr = usart_recv_blocking(usart_instance);
        ptr++;
    }

    return len;
}

///
/// \brief Increase program data space.
///
void *_sbrk(int incr)
{
    static uint8_t *heap = NULL;
    uint8_t *prev_heap;

    if (heap == NULL)
    {
        heap = (uint8_t*)&_end;
    }

    prev_heap = heap;
    heap      = heap + incr;

    return prev_heap;
}

///
/// \brief Query whether output stream is a terminal.
///
int _isatty(int file)
{
    return 1;
}

///
/// \brief Exit a program without cleaning up files.
///
void _exit(int status)
{
    __asm("BKPT #0");
}

///
/// \brief Send a signal.
///
void _kill(int pid, int sig)
{
    return;
}

///
/// \brief Process-ID.
///
int _getpid(void)
{
    return -1;
}
