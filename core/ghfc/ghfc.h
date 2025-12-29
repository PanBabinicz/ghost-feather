#ifndef _GHFC_H
#define _GHFC_H

#include <stdint.h>
#include <stdbool.h>

#define GHFC_START_APP       (1U)
#define GHFC_PROC_FREQ       (216000000U)
#define GHFC_SINGLE_CYCLE    (4.62962962962963F)
#define GHFC_US_IN_CYCLES    (216U)
#define GHFC_MS_IN_CYCLES    (216000U)

extern uint32_t ghfc_systick_cnt;

///
/// \brief
///
bool ghfc_dwt_init(void);

///
/// \brief
///
void ghfc_dwt_delay_us(const uint32_t us);

///
/// \brief
///
void ghfc_dwt_delay_ms(const uint32_t ms);

///
/// \brief Initializes the ghost feather common systick counter.
///
void ghfc_systick_init(void);

///
/// \brief Deinitializes the ghost feather common systick counter.
///
void ghfc_systick_deinit(void);

///
/// \brief SysTick delay execution for a specified number of milliseconds.
///
/// \param[in] ms The number of milliseconds.
///
void ghfc_systick_delay_ms(const uint32_t ms);

#endif  /* _GHFC_H */
