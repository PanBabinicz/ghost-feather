#ifndef _LL_I2C_H
#define _LL_I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The I2C result type.
///
typedef enum ll_i2c_res
{
    LL_I2C_RES_OK = 0,
    LL_I2C_RES_ERR,
} ll_i2c_res_t;

///
/// \brief The I2C status type.
///
/// This enum reflects whether a I2C peripheral is currently initialized or
/// not.
///
typedef enum ll_i2c_stat
{
    LL_I2C_STAT_DEINIT = 0,
    LL_I2C_STAT_INIT,
} ll_i2c_stat_t;

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_I2C_H */

