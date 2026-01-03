#ifndef _LL_SPI_H
#define _LL_SPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define CRCPOLY_RES_VAL (0x0007)

///
/// TODO
/// \brief The spi controller device type.
///
struct ll_spi_dev;

///
/// TODO
/// \brief The spi controller result type.
///
typedef enum ll_spi_res
{
    LL_SPI_RES_OK = 0,
    LL_SPI_RES_ERR,
} ll_spi_res_t;

/* TODO: Add idle status. */
///
/// \brief The spi controller result type.
///
typedef enum ll_spi_stat
{
    LL_SPI_STAT_DEINIT = 0,                         /*!< The spi controller is deinitialized.               */
    LL_SPI_STAT_INIT,                               /*!< The spi controller is initialized.                 */
    LL_SPI_STAT_RUN,                                /*!< The spi controller executes transaction.           */
    LL_SPI_STAT_STOP,                               /*!< The spi controller completed the transaction.      */
} ll_spi_stat_t;

///
/// TODO
/// \brief The spi ctrl clock phase type.
///
typedef enum ll_spi_cpha
{
    LL_SPI_CPHA_BEGIN = 0,                          /*!< The clock phase begin indicator.                   */
    LL_SPI_CPHA_0     = 0,                          /*!< Data is captured on the 1st clock edge after CS.   */
    LL_SPI_CPHA_1,                                  /*!< Data is captured on the 2nd clock edge after CS.   */
    LL_SPI_CPHA_TOTAL,                              /*!< The clock phase total indicator.                   */
} ll_spi_cpha_t;

///
/// TODO
/// \brief The spi ctrl clock polarity type.
///
typedef enum ll_spi_cpol
{
    LL_SPI_CPOL_BEGIN = 0,                          /*!< The clock polarity begin indicator.                */
    LL_SPI_CPOL_0     = 0,                          /*!< The clock polarity to 0 when idle.                 */
    LL_SPI_CPOL_1,                                  /*!< The clock polarity to 1 when idle.                 */
    LL_SPI_CPOL_TOTAL,                              /*!< The clock polarity total indicator.                */
} ll_spi_cpol_t;

///
/// TODO
/// \brief The spi ctrl bidirectional data mode type.
///
typedef enum ll_spi_bidimode
{
    LL_SPI_BIDIMODE_BEGIN = 0,                      /*!< The bidirectional data mode begin indicator.       */
    LL_SPI_BIDIMODE_0     = 0,                      /*!< 2-line unidirectional data mode selected.          */
    LL_SPI_BIDIMODE_1,                              /*!< 1-line bidirectional data mode selected.           */
    LL_SPI_BIDIMODE_TOTAL,                          /*!< The bidirectional data mode total indicator.       */
} ll_spi_bidimode_t;

///
/// TODO
/// \brief The spi ctrl output enable in bidirectional mode type.
///
typedef enum ll_spi_bidioe
{
    LL_SPI_BIDIOE_BEGIN = 0,                        /*!< The OE in bidirectional mode begin indicator.      */
    LL_SPI_BIDIOE_0     = 0,                        /*!< Output disabled (receive-only mode).               */
    LL_SPI_BIDIOE_1,                                /*!< Output enabled (transmit-only mode).               */
    LL_SPI_BIDIOE_TOTAL,                            /*!< The OE in bidirectional mode total indicator.      */
} ll_spi_bidioe_t;

///
/// TODO
/// \brief The spi ctrl receive only mode enable type.
///
typedef enum ll_spi_rxonly
{
    LL_SPI_RXONLY_BEGIN = 0,                        /*!< The receive only mode enable begin indicator.      */
    LL_SPI_RXONLY_0     = 0,                        /*!< Full-duplex (transmit and receive).                */
    LL_SPI_RXONLY_1,                                /*!< Output disabled (receive-only mode).               */
    LL_SPI_RXONLY_TOTAL,                            /*!< The receive only mode enable total indicator.      */
} ll_spi_rxonly_t;

///
/// TODO
/// \brief The spi ctrl frame format type.
///
typedef enum ll_spi_lsbfirst
{
    LL_SPI_LSBFIRST_BEGIN = 0,                      /*!< The frame format begin indicator.                  */
    LL_SPI_LSBFIRST_0     = 0,                      /*!< The data is transmitted/received with MSB first.   */
    LL_SPI_LSBFIRST_1,                              /*!< The data is transmitted/received with LSB first.   */
    LL_SPI_LSBFIRST_TOTAL,                          /*!< The frame format total indicator.                  */
} ll_spi_lsbfirst_t;

///
/// TODO
/// \brief The spi ctrl hardware CRC calculation type.
///
typedef enum ll_spi_crcen
{
    LL_SPI_CRCEN_BEGIN = 0,                         /*!< The hardware CRC calc enable begin indicator.      */
    LL_SPI_CRCEN_0     = 0,                         /*!< The hardware CRC calc disabled.                    */
    LL_SPI_CRCEN_1,                                 /*!< The hardware CRC calc enabled.                     */
    LL_SPI_CRCEN_TOTAL,                             /*!< The hardware CRC calc enable total indicator.      */
} ll_spi_crcen_t;

///
/// TODO
/// \brief The spi ctrl CRC length type.
///
typedef enum ll_spi_crcl
{
    LL_SPI_CRCL_BEGIN = 0,                          /*!< The hardware CRC length begin indicator.           */
    LL_SPI_CRCL_0     = 0,                          /*!< The hardware CRC length set to 8-bits.             */
    LL_SPI_CRCL_1,                                  /*!< The hardware CRC length set to 16-bits.            */
    LL_SPI_CRCL_TOTAL,                              /*!< The hardware CRC length total indicator.           */
} ll_spi_crcl_t;

///
/// TODO
/// \brief The spi ctrl software slave management type.
///
typedef enum ll_spi_ssm
{
    LL_SPI_SSM_BEGIN = 0,                           /*!< The software slave management begin indicator.     */
    LL_SPI_SSM_0     = 0,                           /*!< The software slave management disabled.            */
    LL_SPI_SSM_1,                                   /*!< The software slave management enabled.             */
    LL_SPI_SSM_TOTAL,                               /*!< The software slave management total indicator.     */
} ll_spi_ssm_t;

///
/// TODO
/// \brief The spi ctrl internal slave select type.
///
typedef enum ll_spi_ssi
{
    LL_SPI_SSI_BEGIN = 0,                           /*!< The internal slave select begin indicator.         */
    LL_SPI_SSI_0     = 0,                           /*!< The internal slave select disabled.                */
    LL_SPI_SSI_1,                                   /*!< The internal slave select enabled.                 */
    LL_SPI_SSI_TOTAL,                               /*!< The internal slave select total indicator.         */
} ll_spi_ssi_t;

///
/// TODO
/// \brief The spi ctrl master selection type.
///
typedef enum ll_spi_mstr
{
    LL_SPI_MSTR_BEGIN = 0,                          /*!< The master selection begin indicator.              */
    LL_SPI_MSTR_0     = 0,                          /*!< The slave configuration.                           */
    LL_SPI_MSTR_1,                                  /*!< The master configuration.                          */
    LL_SPI_MSTR_TOTAL,                              /*!< The master selection total indicator.              */
} ll_spi_mstr_t;

///
/// TODO
/// \brief The spi ctrl internal slave select type.
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
/// TODO
/// \brief The spi ctrl slave select output enable type.
///
typedef enum ll_spi_ssoe
{
    LL_SPI_SSOE_BEGIN = 0,                          /*!< The slave select output enable begin indicator.    */
    LL_SPI_SSOE_0     = 0,                          /*!< The slave select is disabled in master mode.       */
    LL_SPI_SSOE_1,                                  /*!< The slave select is enabled in master mode.        */
    LL_SPI_SSOE_TOTAL,                              /*!< The slave select output enable total indicator.    */
} ll_spi_ssoe_t;

///
/// TODO
/// \brief The spi ctrl frame format type.
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
/// TODO
/// \brief The spi ctrl NSS pulse management type.
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
/// TODO
/// \brief The spi ctrl FIFO reception threshold type.
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
/// TODO
/// \brief The spi ctrl last DMA transfer for transmission type.
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
/// TODO
/// \brief The spi ctrl last DMA transfer for reception type.
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
/// TODO
/// \brief Initializes the spi controller.
///
/// \param[in] dev The spi controller device.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_dev_init(struct ll_spi_dev *const dev);

/// TODO
/// \brief Deinitializes the spi controller.
///
/// \param[in] dev The spi controller device.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_dev_deinit(struct ll_spi_dev *const dev);

///
/// TODO
/// \brief Gets the spi device.
///
/// \return struct ll_spi_dev* The spi controller device address.
///
struct ll_spi_dev* ll_spi_dev_get(void);

///
/// TODO
/// \brief Sets the spi CRC polynomial value inside device.
///
/// \note  Default reset value is `0x0007`.
///
/// \param[in] dev           The spi controller device.
/// \param[in] crcpoly       The spi controller CRC polynomial value.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_crcpr_set(struct ll_spi_dev *const dev, const uint16_t crcpoly);

///
/// TODO
/// \brief Sets the spi clock phase index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] cpha          The spi controller clock phase index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_cpha_set(struct ll_spi_dev *const dev, const ll_spi_cpha_t cpha);

///
/// TODO
/// \brief Sets the spi clock polarity index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] cpol          The spi controller clock polarity index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_cpol_set(struct ll_spi_dev *const dev, const ll_spi_cpol_t cpol);

///
/// TODO
/// \brief Sets the spi bidirectional data mode index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] bidimode      The spi controller bidirectional data mode index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_bidimode_set(struct ll_spi_dev *const dev, const ll_spi_bidimode_t bidimode);

///
/// TODO
/// \brief Sets the spi output enable in bidirectional mode index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] bidioe        The spi controller output enable in bidirectional mode index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_bidioe_set(struct ll_spi_dev *const dev, const ll_spi_bidioe_t bidioe);

///
/// TODO
/// \brief Sets the spi receive only mode enable index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] rxonly        The spi controller receive only mode enable index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_rxonly_set(struct ll_spi_dev *const dev, const ll_spi_rxonly_t rxonly);

///
/// TODO
/// \brief Sets the spi frame format index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] lsbfirst      The spi controller frame format index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_lsbfirst_set(struct ll_spi_dev *const dev, const ll_spi_lsbfirst_t lsbfirst);

///
/// TODO
/// \brief Sets the spi hardware CRC calculation index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] crcen         The spi controller hardware CRC calculation index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_crcen_set(struct ll_spi_dev *const dev, const ll_spi_crcen_t crcen);

///
/// TODO
/// \brief Sets the spi CRC length index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] crcl          The spi controller CRC length index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_crcl_set(struct ll_spi_dev *const dev, const ll_spi_crcl_t crcl);

///
/// TODO
/// \brief Sets the spi software slave management index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ssm           The spi controller software slave management index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ssm_set(struct ll_spi_dev *const dev, const ll_spi_ssm_t ssm);

///
/// TODO
/// \brief Sets the spi internal slave select index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ssi           The spi controller internal slave select index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ssi_set(struct ll_spi_dev *const dev, const ll_spi_ssi_t ssi);

///
/// TODO
/// \brief Sets the spi master selection index inside dev.
///
/// \param[in] dev           The spi controller device.
/// \param[in] mstr          The spi controller master selection index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_mstr_set(struct ll_spi_dev *const dev, const ll_spi_mstr_t mstr);

///
/// TODO
/// \brief Sets the spi data size index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ds            The spi controller data size index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ds_set(struct ll_spi_dev *const dev, const ll_spi_ds_t ds);

///
/// TODO
/// \brief Sets the spi slave select output enable index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ssoe          The spi controller slave select output enable index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ssoe_set(struct ll_spi_dev *const dev, const ll_spi_ssoe_t ssoe);

///
/// TODO
/// \brief Sets the spi frame format inside index device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] frf           The spi controller frame format index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_frf_set(struct ll_spi_dev *const dev, const ll_spi_frf_t frf);

///
/// TODO
/// \brief Sets the spi NSS pulse mangement index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] nssp          The spi controller NSS pulse management index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_nssp_set(struct ll_spi_dev *const dev, const ll_spi_nssp_t nssp);

///
/// TODO
/// \brief Sets the spi FIFO reception threshold index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] frxth         The spi controller FIFO reception threshold index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_frxth_set(struct ll_spi_dev *const dev, const ll_spi_frxth_t frxth);

///
/// TODO
/// \brief Sets the spi last DMA transfer for transmission index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ldmatx        The spi controller last DMA transfer for transmission index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ldmatx_set(struct ll_spi_dev *const dev, const ll_spi_ldmatx_t ldmatx);

///
/// TODO
/// \brief Sets the spi last DMA transfer for reception index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ldmarx        The spi controller last DMA transfer for reception index.
///
/// \return ll_spi_res_t   The spi controller result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
ll_spi_res_t ll_spi_ldmarx_set(struct ll_spi_dev *const dev, const ll_spi_ldmarx_t ldmarx);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_SPI_H */
