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

///
/// \brief Interrupt Clear Register (ICR) for I2C.
///
union ll_i2c_icr
{
    uint32_t r;
    struct
    {
        uint32_t          : 3;
        uint32_t addrcf   : 1;
        uint32_t nackcf   : 1;
        uint32_t stopcf   : 1;
        uint32_t          : 2;
        uint32_t berrcf   : 1;
        uint32_t arlocf   : 1;
        uint32_t ovrcf    : 1;
        uint32_t peccf    : 1;
        uint32_t timoutcf : 1;
        uint32_t alertcf  : 1;
        uint32_t          : 18;
    } bf;
};

///
/// \brief PEC Register (PECR) for I2C.
///
union ll_i2c_pecr
{
    uint32_t r;
    struct
    {
        uint32_t pec : 8;
        uint32_t     : 24;
    } bf;
};

///
/// \brief Receive Data Register (RXDR) for I2C.
///
union ll_i2c_rxdr
{
    uint32_t r;
    struct
    {
        uint32_t rxdata : 8;
        uint32_t        : 24;
    } bf;
};

///
/// \brief Transmit Data Register (TXDR) for I2C.
///
union ll_i2c_txdr
{
    uint32_t r;
    struct
    {
        uint32_t txdata : 8;
        uint32_t        : 24;
    } bf;
};

///
/// \brief Register map for I2C.
///
/// This structure represents the memory-mapped register layout of the
/// I2C. The register order and reserved fields are aligned with the
/// device reference manual to allow direct access via a peripheral base
/// address.
///
struct ll_i2c_regs
{
    union ll_i2c_cr1 cr1;
    union ll_i2c_cr2 cr2;
    union ll_i2c_oar1 oar1;
    union ll_i2c_oar2 oar2;
    union ll_i2c_timingr timingr;
    union ll_i2c_timeoutr timeoutr;
    union ll_i2c_isr isr;
    union ll_i2c_icr icr;
    union ll_i2c_pecr pecr;
    union ll_i2c_rxdr rxdr;
    union ll_i2c_txdr txdr;
};

///
/// \brief Runtime device context for I2C.
///
/// This structure holds all runtime state required to control a I2C instance.
/// It includes a pointer to the memory-mapped registers, a temporary
/// shadow copy for safe modification and initialization status.
///
struct ll_i2c_dev
{
    volatile struct ll_i2c_regs *rmap;
    struct ll_i2c_regs rtmp;
    ll_i2c_stat_t stat;
};

///
/// \brief Initializes the I2C.
///
/// \param[in] handle The pointer to i2c device.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_init(ll_i2c_dev *handle);

///
/// \brief Deinitializes the I2C.
///
/// \param[in] handle The pointer to i2c device.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_deinit(ll_i2c_dev *handle);

///
/// \brief Performs the software reset of the I2C.
///
/// \param[in] handle The pointer to i2c device.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_software_reset(ll_i2c_dev *handle);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_I2C_H */

