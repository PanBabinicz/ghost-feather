#ifndef _TIMING_H
#define _TIMING_H

#include <stdint.h>

///
/// \brief System clock frequency value (Hz) stored in shared memory for use across all firmware
///        stages.
///
extern volatile uint32_t timing_sysclk_freq;

///
/// \brief The timing result type.
///
typedef enum timing_res
{
    TIMING_RES_OK = 0,
    TIMING_RES_ERR,
} timing_res_t;

///
/// \brief Initializes the DWT unit.
///
/// \return timing_res_t   The timing result.
/// \retval TIMING_RES_OK  On success.
/// \retval TIMING_RES_ERR Otherwise.
///
timing_res_t timing_init(void);

///
/// \brief Starts and resets the DWT cycle counter.
///
void timing_start(void);

///
/// \brief Stops the DWT cycle counter.
///
void timing_stop(void);

///
/// \brief Gets the DWT cycle counter value.
///
/// \return uint32_t The DWT cycle counter value.
///
uint32_t timing_cnt_get(void);

///
/// \brief Delays for the given number of microseconds.
///
/// \param[in] us The given number of microseconds.
///
void timing_delay_us(const uint32_t us);

#endif  /* _TIMING_H */
