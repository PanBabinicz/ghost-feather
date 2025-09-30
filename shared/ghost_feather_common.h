#ifndef _GHOST_FEATHER_COMMON_H
#define _GHOST_FEATHER_COMMON_H

#include <stdint.h>
#include "libopencm3/cm3/systick.h"

#define GHOST_FEATHER_COMMON_START_APP              (1U)
#define GHOST_FEATHER_COMMON_PROCESSOR_FREQUENCY    (216000000U)
#define GHOST_FEATHER_COMMON_SINGLE_CYCLE           (4.62962962962963F)
#define GHOST_FEATHER_COMMON_US_IN_CYCLES           (216U)
#define GHOST_FEATHER_COMMON_MS_IN_CYCLES           (216000U)

///*************************************************************************************************
/// Private objects - definition.
///*************************************************************************************************
///
/// \brief The systick counter variable. It updates in _systick_handler.
///
static uint32_t systick_cntr;

///*************************************************************************************************
/// Private functions - declaration.
///*************************************************************************************************
///
/// \brief Initializes the systick counter.
///
/// \param[in] rld The systick counter reload value.
///
static inline void systick_init(uint32_t rld);

///
/// \brief Deinitializes the systick counter.
///
/// \param[in] rld The systick counter reload value.
///
static inline void systick_deinit(void);

///
/// \brief Delays execution for a specified number of microseconds.
///
/// \param[in] us The number of microseconds.
///
static inline void systick_delay_us(uint32_t ms);

///*************************************************************************************************
/// Private functions - definition.
///*************************************************************************************************
static inline void systick_init(uint32_t rld)
{
    systick_counter_disable();
    systick_interrupt_enable();
    systick_set_reload(rld - 1);
    systick_clear();
    systick_counter_enable();
}

static inline void systick_deinit(void)
{
    systick_counter_disable();
    systick_interrupt_disable();
}

static inline void systick_delay_us(uint32_t us)
{
    systick_cntr = 0;
    while (systick_cntr < us);
}

#endif  /* _GHOST_FEATHER_COMMON_H */
