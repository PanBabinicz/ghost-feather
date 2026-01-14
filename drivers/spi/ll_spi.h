#ifndef _LL_SPI_H
#define _LL_SPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define CRCPOLY_RES_VAL (0x0007)

///
/// \brief The SPI device type.
///
struct ll_spi_dev;

///
/// \brief The SPI result type.
///
typedef enum ll_spi_res
{
    LL_SPI_RES_OK = 0,
    LL_SPI_RES_ERR,
} ll_spi_res_t;

///
/// \brief The SPI result type.
///
typedef enum ll_spi_stat
{
    LL_SPI_STAT_DEINIT = 0,                         /*!< The SPI is deinitialized.                          */
    LL_SPI_STAT_INIT,                               /*!< The SPI is initialized.                            */
    LL_SPI_STAT_RUN,                                /*!< The SPI executes transaction.                      */
    LL_SPI_STAT_STOP,                               /*!< The SPI completed the transaction.                 */
    LL_SPI_STAT_IDLE,                               /*!< The SPI is idle.                                   */
} ll_spi_stat_t;

///
/// \brief The SPI clock phase type.
///
typedef enum ll_spi_cpha
{
    LL_SPI_CPHA_BEGIN = 0,                          /*!< The clock phase begin indicator.                   */
    LL_SPI_CPHA_0     = 0,                          /*!< Data is captured on the 1st clock edge after CS.   */
    LL_SPI_CPHA_1,                                  /*!< Data is captured on the 2nd clock edge after CS.   */
    LL_SPI_CPHA_TOTAL,                              /*!< The clock phase total indicator.                   */
} ll_spi_cpha_t;

///
/// \brief The SPI clock polarity type.
///
typedef enum ll_spi_cpol
{
    LL_SPI_CPOL_BEGIN = 0,                          /*!< The clock polarity begin indicator.                */
    LL_SPI_CPOL_0     = 0,                          /*!< The clock polarity to 0 when idle.                 */
    LL_SPI_CPOL_1,                                  /*!< The clock polarity to 1 when idle.                 */
    LL_SPI_CPOL_TOTAL,                              /*!< The clock polarity total indicator.                */
} ll_spi_cpol_t;

///
/// \brief The SPI bidirectional data mode type.
///
typedef enum ll_spi_bidimode
{
    LL_SPI_BIDIMODE_BEGIN = 0,                      /*!< The bidirectional data mode begin indicator.       */
    LL_SPI_BIDIMODE_0     = 0,                      /*!< 2-line unidirectional data mode selected.          */
    LL_SPI_BIDIMODE_1,                              /*!< 1-line bidirectional data mode selected.           */
    LL_SPI_BIDIMODE_TOTAL,                          /*!< The bidirectional data mode total indicator.       */
} ll_spi_bidimode_t;

///
/// \brief The SPI output enable in bidirectional mode type.
///
typedef enum ll_spi_bidioe
{
    LL_SPI_BIDIOE_BEGIN = 0,                        /*!< The OE in bidirectional mode begin indicator.      */
    LL_SPI_BIDIOE_0     = 0,                        /*!< Output disabled (receive-only mode).               */
    LL_SPI_BIDIOE_1,                                /*!< Output enabled (transmit-only mode).               */
    LL_SPI_BIDIOE_TOTAL,                            /*!< The OE in bidirectional mode total indicator.      */
} ll_spi_bidioe_t;

///
/// \brief The SPI receive only mode enable type.
///
typedef enum ll_spi_rxonly
{
    LL_SPI_RXONLY_BEGIN = 0,                        /*!< The receive only mode enable begin indicator.      */
    LL_SPI_RXONLY_0     = 0,                        /*!< Full-duplex (transmit and receive).                */
    LL_SPI_RXONLY_1,                                /*!< Output disabled (receive-only mode).               */
    LL_SPI_RXONLY_TOTAL,                            /*!< The receive only mode enable total indicator.      */
} ll_spi_rxonly_t;

///
/// \brief The SPI frame format type.
///
typedef enum ll_spi_lsbfirst
{
    LL_SPI_LSBFIRST_BEGIN = 0,                      /*!< The frame format begin indicator.                  */
    LL_SPI_LSBFIRST_0     = 0,                      /*!< The data is transmitted/received with MSB first.   */
    LL_SPI_LSBFIRST_1,                              /*!< The data is transmitted/received with LSB first.   */
    LL_SPI_LSBFIRST_TOTAL,                          /*!< The frame format total indicator.                  */
} ll_spi_lsbfirst_t;

///
/// \brief The SPI hardware CRC calculation type.
///
typedef enum ll_spi_crcen
{
    LL_SPI_CRCEN_BEGIN = 0,                         /*!< The hardware CRC calc enable begin indicator.      */
    LL_SPI_CRCEN_0     = 0,                         /*!< The hardware CRC calc disabled.                    */
    LL_SPI_CRCEN_1,                                 /*!< The hardware CRC calc enabled.                     */
    LL_SPI_CRCEN_TOTAL,                             /*!< The hardware CRC calc enable total indicator.      */
} ll_spi_crcen_t;

///
/// \brief The SPI CRC length type.
///
typedef enum ll_spi_crcl
{
    LL_SPI_CRCL_BEGIN = 0,                          /*!< The hardware CRC length begin indicator.           */
    LL_SPI_CRCL_0     = 0,                          /*!< The hardware CRC length set to 8-bits.             */
    LL_SPI_CRCL_1,                                  /*!< The hardware CRC length set to 16-bits.            */
    LL_SPI_CRCL_TOTAL,                              /*!< The hardware CRC length total indicator.           */
} ll_spi_crcl_t;

///
/// \brief The SPI software slave management type.
///
typedef enum ll_spi_ssm
{
    LL_SPI_SSM_BEGIN = 0,                           /*!< The software slave management begin indicator.     */
    LL_SPI_SSM_0     = 0,                           /*!< The software slave management disabled.            */
    LL_SPI_SSM_1,                                   /*!< The software slave management enabled.             */
    LL_SPI_SSM_TOTAL,                               /*!< The software slave management total indicator.     */
} ll_spi_ssm_t;

///
/// \brief The SPI internal slave select type.
///
typedef enum ll_spi_ssi
{
    LL_SPI_SSI_BEGIN = 0,                           /*!< The internal slave select begin indicator.         */
    LL_SPI_SSI_0     = 0,                           /*!< The internal slave select disabled.                */
    LL_SPI_SSI_1,                                   /*!< The internal slave select enabled.                 */
    LL_SPI_SSI_TOTAL,                               /*!< The internal slave select total indicator.         */
} ll_spi_ssi_t;

///
/// \brief The SPI master selection type.
///
typedef enum ll_spi_mstr
{
    LL_SPI_MSTR_BEGIN = 0,                          /*!< The master selection begin indicator.              */
    LL_SPI_MSTR_0     = 0,                          /*!< The slave configuration.                           */
    LL_SPI_MSTR_1,                                  /*!< The master configuration.                          */
    LL_SPI_MSTR_TOTAL,                              /*!< The master selection total indicator.              */
} ll_spi_mstr_t;

///
/// \brief The SPI internal slave select type.
///
typedef enum ll_spi_ds
{
    LL_SPI_DS_BEGIN = 3,                            /*!< The data size begin indicator.                     */
    LL_SPI_DS_4     = 3,                            /*!< The 4-bit data size.                               */
    LL_SPI_DS_5,                                    /*!< The 5-bit data size.                               */
    LL_SPI_DS_6,                                    /*!< The 6-bit data size.                               */
    LL_SPI_DS_7,                                    /*!< The 7-bit data size.                               */
    LL_SPI_DS_8,                                    /*!< The 8-bit data size.                               */
    LL_SPI_DS_9,                                    /*!< The 9-bit data size.                               */
    LL_SPI_DS_10,                                   /*!< The 10-bit data size.                              */
    LL_SPI_DS_11,                                   /*!< The 11-bit data size.                              */
    LL_SPI_DS_12,                                   /*!< The 12-bit data size.                              */
    LL_SPI_DS_13,                                   /*!< The 13-bit data size.                              */
    LL_SPI_DS_14,                                   /*!< The 14-bit data size.                              */
    LL_SPI_DS_15,                                   /*!< The 15-bit data size.                              */
    LL_SPI_DS_16,                                   /*!< The 16-bit data size.                              */
    LL_SPI_DS_TOTAL,                                /*!< The data size total indicator.                     */
} ll_spi_ds_t;

///
/// \brief The SPI slave select output enable type.
///
typedef enum ll_spi_ssoe
{
    LL_SPI_SSOE_BEGIN = 0,                          /*!< The slave select output enable begin indicator.    */
    LL_SPI_SSOE_0     = 0,                          /*!< The slave select is disabled in master mode.       */
    LL_SPI_SSOE_1,                                  /*!< The slave select is enabled in master mode.        */
    LL_SPI_SSOE_TOTAL,                              /*!< The slave select output enable total indicator.    */
} ll_spi_ssoe_t;

///
/// \brief The SPI frame format type.
///
/// \note  Set the FRF bit if the TI protocol is required (keep NSSP bit cleared in TI mode).
///
typedef enum ll_spi_frf
{
    LL_SPI_FRF_BEGIN = 0,                           /*!< The frame format begin indicator.                  */
    LL_SPI_FRF_0     = 0,                           /*!< The frame format set to motorola.                  */
    LL_SPI_FRF_1,                                   /*!< The frame format set to TI.                        */
    LL_SPI_FRF_TOTAL,                               /*!< The frame format total indicator.                  */
} ll_spi_frf_t;

///
/// \brief The SPI NSS pulse management type.
///
/// \note  This bit must be written only when the SPI is disabled (SPE=0).
///        This bit is not used in I2S mode and SPI TI mode.
///
typedef enum ll_spi_nssp
{
    LL_SPI_NSSP_BEGIN = 0,                          /*!< The NSS pulse management begin indicator.          */
    LL_SPI_NSSP_0     = 0,                          /*!< The NSS pulse management is disabled.              */
    LL_SPI_NSSP_1,                                  /*!< The NSS pulse management is enabled.               */
    LL_SPI_NSSP_TOTAL,                              /*!< The NSS pulse management total indicator.          */
} ll_spi_nssp_t;

///
/// \brief The SPI FIFO reception threshold type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum ll_spi_frxth
{
    LL_SPI_FRXTH_BEGIN = 0,                         /*!< The FIFO reception threshold begin indicator.      */
    LL_SPI_FRXTH_0     = 0,                         /*!< When the FIFO level >= 1/2, generate RXNE event.   */
    LL_SPI_FRXTH_1,                                 /*!< When the FIFO level >= 1/4, generate RXNE event.   */
    LL_SPI_FRXTH_TOTAL,                             /*!< The FIFO reception threshold total indicator.      */
} ll_spi_frxth_t;

///
/// \brief The SPI last DMA transfer for transmission type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum ll_spi_ldmatx
{
    LL_SPI_LDMATX_BEGIN = 0,                        /*!< LDMA transfer for transmission begin indicator.    */
    LL_SPI_LDMATX_0     = 0,                        /*!< Number of data to transfer is even.                */
    LL_SPI_LDMATX_1,                                /*!< Number of data to transfer is odd.                 */
    LL_SPI_LDMATX_TOTAL,                            /*!< LDMA transfer for transmission total indicator.    */
} ll_spi_ldmatx_t;

///
/// \brief The SPI last DMA transfer for reception type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum ll_spi_ldmarx
{
    LL_SPI_LDMARX_BEGIN = 0,                        /*!< LDMA transfer for reception begin indicator.       */
    LL_SPI_LDMARX_0     = 0,                        /*!< Number of data to transfer is even.                */
    LL_SPI_LDMARX_1,                                /*!< Number of data to transfer is odd.                 */
    LL_SPI_LDMARX_TOTAL,                            /*!< LDMA transfer for reception total indicator.       */
} ll_spi_ldmarx_t;

///
/// \brief Initializes the SPI.
///
/// \param[in] dev The SPI device.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_dev_init(struct ll_spi_dev *const dev);

/// \brief Deinitializes the SPI.
///
/// \param[in] dev The SPI device.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_dev_deinit(struct ll_spi_dev *const dev);

///
/// \brief Gets the SPI device.
///
/// \return struct ll_spi_dev* The SPI device address.
///
struct ll_spi_dev* ll_spi_dev_get(void);

///
/// \brief Sets the SPI CRC polynomial value inside device.
///
/// \note  Default reset value is `0x0007`.
///
/// \param[in] dev     The SPI device.
/// \param[in] crcpoly The SPI CRC polynomial value.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_crcpr_set(struct ll_spi_dev *const dev, const uint16_t crcpoly);

///
/// \brief Sets the SPI clock phase index inside device.
///
/// \param[in] dev  The SPI device.
/// \param[in] cpha The SPI clock phase index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_cpha_set(struct ll_spi_dev *const dev, const ll_spi_cpha_t cpha);

///
/// \brief Sets the SPI clock polarity index inside device.
///
/// \param[in] dev  The SPI device.
/// \param[in] cpol The SPI clock polarity index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_cpol_set(struct ll_spi_dev *const dev, const ll_spi_cpol_t cpol);

///
/// \brief Sets the SPI bidirectional data mode index inside device.
///
/// \param[in] dev      The SPI device.
/// \param[in] bidimode The SPI bidirectional data mode index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_bidimode_set(struct ll_spi_dev *const dev, const ll_spi_bidimode_t bidimode);

///
/// \brief Sets the SPI output enable in bidirectional mode index inside device.
///
/// \param[in] dev    The SPI device.
/// \param[in] bidioe The SPI output enable in bidirectional mode index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_bidioe_set(struct ll_spi_dev *const dev, const ll_spi_bidioe_t bidioe);

///
/// \brief Sets the SPI receive only mode enable index inside device.
///
/// \param[in] dev    The SPI device.
/// \param[in] rxonly The SPI receive only mode enable index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_rxonly_set(struct ll_spi_dev *const dev, const ll_spi_rxonly_t rxonly);

///
/// \brief Sets the SPI frame format index inside device.
///
/// \param[in] dev      The SPI device.
/// \param[in] lsbfirst The SPI frame format index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_lsbfirst_set(struct ll_spi_dev *const dev, const ll_spi_lsbfirst_t lsbfirst);

///
/// \brief Sets the SPI hardware CRC calculation index inside device.
///
/// \param[in] dev   The SPI device.
/// \param[in] crcen The SPI hardware CRC calculation index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_crcen_set(struct ll_spi_dev *const dev, const ll_spi_crcen_t crcen);

///
/// \brief Sets the SPI CRC length index inside device.
///
/// \param[in] dev  The SPI device.
/// \param[in] crcl The SPI CRC length index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_crcl_set(struct ll_spi_dev *const dev, const ll_spi_crcl_t crcl);

///
/// \brief Sets the SPI software slave management index inside device.
///
/// \param[in] dev The SPI device.
/// \param[in] ssm The SPI software slave management index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ssm_set(struct ll_spi_dev *const dev, const ll_spi_ssm_t ssm);

///
/// \brief Sets the SPI internal slave select index inside device.
///
/// \param[in] dev The SPI device.
/// \param[in] ssi The SPI internal slave select index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ssi_set(struct ll_spi_dev *const dev, const ll_spi_ssi_t ssi);

///
/// \brief Sets the SPI master selection index inside dev.
///
/// \param[in] dev  The SPI device.
/// \param[in] mstr The SPI master selection index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_mstr_set(struct ll_spi_dev *const dev, const ll_spi_mstr_t mstr);

///
/// \brief Sets the SPI data size index inside device.
///
/// \param[in] dev The SPI device.
/// \param[in] ds  The SPI data size index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ds_set(struct ll_spi_dev *const dev, const ll_spi_ds_t ds);

///
/// \brief Sets the SPI slave select output enable index inside device.
///
/// \param[in] dev  The SPI device.
/// \param[in] ssoe The SPI slave select output enable index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ssoe_set(struct ll_spi_dev *const dev, const ll_spi_ssoe_t ssoe);

///
/// \brief Sets the SPI frame format inside index device.
///
/// \param[in] dev The SPI device.
/// \param[in] frf The SPI frame format index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_frf_set(struct ll_spi_dev *const dev, const ll_spi_frf_t frf);

///
/// \brief Sets the SPI NSS pulse mangement index inside device.
///
/// \param[in] dev  The SPI device.
/// \param[in] nssp The SPI NSS pulse management index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_nssp_set(struct ll_spi_dev *const dev, const ll_spi_nssp_t nssp);

///
/// \brief Sets the SPI FIFO reception threshold index inside device.
///
/// \param[in] dev   The SPI device.
/// \param[in] frxth The SPI FIFO reception threshold index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_frxth_set(struct ll_spi_dev *const dev, const ll_spi_frxth_t frxth);

///
/// \brief Sets the SPI last DMA transfer for transmission index inside device.
///
/// \param[in] dev    The SPI device.
/// \param[in] ldmatx The SPI last DMA transfer for transmission index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ldmatx_set(struct ll_spi_dev *const dev, const ll_spi_ldmatx_t ldmatx);

///
/// \brief Sets the SPI last DMA transfer for reception index inside device.
///
/// \param[in] dev    The SPI device.
/// \param[in] ldmarx The SPI last DMA transfer for reception index.
///
/// \return ll_spi_res_t   The SPI result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ldmarx_set(struct ll_spi_dev *const dev, const ll_spi_ldmarx_t ldmarx);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_SPI_H */
