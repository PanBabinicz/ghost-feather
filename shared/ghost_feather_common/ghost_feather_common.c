#include "ghost_feather_common.h"
#include "libopencm3/cm3/dwt.h"
#include "libopencm3/cm3/systick.h"

///*************************************************************************************************
/// Global objects - definition.
///*************************************************************************************************
///
/// \brief
///
uint32_t gfc_systick_cnt;

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief
///
static bool gfc_dwt_is_init(void);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static bool gfc_dwt_is_init(void)
{
    bool is_init = (!(DWT_CTRL & DWT_CTRL_NOCYCCNT) &&
            ((DWT_CTRL & DWT_CTRL_CYCCNTENA) != 0));

    return is_init;
}

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
bool gfc_dwt_init(void)
{
    return dwt_enable_cycle_counter();
}

void gfc_dwt_delay_us(const uint32_t us)
{
    if (!gfc_dwt_is_init())
    {
        return;
    }

    uint32_t cycles_needed = ((uint32_t)(us * 1000)) / GHOST_FEATHER_COMMON_SINGLE_CYCLE;
    uint32_t start = DWT_CYCCNT;

    while ((uint32_t)(DWT_CYCCNT - start) < cycles_needed)
    {
        __asm("nop");
    }
}

void gfc_dwt_delay_ms(const uint32_t ms)
{
    if (!gfc_dwt_is_init())
    {
        return;
    }

    /*
    uint64_t cycles_needed = ((uint64_t)(ms * 1000000)) / GHOST_FEATHER_COMMON_SINGLE_CYCLE;
    uint32_t start = dwt_read_cycle_counter();

    while ((uint32_t)(dwt_read_cycle_counter() - start) < cycles_needed)
    {
        __asm("nop");
    }
    */
}

void gfc_systick_init(void)
{
    systick_counter_disable();
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_interrupt_enable();
    systick_set_reload(GHOST_FEATHER_COMMON_MS_IN_CYCLES - 1);
    systick_clear();
    systick_counter_enable();
}

void gfc_systick_deinit(void)
{
    systick_counter_disable();
    systick_interrupt_disable();
}

void gfc_systick_delay_ms(const uint32_t ms)
{
    gfc_systick_cnt = 0;
    while (gfc_systick_cnt < ms)
    {
        __asm("nop");
    }
}
