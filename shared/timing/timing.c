#include "timing.h"
#include "libopencm3/cm3/dwt.h"
#include "libopencm3/cm3/itm.h"
#include "libopencm3/cm3/scs.h"
#include <stdbool.h>

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
