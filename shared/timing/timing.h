#ifndef _TIMING_H
#define _TIMING_H

#include <stdint.h>

///
/// \brief
///
typedef enum timing_res
{
    TIMING_RES_OK = 0,
    TIMING_RES_ERR,
} timing_res_t;

///
/// \brief
///
timing_res_t timing_init(void);

///
/// \brief
///
void timing_start();

///
/// \brief
///
void timing_stop();

#endif  /* _TIMING_H */
