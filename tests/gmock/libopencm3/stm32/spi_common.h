#ifndef _SPI_COMMON_H
#define _SPI_COMMON_H

#include <stdint.h>

#define SPI_FIFO_BUF_MAX_SZ (0x8000U)

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
    uint32_t tx_idx;
    uint32_t rx_idx;
    uint8_t buf[SPI_FIFO_BUF_MAX_SZ];
};

#endif  /* _SPI_COMMON_H */
