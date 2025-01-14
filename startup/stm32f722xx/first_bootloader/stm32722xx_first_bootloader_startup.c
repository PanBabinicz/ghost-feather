#include "stm32f722xx_first_bootloader.h"

#define CPACR   (*(volatile uint32_t*)(0xe000ed88))

extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _etext;

extern void _reset_handler(void);

///
/// \breif Unlock the FPU on Cortex M7.
///
static void fpu_unlock();

static void fpu_unlock()
{
    /* CP11 and CP10 are (23-22) and (21-20) bits respectively. */
    CPACR |= ((0x03 << 0x16) | (0x03 <<0x14));
}

///
/// \breif This reset handler function is used to prepare for the first bootloader.
///
void _reset_handler(void)
{
    /* Clear the bss section. */
    for (uint32_t *bss = &_sbss; bss < &_ebss; )
    {
        *bss++ = 0;
    }

    /* Set the global and static variables. */
    uint32_t *init_value = &_etext;
    uint32_t *data       = &_sdata;

    if (init_value != data)
    {
        while (data < &_edata)
        {
            *data++ = *init_value++;
        }
    }

    /* Unlock the FPU. */
    fpu_unlock();

    first_bootloader_start();

    /* Never return */
    while (1);
}
