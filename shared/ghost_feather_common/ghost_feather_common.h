#ifndef _GHOST_FEATHER_COMMON_H
#define _GHOST_FEATHER_COMMON_H

#include <stdint.h>
#include <stdbool.h>

#define GHOST_FEATHER_COMMON_START_APP              (1U)
#define GHOST_FEATHER_COMMON_PROCESSOR_FREQUENCY    (216000000U)
#define GHOST_FEATHER_COMMON_SINGLE_CYCLE           (4.62962962962963F)
#define GHOST_FEATHER_COMMON_US_IN_CYCLES           (216U)
#define GHOST_FEATHER_COMMON_MS_IN_CYCLES           (216000U)

extern uint32_t gfc_systick_cnt;

///
/// \brief
///
bool gfc_dwt_init(void);

///
/// \brief
///
void gfc_dwt_delay_us(const uint32_t us);

///
/// \brief
///
void gfc_dwt_delay_ms(const uint32_t ms);

///
/// \brief Initializes the ghost feather common systick counter.
///
void gfc_systick_init(void);

///
/// \brief Deinitializes the ghost feather common systick counter.
///
void gfc_systick_deinit(void);

///
/// \brief SysTick delay execution for a specified number of milliseconds.
///
/// \param[in] ms The number of milliseconds.
///
void gfc_systick_delay_ms(const uint32_t ms);

#endif  /* _GHOST_FEATHER_COMMON_H */
