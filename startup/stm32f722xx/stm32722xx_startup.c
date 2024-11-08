#include "stm32f722xx_memory_map.h"
#include "stm32f722xx_first_bootloader.h"

extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _etext;

extern void _reset_handler(void);

///
/// \breif This reset handler function is used to run first bootloader.
///
void _reset_handler(void)
{
    /* Clear the bss section */
    for (uint32_t *bss = &_sbss; bss < &_ebss; )
    {
        *bss++ = 0;
    }

    /* Set the global and static variables */
    uint32_t *init_value = &_etext;
    uint32_t *data       = &_sdata;

    if (init_value != data)
    {
        while (data < &_edata)
        {
            *data++ = *init_value++;
        }
    }

    first_bootloader_start();

    /* Never return */
    while (1);
}
