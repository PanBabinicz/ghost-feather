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

///
/// \brief Control Register 1 (CR1) for I2C.
///
union ll_i2c_cr1
{
    uint32_t r;
    struct
    {
        uint32_t pe        : 1;
        uint32_t txie      : 1;
        uint32_t rxie      : 1;
        uint32_t addrie    : 1;
        uint32_t nackie    : 1;
        uint32_t stopie    : 1;
        uint32_t tcie      : 1;
        uint32_t errie     : 1;
        uint32_t dnf       : 4;
        uint32_t anfoff    : 1;
        uint32_t           : 1;
        uint32_t txdmaen   : 1;
        uint32_t rxdmaen   : 1;
        uint32_t sbc       : 1;
        uint32_t nostretch : 1;
        uint32_t           : 1;
        uint32_t gcen      : 1;
        uint32_t smbhen    : 1;
        uint32_t smbden    : 1;
        uint32_t alerten   : 1;
        uint32_t pcen      : 1;
        uint32_t           : 8;
    } bf;
};

///
/// \brief Control Register 2 (CR2) for I2C.
///
union ll_i2c_cr2
{
    uint32_t r;
    struct
    {
        uint32_t sadd    : 10;
        uint32_t rdwrn   : 1;
        uint32_t add10   : 1;
        uint32_t head10r : 1;
        uint32_t start   : 1;
        uint32_t stop    : 1;
        uint32_t nack    : 1;
        uint32_t nbytes  : 8;
        uint32_t reload  : 1;
        uint32_t autoend : 1;
        uint32_t pecbyte : 1;
        uint32_t         : 5;
    } bf;
};

///
/// \brief Own Address Register 1 (OAR1) for I2C.
///
union ll_i2c_oar1
{
    uint32_t r;
    struct
    {
        uint32_t oa1_0   : 1;
        uint32_t oa1_71  : 7;
        uint32_t oa1_98  : 2;
        uint32_t oa1mode : 1;
        uint32_t         : 4;
        uint32_t oa1en   : 1;
        uint32_t         : 16;
    } bf;
};

///
/// \brief Own Address Register 2 (OAR2) for I2C.
///
union ll_i2c_oar2
{
    uint32_t r;
    struct
    {
        uint32_t        : 1;
        uint32_t oa2_71 : 7;
        uint32_t oa2msk : 3;
        uint32_t        : 4;
        uint32_t oa2en  : 1;
        uint32_t        : 16;
    } bf;
};

///
/// \brief Timing Register (TIMINGR) for I2C.
///
union ll_i2c_timingr
{
    uint32_t r;
    struct
    {
        uint32_t scll   : 8;
        uint32_t sclh   : 8;
        uint32_t sdadel : 4;
        uint32_t scldel : 4;
        uint32_t        : 4;
        uint32_t presc  : 4;
    } bf;
};

///
/// \brief Timeout Register (TIMEOUTR) for I2C.
///
union ll_i2c_timeoutr
{
    uint32_t r;
    struct
    {
        uint32_t timeouta : 12;
        uint32_t tidle    : 1;
        uint32_t          : 2;
        uint32_t timouten : 1;
        uint32_t timeoutb : 12;
        uint32_t          : 3;
        uint32_t texten   : 1;
    } bf;
};

///
/// \brief Interrupt and Status Register (ISR) for I2C.
///
union ll_i2c_isr
{
    uint32_t r;
    struct
    {
        uint32_t txe     : 1;
        uint32_t txis    : 1;
        uint32_t rxne    : 1;
        uint32_t addr    : 1;
        uint32_t nackf   : 1;
        uint32_t stopf   : 1;
        uint32_t tc      : 1;
        uint32_t tcr     : 1;
        uint32_t berr    : 1;
        uint32_t arlo    : 1;
        uint32_t ovr     : 1;
        uint32_t pecerr  : 1;
        uint32_t timeout : 1;
        uint32_t alert   : 1;
        uint32_t         : 1;
        uint32_t busy    : 1;
        uint32_t dir     : 1;
        uint32_t addcode : 7;
        uint32_t         : 8;
    } bf;
};

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_I2C_H */

