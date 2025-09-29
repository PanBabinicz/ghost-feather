#ifndef _GHOST_FEATHER_COMMON_H
#define _GHOST_FEATHER_COMMON_H

#include <stdint.h>
#include "libopencm3/cm3/systick.h"

#define GHOST_FEATHER_COMMON_START_APP              (0U)
#define GHOST_FEATHER_COMMON_PROCESSOR_FREQUENCY    (216000000U)
#define GHOST_FEATHER_COMMON_CYCLE_TIME             (4.62962962962963F)

///
/// \brief Delays execution for a specified number of milliseconds.
///
/// \param[in] ms The number of milliseconds.
///
static inline void systick_delay_ms(uint32_t ms);

static inline void systick_delay_ms(uint32_t ms)
{
    uint32_t rld_val;
    uint32_t ns = ms * 1000000;

    rld_val = (uint32_t)((float)ns / GHOST_FEATHER_COMMON_CYCLE_TIME);

    systick_set_reload(rld_val);
    systick_clear();

    /* Wait for the count flag to be set */
    while (!systick_get_countflag());
}

#endif  /* _GHOST_FEATHER_COMMON_H */
