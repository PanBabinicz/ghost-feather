#ifndef _GMOCK_LIBOPENCM3_SPI_H
#define _GMOCK_LIBOPENCM3_SPI_H

#include <stdint.h>

#define SPI_FIFO_BUF_MAX_SZ (0xffU)

#define SPI_CRCPR(spi_base) (SPI_CRCPR_ARR[spi_base])

#define SPI1                (SPI_INTF_1)
#define SPI2                (SPI_INTF_2)
#define SPI3                (SPI_INTF_3)
#define SPI4                (SPI_INTF_4)
#define SPI5                (SPI_INTF_5)

#define SPI_CR1_SPE         (1 << 6)

///
/// \breif The spi interface type.
///
typedef enum spi_intf
{
    SPI_INTF_1 = 0,
    SPI_INTF_2,
    SPI_INTF_3,
    SPI_INTF_4,
    SPI_INTF_5,
    SPI_INTF_6,
    SPI_INTF_TOTAL,
} spi_intf_t;

struct spi_dr
{
    uint8_t idx;
    uint8_t buf[SPI_FIFO_BUF_MAX_SZ];
};

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

static uint32_t      SPI_CR1_ARR[SPI_INTF_TOTAL];
static uint32_t      SPI_CRCPR_ARR[SPI_INTF_TOTAL];
static struct spi_dr SPI_DR_ARR[SPI_INTF_TOTAL];

///
/// \breif Mock implementation of spi_enable function.
///
static inline void spi_enable(uint32_t spi)
{
    SPI_CR1_ARR[spi] |= SPI_CR1_SPE;
}

///
/// \breif Mock implementation of spi_disable function.
///
static inline void spi_disable(uint32_t spi)
{
    SPI_CR1_ARR[spi] &= ~(SPI_CR1_SPE);
}

///
/// \breif Mock implementation of spi_clean_disable function.
///
static inline uint16_t spi_clean_disable(uint32_t spi)
{
    return 0;
}

///
/// \breif Mock implementation of spi_write function.
///
static inline void spi_write(uint32_t spi, uint16_t data)
{
    return;
}

///
/// \breif Mock implementation of spi_send function.
///
static inline void spi_send(uint32_t spi, uint16_t data)
{
    SPI_DR_ARR[spi].buf[SPI_DR_ARR[spi].idx] = data;
    SPI_DR_ARR[spi].idx++;
}

///
/// \breif Mock implementation of spi_read function.
///
static inline uint16_t spi_read(uint32_t spi)
{
    uint8_t data = SPI_DR_ARR[spi].buf[SPI_DR_ARR[spi].idx];

    SPI_DR_ARR[spi].idx--;

    return data;
}

///
/// \breif Mock implementation of spi_xfer function.
///
static inline uint16_t spi_xfer(uint32_t spi, uint16_t data)
{
    return 0;
}

///
/// \breif Mock implementation of spi_set_bidirectional_mode function.
///
static inline void spi_set_bidirectional_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_unidirectional_mode function.
///
static inline void spi_set_unidirectional_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_bidirectional_receive_only_mode function.
///
static inline void spi_set_bidirectional_receive_only_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_bidirectional_transmit_only_mode function.
///
static inline void spi_set_bidirectional_transmit_only_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_crc function.
///
static inline void spi_enable_crc(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_crc function.
///
static inline void spi_disable_crc(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_next_tx_from_buffer function.
///
static inline void spi_set_next_tx_from_buffer(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_next_tx_from_crc function.
///
static inline void spi_set_next_tx_from_crc(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_full_duplex_mode function.
///
static inline void spi_set_full_duplex_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_receive_only_mode function.
///
static inline void spi_set_receive_only_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_software_slave_management function.
///
static inline void spi_disable_software_slave_management(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_software_slave_management function.
///
static inline void spi_enable_software_slave_management(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_nss_high function.
///
static inline void spi_set_nss_high(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_nss_low function.
///
static inline void spi_set_nss_low(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_send_lsb_first function.
///
static inline void spi_send_lsb_first(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_send_msb_first function.
///
static inline void spi_send_msb_first(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_baudrate_prescale function.
///
static inline void spi_set_baudrate_prescale(uint32_t spi, uint8_t baudrate)
{
    return;
}

///
/// \breif Mock implementation of spi_set_master_mode function.
///
static inline void spi_set_master_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_slave_mode function.
///
static inline void spi_set_slave_mode(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_clock_polarity_1 function.
///
static inline void spi_set_clock_polarity_1(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_clock_polarity_0 function.
///
static inline void spi_set_clock_polarity_0(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_clock_phase_1 function.
///
static inline void spi_set_clock_phase_1(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_clock_phase_0 function.
///
static inline void spi_set_clock_phase_0(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_tx_buffer_empty_interrupt function.
///
static inline void spi_enable_tx_buffer_empty_interrupt(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_tx_buffer_empty_interrupt function.
///
static inline void spi_disable_tx_buffer_empty_interrupt(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_rx_buffer_not_empty_interrupt function.
///
static inline void spi_enable_rx_buffer_not_empty_interrupt(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_rx_buffer_not_empty_interrupt function.
///
static inline void spi_disable_rx_buffer_not_empty_interrupt(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_error_interrupt function.
///
static inline void spi_enable_error_interrupt(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_error_interrupt function.
///
static inline void spi_disable_error_interrupt(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_ss_output function.
///
static inline void spi_enable_ss_output(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_ss_output function.
///
static inline void spi_disable_ss_output(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_tx_dma function.
///
static inline void spi_enable_tx_dma(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_tx_dma function.
///
static inline void spi_disable_tx_dma(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_rx_dma function.
///
static inline void spi_enable_rx_dma(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_rx_dma function.
///
static inline void spi_disable_rx_dma(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_standard_mode function.
///
static inline void spi_set_standard_mode(uint32_t spi, uint8_t mode)
{
    return;
}

///
/// \breif Mock implementation of spi_init_master function.
///
static inline int spi_init_master(uint32_t spi, uint32_t br, uint32_t cpol, uint32_t cpha, uint32_t lsbfirst)
{
    return 0;
}

///
/// \breif Mock implementation of spi_send8 function.
///
static inline void spi_send8(uint32_t spi, uint8_t data)
{
    return;
}

///
/// \breif Mock implementation of spi_read8 function.
///
static inline uint8_t spi_read8(uint32_t spi)
{
    return 0;
}

///
/// \breif Mock implementation of spi_set_crcl_8bit function.
///
static inline void spi_set_crcl_8bit(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_crcl_16bit function.
///
static inline void spi_set_crcl_16bit(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_data_size function.
///
static inline void spi_set_data_size(uint32_t spi, uint16_t data_s)
{
    return;
}

///
/// \breif Mock implementation of spi_fifo_reception_threshold_8bit function.
///
static inline void spi_fifo_reception_threshold_8bit(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_fifo_reception_threshold_16bit function.
///
static inline void spi_fifo_reception_threshold_16bit(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_enable_nssp function.
///
static inline void spi_enable_nssp(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable_nssp function.
///
static inline void spi_disable_nssp(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_ldmatx_even function.
///
static inline void spi_set_ldmatx_even(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_ldmatx_odd function.
///
static inline void spi_set_ldmatx_odd(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_ldmarx_even function.
///
static inline void spi_set_ldmarx_even(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_ldmarx_odd function.
///
static inline void spi_set_ldmarx_odd(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_frf_ti function.
///
static inline void spi_set_frf_ti(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_set_frf_motorola function.
///
static inline void spi_set_frf_motorola(uint32_t spi)
{
    return;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _GMOCK_LIBOPENCM3_SPI_H */
