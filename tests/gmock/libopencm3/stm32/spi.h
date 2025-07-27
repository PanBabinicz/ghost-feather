#ifndef _GMOCK_LIBOPENCM3_SPI_H
#define _GMOCK_LIBOPENCM3_SPI_H

#include <stdint.h>

#define MMIO32(addr)		(*(volatile uint32_t *)((uintptr_t)(addr)))
#define SPI_CRCPR(spi_base) (MMIO32((spi_base) + 0x10))

#define SPI1_BASE           (0x40013000U)
#define SPI1                (SPI1_BASE)


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \breif Mock implementation of spi_enable function.
///
static inline void spi_enable(uint32_t spi)
{
    return;
}

///
/// \breif Mock implementation of spi_disable function.
///
static inline void spi_disable(uint32_t spi)
{
    return;
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
    return;
}

///
/// \breif Mock implementation of spi_read function.
///
static inline uint16_t spi_read(uint32_t spi)
{
    return 0;
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
