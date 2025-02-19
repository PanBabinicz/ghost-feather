#include "stm32f722xx_boot_updater.h"

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _etext;

///*************************************************************************************************
/// Global functions - declaration.
///*************************************************************************************************
///
/// \brief The reset handler which initializes memory and start the
///        boot updater.
///
/// This function clears the BSS section, initializes global and static
/// variables.
///
extern void _reset_handler(void);

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

    boot_updater_start();

    /* Never return. */
    while (1);
}
