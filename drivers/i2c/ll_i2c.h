#ifndef _LL_I2C_H
#define _LL_I2C_H

#include <stdint.h>
#include "libopencm3/cm3/common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define LL_I2C_I2C1_ADDRESS             (0x40005400ul)
#define LL_I2C_I2C2_ADDRESS             (0x40005800ul)
#define LL_I2C_I2C3_ADDRESS             (0x40005c00ul)

#define LL_I2C_REG_CR1(address)         MMIO32(address + LL_I2C_REG_OFFSET_CR1)
#define LL_I2C_REG_CR2(address)         MMIO32(address + LL_I2C_REG_OFFSET_CR2)
#define LL_I2C_REG_OAR1(address)        MMIO32(address + LL_I2C_REG_OFFSET_OAR1)
#define LL_I2C_REG_OAR2(address)        MMIO32(address + LL_I2C_REG_OFFSET_OAR2)
#define LL_I2C_REG_TIMINGR(address)     MMIO32(address + LL_I2C_REG_OFFSET_TIMINGR)
#define LL_I2C_REG_TIMEOUTR(address)    MMIO32(address + LL_I2C_REG_OFFSET_TIMEOUTR)
#define LL_I2C_REG_ISR(address)         MMIO32(address + LL_I2C_REG_OFFSET_ISR)
#define LL_I2C_REG_ICR(address)         MMIO32(address + LL_I2C_REG_OFFSET_ICR)
#define LL_I2C_REG_PECR(address)        MMIO32(address + LL_I2C_REG_OFFSET_PECR)
#define LL_I2C_REG_RXDR(address)        MMIO32(address + LL_I2C_REG_OFFSET_RXDR)
#define LL_I2C_REG_TXDR(address)        MMIO32(address + LL_I2C_REG_OFFSET_TXDR)

///
/// \brief The I2C Register Offset type.
///
typedef enum ll_i2c_reg_offset
{
    LL_I2C_REG_OFFSET_CR1      = 0x00,
    LL_I2C_REG_OFFSET_CR2      = 0x04,
    LL_I2C_REG_OFFSET_OAR1     = 0x08,
    LL_I2C_REG_OFFSET_OAR2     = 0x0c,
    LL_I2C_REG_OFFSET_TIMINGR  = 0x10,
    LL_I2C_REG_OFFSET_TIMEOUTR = 0x14,
    LL_I2C_REG_OFFSET_ISR      = 0x18,
    LL_I2C_REG_OFFSET_ICR      = 0x1c,
    LL_I2C_REG_OFFSET_PECR     = 0x20,
    LL_I2C_REG_OFFSET_RXDR     = 0x24,
    LL_I2C_REG_OFFSET_TXDR     = 0x28,
} ll_i2c_reg_offset_t;

///
/// \brief The I2C Control Register 1 (CR1) mask type.
///
typedef enum ll_i2c_cr1_mask
{
    LL_I2C_CR1_PE_MASK        = (0x01U << 0x00),
    LL_I2C_CR1_TXIE_MASK      = (0x01U << 0x01),
    LL_I2C_CR1_RXIE_MASK      = (0x01U << 0x02),
    LL_I2C_CR1_ADDRIE_MASK    = (0x01U << 0x03),
    LL_I2C_CR1_NACKIE_MASK    = (0x01U << 0x04),
    LL_I2C_CR1_STOPIE_MASK    = (0x01U << 0x05),
    LL_I2C_CR1_TCIE_MASK      = (0x01U << 0x06),
    LL_I2C_CR1_ERRIE_MASK     = (0x01U << 0x07),
    LL_I2C_CR1_DNF_MASK       = (0x0fU << 0x08),
    LL_I2C_CR1_ANFOFF_MASK    = (0x01U << 0x0c),
    LL_I2C_CR1_TXDMAEN_MASK   = (0x01U << 0x0e),
    LL_I2C_CR1_RXDMAEN_MASK   = (0x01U << 0x0f),
    LL_I2C_CR1_SBC_MASK       = (0x01U << 0x10),
    LL_I2C_CR1_NOSTRETCH_MASK = (0x01U << 0x11),
    LL_I2C_CR1_GCEN_MASK      = (0x01U << 0x13),
    LL_I2C_CR1_SMBHEN_MASK    = (0x01U << 0x14),
    LL_I2C_CR1_SMBDEN_MASK    = (0x01U << 0x15),
    LL_I2C_CR1_ALERTEN_MASK   = (0x01U << 0x16),
    LL_I2C_CR1_PECEN_MASK     = (0x01U << 0x17),
} ll_i2c_cr1_mask_t;

///
/// \brief The I2C Control Register 2 (CR2) mask type.
///
typedef enum ll_i2c_cr2_mask
{
    LL_I2C_CR2_SADD_MASK    = (0x03ffU << 0x00),
    LL_I2C_CR2_RDWRN_MASK   = (0x0001U << 0x0a),
    LL_I2C_CR2_ADD10_MASK   = (0x0001U << 0x0b),
    LL_I2C_CR2_HEAD10R_MASK = (0x0001U << 0x0c),
    LL_I2C_CR2_START_MASK   = (0x0001U << 0x0d),
    LL_I2C_CR2_STOP_MASK    = (0x0001U << 0x0e),
    LL_I2C_CR2_NACK_MASK    = (0x0001U << 0x0f),
    LL_I2C_CR2_NBYTES_MASK  = (0x00ffU << 0x10),
    LL_I2C_CR2_RELOAD_MASK  = (0x0001U << 0x18),
    LL_I2C_CR2_AUTOEND_MASK = (0x0001U << 0x19),
    LL_I2C_CR2_PECBYTE_MASK = (0x0001U << 0x1a),
} ll_i2c_cr2_mask_t;

///
/// \brief The I2C Own Address Register 1 (OAR1) mask type.
///
typedef enum ll_i2c_oar1_mask
{
    LL_I2C_OAR1_OA1_MASK     = (0x03ffU << 0x00),
    LL_I2C_OAR1_OA1MODE_MASK = (0x0001U << 0x0a),
    LL_I2C_OAR1_OA1EN_MASK   = (0x0001U << 0x0f),
} ll_i2c_oar1_mask_t;

///
/// \brief The I2C Own Address Register 2 (OAR2) mask type.
///
typedef enum ll_i2c_oar2_mask
{
    LL_I2C_OAR2_OA2_MASK    = (0x007fU << 0x01),
    LL_I2C_OAR2_OA2MSK_MASK = (0x0007U << 0x08),
    LL_I2C_OAR2_OA2EN_MASK  = (0x0001U << 0x0f),
} ll_i2c_oar2_mask_t;

///
/// \brief The I2C Timing Register (TIMINGR) mask type.
///
typedef enum ll_i2c_timingr_mask
{
    LL_I2C_TIMINGR_SCLL_MASK   = (0x00ffU << 0x00),
    LL_I2C_TIMINGR_SCLH_MASK   = (0x00ffU << 0x08),
    LL_I2C_TIMINGR_SDADEL_MASK = (0x000fU << 0x10),
    LL_I2C_TIMINGR_SCLDEL_MASK = (0x000fU << 0x14),
    LL_I2C_TIMINGR_PRESC_MASK  = (0x000fU << 0x1c),
} ll_i2c_timingr_mask_t;

///
/// \brief The I2C Timeout Register (TIMEOUTR) mask type.
///
typedef enum ll_i2c_timeoutr_mask
{
    LL_I2C_TIMEOUTR_TIMEOUTA_MASK = (0x0fffU << 0x00),
    LL_I2C_TIMEOUTR_TIDLE_MASK    = (0x0001U << 0x0c),
    LL_I2C_TIMEOUTR_TIMOUTEN_MASK = (0x0001U << 0x0f),
    LL_I2C_TIMEOUTR_TIMEOUTB_MASK = (0x0fffU << 0x10),
    LL_I2C_TIMEOUTR_TEXTEN_MASK   = (0x0001U << 0x1f),
} ll_i2c_timeoutr_mask_t;

///
/// \brief The I2C Interrupt and Status Register (ISR) mask type.
///
typedef enum ll_i2c_isr_mask
{
    LL_I2C_ISR_TXE_MASK     = (0x0001U << 0x00),
    LL_I2C_ISR_TXIS_MASK    = (0x0001U << 0x01),
    LL_I2C_ISR_RXNE_MASK    = (0x0001U << 0x02),
    LL_I2C_ISR_ADDR_MASK    = (0x0001U << 0x03),
    LL_I2C_ISR_NACKF_MASK   = (0x0001U << 0x04),
    LL_I2C_ISR_STOPF_MASK   = (0x0001U << 0x05),
    LL_I2C_ISR_TC_MASK      = (0x0001U << 0x06),
    LL_I2C_ISR_TCR_MASK     = (0x0001U << 0x07),
    LL_I2C_ISR_BERR_MASK    = (0x0001U << 0x08),
    LL_I2C_ISR_ARLO_MASK    = (0x0001U << 0x09),
    LL_I2C_ISR_OVR_MASK     = (0x0001U << 0x0a),
    LL_I2C_ISR_PECERR_MASK  = (0x0001U << 0x0b),
    LL_I2C_ISR_TIMEOUT_MASK = (0x0001U << 0x0c),
    LL_I2C_ISR_ALERT_MASK   = (0x0001U << 0x0d),
    LL_I2C_ISR_BUSY_MASK    = (0x0001U << 0x0f),
    LL_I2C_ISR_DIR_MASK     = (0x0001U << 0x10),
    LL_I2C_ISR_ADDCODE_MASK = (0x007fU << 0x11),
} ll_i2c_isr_mask_t;

///
/// \brief The I2C Interrupt Clear Register (ICR) mask type.
///
typedef enum ll_i2c_icr_mask
{
    LL_I2C_ICR_ADDRCF_MASK   = (0x0001U << 0x03),
    LL_I2C_ICR_NACKCF_MASK   = (0x0001U << 0x04),
    LL_I2C_ICR_STOPCF_MASK   = (0x0001U << 0x05),
    LL_I2C_ICR_BERRCF_MASK   = (0x0001U << 0x08),
    LL_I2C_ICR_ARLOCF_MASK   = (0x0001U << 0x09),
    LL_I2C_ICR_OVRCF_MASK    = (0x0001U << 0x0a),
    LL_I2C_ICR_PECCF_MASK    = (0x0001U << 0x0b),
    LL_I2C_ICR_TIMOUTCF_MASK = (0x0001U << 0x0c),
    LL_I2C_ICR_ALERTCF_MASK  = (0x0001U << 0x0d),
} ll_i2c_icr_mask_t;

///
/// \brief The I2C interrupt type.
///
typedef enum ll_i2c_interrupt
{
    LL_I2C_INTERRUPT_TX = 0x01,
    LL_I2C_INTERRUPT_RX,
    LL_I2C_INTERRUPT_ADDR,
    LL_I2C_INTERRUPT_NACK,
    LL_I2C_INTERRUPT_STOP,
    LL_I2C_INTERRUPT_TC,
    LL_I2C_INTERRUPT_ERR,
} ll_i2c_interrupt_t;

///
/// \brief The I2C digital noise filter capability type.
///
typedef enum ll_i2c_dnf
{
    LL_I2C_DNF_DISABLE = 0,
    LL_I2C_DNF_1TCLK,
    LL_I2C_DNF_2TCLK,
    LL_I2C_DNF_3TCLK,
    LL_I2C_DNF_4TCLK,
    LL_I2C_DNF_5TCLK,
    LL_I2C_DNF_6TCLK,
    LL_I2C_DNF_7TCLK,
    LL_I2C_DNF_8TCLK,
    LL_I2C_DNF_9TCLK,
    LL_I2C_DNF_10TCLK,
    LL_I2C_DNF_11TCLK,
    LL_I2C_DNF_12TCLK,
    LL_I2C_DNF_13TCLK,
    LL_I2C_DNF_14TCLK,
    LL_I2C_DNF_15TCLK,
} ll_i2c_dnf_t;

///
/// \brief The I2C PEC Register (PECR) mask type.
///
typedef enum ll_i2c_pecr_mask
{
    LL_I2C_PECR_PEC_MASK = (0x00ffU << 0x00),
} ll_i2c_pecr_mask_t;

///
/// \brief The I2C Receive Data Register (RXDR) mask type.
///
typedef enum ll_i2c_rxdr_mask
{
    LL_I2C_RXDR_RXDATA_MASK = (0x00ffU << 0x00),
} ll_i2c_rxdr_mask_t;

///
/// \brief The I2C Transmit Data Register (TXDR) mask type.
///
typedef enum ll_i2c_txdr_mask
{
    LL_I2C_TXDR_TXDATA_MASK = (0x00ffU << 0x00),
} ll_i2c_txdr_mask_t;

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
/// \brief Enables the I2C peripheral.
///
/// \param[in] address The I2C address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_periph_enable(const uint32_t address);

///
/// \brief Disable the I2C peripheral.
///
/// \param[in] address The I2C address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_periph_disable(const uint32_t address);

///
/// \brief Performs the software reset of the I2C.
///
/// \param[in] address The I2C address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_software_reset(const uint32_t address);

///
/// \brief Receives a single byte over the I2C bus.
///
/// \param[in]  address The I2C address.
/// \param[out] byte    The pointer to storage for the received byte.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_receive(const uint32_t address, uint8_t *const byte);

///
/// \brief Transmits a single byte over the I2C bus.
///
/// \param[in] address The I2C address.
/// \param[in] byte    The pointer to storage for the transmited byte.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_transmit(const uint32_t address, const uint8_t *const byte);

///
/// \brief Enables TX DMA mode on I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_txdma_enable(const uint32_t address);

///
/// \brief Enables RX DMA mode on I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_rxdma_enable(const uint32_t address);

///
/// \brief Disables TX DMA mode on I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_txdma_disable(const uint32_t address);

///
/// \brief Disables RX DMA mode on I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_rxdma_disable(const uint32_t address);

///
/// \brief Enables selected interrupt in I2C.
///
/// \param[in] address   The i2c address.
/// \param[in] interrupt The interrupt type.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_interrupt_enable(const uint32_t address, const ll_i2c_interrupt_t interrupt);

///
/// \brief Disables selected interrupt in I2C.
///
/// \param[in] address   The i2c address.
/// \param[in] interrupt The interrupt type.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_interrupt_disable(const uint32_t address, const ll_i2c_interrupt_t interrupt);

///
/// \brief Sets digital noise filter on SDA and SCL input in I2C.
///
/// \param[in] address The i2c address.
/// \param[in] dnf     The digital noise filter capability.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_set_dnf(const uint32_t address, const ll_i2c_dnf_t dnf);

///
/// \brief Enables analog noise filter in I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_anf_enable(const uint32_t address);

///
/// \brief Disables analog noise filter in I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_anf_disable(const uint32_t address);

///
/// \brief Enables slave byte control in I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_sbc_enable(const uint32_t address);

///
/// \brief Disables slave byte control in I2C.
///
/// \param[in] address The i2c address.
///
/// \return ll_i2c_res_t   The I2C result.
/// \retval LL_I2C_RES_OK  On success.
/// \retval LL_I2C_RES_ERR Otherwise.
///
ll_i2c_res_t ll_i2c_sbc_disable(const uint32_t address);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_I2C_H */

