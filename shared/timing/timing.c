#include "timing.h"
#include "libopencm3/cm3/dwt.h"
#include "libopencm3/cm3/itm.h"
#include "libopencm3/cm3/scs.h"
#include "libopencm3/stm32/rcc.h"
#include <stdbool.h>

#define TIMING_TICK_DURATION    ((1.0f)/(timing_sysclk_freq))
#define TIMING_US_TO_TICKS(us)  ((us)/((TIMING_TICK_DURATION) * (1000000.0f)))

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \brief System clock frequency value (Hz) stored in shared memory for use across all firmware
///        stages.
///
volatile uint32_t __attribute__((section(".shared"))) timing_sysclk_freq;

///*************************************************************************************************
/// Global functions - definition.
///*************************************************************************************************
timing_res_t timing_init(void)
{
    SCS_DEMCR |= SCS_DEMCR_TRCENA;

    if (DWT_CTRL & DWT_CTRL_NOCYCCNT)
    {
        return TIMING_RES_ERR;
    }

    return TIMING_RES_OK;
}

void timing_start(void)
{
	DWT_CYCCNT = 0;
	DWT_CTRL |= DWT_CTRL_CYCCNTENA;
}

void timing_stop(void)
{
	DWT_CTRL &= ~DWT_CTRL_CYCCNTENA;
}

uint32_t timing_cnt_get(void)
{
    return DWT_CYCCNT;
}

void timing_delay_us(const uint32_t us)
{
    uint32_t ticks = TIMING_US_TO_TICKS(us);
    uint32_t prev = timing_cnt_get();
    uint32_t curr = prev;

    while ((curr - prev) < ticks)
    {
        curr = timing_cnt_get();
    }
}
