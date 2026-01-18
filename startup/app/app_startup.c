#include "app.h"
#include "libopencm3/cm3/scb.h"

///*************************************************************************************************
/// Private objects - declaration.
///*************************************************************************************************
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _etext;
extern uint32_t _vector_table;

///*************************************************************************************************
/// Global functions - declaration.
///*************************************************************************************************
///
/// \brief The reset handler which initializes memory and start the application.
///
/// This function clears the BSS section, initializes global and static
/// variables.
///
extern void _reset_handler(void);

///*************************************************************************************************
/// Global functions - definiton.
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

    SCB_VTOR = (uint32_t)&_vector_table;

    app_start();

    /* Never return. */
    while (1);
}
