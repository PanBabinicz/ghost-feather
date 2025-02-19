#include "stm32f722xx_first_bootloader.h"

#define CPACR   (*(volatile uint32_t*)(0xe000ed88))

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _etext;

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \breif Unlocks the FPU.
///
static void fpu_unlock();

///*************************************************************************************************
/// Global functions - declaration.
///*************************************************************************************************
///
/// \brief The reset handler which initializes memory and start the
///        first bootloader.
///
/// This function clears the BSS section, initializes global and static
/// variables.
///
extern void _reset_handler(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static void fpu_unlock()
{
    /* CP11 and CP10 are (23-22) and (21-20) bits respectively. */
    CPACR |= ((0x03 << 0x16) | (0x03 <<0x14));
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
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

    /* Never return. */
    while (1);
}
