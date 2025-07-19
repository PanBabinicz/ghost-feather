#ifndef _SPI_CTRL_H
#define _SPI_CTRL_H

#include <stdint.h>

#define CRCPOLY_RES_VAL (0x0007)

///
/// \brief The spi controller instance type.
///
struct spi_ctrl_dev;

///
/// \brief The spi controller result type.
///
typedef enum spi_ctrl_res
{
    SPI_CTRL_RES_OK = 0,
    SPI_CTRL_RES_ERR,
} spi_ctrl_res_t;

///
/// \brief The spi controller result type.
///
typedef enum spi_ctrl_stat
{
    SPI_CTRL_STAT_DEINIT = 0,                       /*!< The spi controller is deinitialized.               */
    SPI_CTRL_STAT_INIT,                             /*!< The spi controller is initialized.                 */
    SPI_CTRL_STAT_RUN,                              /*!< The spi controller executes transaction.           */
    SPI_CTRL_STAT_STOP,                             /*!< The spi controller completed the transaction.      */
} spi_ctrl_stat_t;

///
/// \brief The spi ctrl clock phase type.
///
typedef enum spi_ctrl_cpha
{
    SPI_CTRL_CPHA_BEGIN = 0,                        /*!< The clock phase begin indicator.                   */
    SPI_CTRL_CPHA_0     = 0,                        /*!< Data is captured on the 1st clock edge after CS.   */
    SPI_CTRL_CPHA_1,                                /*!< Data is captured on the 2nd clock edge after CS.   */
    SPI_CTRL_CPHA_TOTAL,                            /*!< The clock phase total indicator.                   */
} spi_ctrl_cpha_t;

///
/// \brief The spi ctrl clock polarity type.
///
typedef enum spi_ctrl_cpol
{
    SPI_CTRL_CPOL_BEGIN = 0,                        /*!< The clock polarity begin indicator.                */
    SPI_CTRL_CPOL_0     = 0,                        /*!< The clock polarity to 0 when idle.                 */
    SPI_CTRL_CPOL_1,                                /*!< The clock polarity to 1 when idle.                 */
    SPI_CTRL_CPOL_TOTAL,                            /*!< The clock polarity total indicator.                */
} spi_ctrl_cpol_t;

///
/// \brief The spi ctrl bidirectional data mode type.
///
typedef enum spi_ctrl_bidimode
{
    SPI_CTRL_BIDIMODE_BEGIN = 0,                    /*!< The bidirectional data mode begin indicator.       */
    SPI_CTRL_BIDIMODE_0     = 0,                    /*!< 2-line unidirectional data mode selected.          */
    SPI_CTRL_BIDIMODE_1,                            /*!< 1-line bidirectional data mode selected.           */
    SPI_CTRL_BIDIMODE_TOTAL,                        /*!< The bidirectional data mode total indicator.       */
} spi_ctrl_bidimode_t;

///
/// \brief The spi ctrl output enable in bidirectional mode type.
///
typedef enum spi_ctrl_bidioe
{
    SPI_CTRL_BIDIOE_BEGIN = 0,                      /*!< The OE in bidirectional mode begin indicator.      */
    SPI_CTRL_BIDIOE_0     = 0,                      /*!< Output disabled (receive-only mode).               */
    SPI_CTRL_BIDIOE_1,                              /*!< Output enabled (transmit-only mode).               */
    SPI_CTRL_BIDIOE_TOTAL,                          /*!< The OE in bidirectional mode total indicator.      */
} spi_ctrl_bidioe_t;

///
/// \brief The spi ctrl receive only mode enable type.
///
typedef enum spi_ctrl_rxonly
{
    SPI_CTRL_RXONLY_BEGIN = 0,                      /*!< The receive only mode enable begin indicator.      */
    SPI_CTRL_RXONLY_0     = 0,                      /*!< Full-duplex (transmit and receive).                */
    SPI_CTRL_RXONLY_1,                              /*!< Output disabled (receive-only mode).               */
    SPI_CTRL_RXONLY_TOTAL,                          /*!< The receive only mode enable total indicator.      */
} spi_ctrl_rxonly_t;

///
/// \brief The spi ctrl frame format type.
///
typedef enum spi_ctrl_lsbfirst
{
    SPI_CTRL_LSBFIRST_BEGIN = 0,                    /*!< The frame format begin indicator.                  */
    SPI_CTRL_LSBFIRST_0     = 0,                    /*!< The data is transmitted/received with MSB first.   */
    SPI_CTRL_LSBFIRST_1,                            /*!< The data is transmitted/received with LSB first.   */
    SPI_CTRL_LSBFIRST_TOTAL,                        /*!< The frame format total indicator.                  */
} spi_ctrl_lsbfirst_t;

///
/// \brief The spi ctrl hardware CRC calculation type.
///
typedef enum spi_ctrl_crcen
{
    SPI_CTRL_CRCEN_BEGIN = 0,                       /*!< The hardware CRC calc enable begin indicator.      */
    SPI_CTRL_CRCEN_0     = 0,                       /*!< The hardware CRC calc disabled.                    */
    SPI_CTRL_CRCEN_1,                               /*!< The hardware CRC calc enabled.                     */
    SPI_CTRL_CRCEN_TOTAL,                           /*!< The hardware CRC calc enable total indicator.      */
} spi_ctrl_crcen_t;

///
/// \brief The spi ctrl CRC length type.
///
typedef enum spi_ctrl_crcl
{
    SPI_CTRL_CRCL_BEGIN = 0,                        /*!< The hardware CRC length begin indicator.           */
    SPI_CTRL_CRCL_0     = 0,                        /*!< The hardware CRC length set to 8-bits.             */
    SPI_CTRL_CRCL_1,                                /*!< The hardware CRC length set to 16-bits.            */
    SPI_CTRL_CRCL_TOTAL,                            /*!< The hardware CRC length total indicator.           */
} spi_ctrl_crcl_t;

///
/// \brief The spi ctrl software slave management type.
///
typedef enum spi_ctrl_ssm
{
    SPI_CTRL_SSM_BEGIN = 0,                         /*!< The software slave management begin indicator.     */
    SPI_CTRL_SSM_0     = 0,                         /*!< The software slave management disabled.            */
    SPI_CTRL_SSM_1,                                 /*!< The software slave management enabled.             */
    SPI_CTRL_SSM_TOTAL,                             /*!< The software slave management total indicator.     */
} spi_ctrl_ssm_t;

///
/// \brief The spi ctrl internal slave select type.
///
typedef enum spi_ctrl_ssi
{
    SPI_CTRL_SSI_BEGIN = 0,                         /*!< The internal slave select begin indicator.         */
    SPI_CTRL_SSI_0     = 0,                         /*!< The internal slave select disabled.                */
    SPI_CTRL_SSI_1,                                 /*!< The internal slave select enabled.                 */
    SPI_CTRL_SSI_TOTAL,                             /*!< The internal slave select total indicator.         */
} spi_ctrl_ssi_t;

///
/// \brief The spi ctrl master selection type.
///
typedef enum spi_ctrl_mstr
{
    SPI_CTRL_MSTR_BEGIN = 0,                        /*!< The master selection begin indicator.              */
    SPI_CTRL_MSTR_0     = 0,                        /*!< The slave configuration.                           */
    SPI_CTRL_MSTR_1,                                /*!< The master configuration.                          */
    SPI_CTRL_MSTR_TOTAL,                            /*!< The master selection total indicator.              */
} spi_ctrl_mstr_t;

///
/// \brief The spi ctrl internal slave select type.
///
typedef enum spi_ctrl_ds
{
    SPI_CTRL_DS_BEGIN = 3,                          /*!< The data size begin indicator.                     */
    SPI_CTRL_DS_4     = 3,                          /*!< The 4-bit data size.                               */
    SPI_CTRL_DS_5,                                  /*!< The 5-bit data size.                               */
    SPI_CTRL_DS_6,                                  /*!< The 6-bit data size.                               */
    SPI_CTRL_DS_7,                                  /*!< The 7-bit data size.                               */
    SPI_CTRL_DS_8,                                  /*!< The 8-bit data size.                               */
    SPI_CTRL_DS_9,                                  /*!< The 9-bit data size.                               */
    SPI_CTRL_DS_10,                                 /*!< The 10-bit data size.                              */
    SPI_CTRL_DS_11,                                 /*!< The 11-bit data size.                              */
    SPI_CTRL_DS_12,                                 /*!< The 12-bit data size.                              */
    SPI_CTRL_DS_13,                                 /*!< The 13-bit data size.                              */
    SPI_CTRL_DS_14,                                 /*!< The 14-bit data size.                              */
    SPI_CTRL_DS_15,                                 /*!< The 15-bit data size.                              */
    SPI_CTRL_DS_16,                                 /*!< The 16-bit data size.                              */
    SPI_CTRL_DS_TOTAL,                              /*!< The data size total indicator.                     */
} spi_ctrl_ds_t;

///
/// \brief The spi ctrl slave select output enable type.
///
typedef enum spi_ctrl_ssoe
{
    SPI_CTRL_SSOE_BEGIN = 0,                        /*!< The slave select output enable begin indicator.    */
    SPI_CTRL_SSOE_0     = 0,                        /*!< The slave select is disabled in master mode.       */
    SPI_CTRL_SSOE_1,                                /*!< The slave select is enabled in master mode.        */
    SPI_CTRL_SSOE_TOTAL,                            /*!< The slave select output enable total indicator.    */
} spi_ctrl_ssoe_t;

///
/// \brief The spi ctrl frame format type.
///
/// \note  Set the FRF bit if the TI protocol is required (keep NSSP bit cleared in TI mode).
///
typedef enum spi_ctrl_frf
{
    SPI_CTRL_FRF_BEGIN = 0,                         /*!< The frame format begin indicator.                  */
    SPI_CTRL_FRF_0     = 0,                         /*!< The frame format set to motorola.                  */
    SPI_CTRL_FRF_1,                                 /*!< The frame format set to TI.                        */
    SPI_CTRL_FRF_TOTAL,                             /*!< The frame format total indicator.                  */
} spi_ctrl_frf_t;

///
/// \brief The spi ctrl NSS pulse management type.
///
/// \note  This bit must be written only when the SPI is disabled (SPE=0).
///        This bit is not used in I2S mode and SPI TI mode.
///
typedef enum spi_ctrl_nssp
{
    SPI_CTRL_NSSP_BEGIN = 0,                        /*!< The NSS pulse management begin indicator.          */
    SPI_CTRL_NSSP_0     = 0,                        /*!< The NSS pulse management is disabled.              */
    SPI_CTRL_NSSP_1,                                /*!< The NSS pulse management is enabled.               */
    SPI_CTRL_NSSP_TOTAL,                            /*!< The NSS pulse management total indicator.          */
} spi_ctrl_nssp_t;

///
/// \brief The spi ctrl FIFO reception threshold type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum spi_ctrl_frxth
{
    SPI_CTRL_FRXTH_BEGIN = 0,                       /*!< The FIFO reception threshold begin indicator.      */
    SPI_CTRL_FRXTH_0     = 0,                       /*!< When the FIFO level >= 1/2, generate RXNE event.   */
    SPI_CTRL_FRXTH_1,                               /*!< When the FIFO level >= 1/4, generate RXNE event.   */
    SPI_CTRL_FRXTH_TOTAL,                           /*!< The FIFO reception threshold total indicator.      */
} spi_ctrl_frxth_t;

///
/// \brief The spi ctrl last DMA transfer for transmission type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum spi_ctrl_ldmatx
{
    SPI_CTRL_LDMATX_BEGIN = 0,                      /*!< LDMA transfer for transmission begin indicator.    */
    SPI_CTRL_LDMATX_0     = 0,                      /*!< Number of data to transfer is even.                */
    SPI_CTRL_LDMATX_1,                              /*!< Number of data to transfer is odd.                 */
    SPI_CTRL_LDMATX_TOTAL,                          /*!< LDMA transfer for transmission total indicator.    */
} spi_ctrl_ldmatx_t;

///
/// \brief The spi ctrl last DMA transfer for reception type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum spi_ctrl_ldmarx
{
    SPI_CTRL_LDMARX_BEGIN = 0,                      /*!< LDMA transfer for reception begin indicator.       */
    SPI_CTRL_LDMARX_0     = 0,                      /*!< Number of data to transfer is even.                */
    SPI_CTRL_LDMARX_1,                              /*!< Number of data to transfer is odd.                 */
    SPI_CTRL_LDMARX_TOTAL,                          /*!< LDMA transfer for reception total indicator.       */
} spi_ctrl_ldmarx_t;

///
/// \brief Initializes the spi controller.
///
/// \param[in] dev           The spi controller device.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_init(struct spi_ctrl_dev *const dev);

///
/// \brief Deinitializes the spi controller.
///
/// \param[in] dev           The spi controller device.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_deinit(struct spi_ctrl_dev *const dev);

///
/// \brief Gets the spi device.
///
/// \param[out] dev          The pointer to the spi controller device.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_get_dev(const struct spi_ctrl_dev **dev);

///
/// \brief Begins an spi transaction by enabling the peripheral and managing NSS if needed.
///
/// \param[in] dev           The spi controller device.
/// \param[in] gpio_port     The gpio port identifier.
/// \param[in] gpios         The gpio pin identifiers. If multiple pins are to be changed,
///                          use bitwise OR '|' to separate them.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_begin(const struct spi_ctrl_dev *const dev, const uint32_t gpio_port,
                              const uint32_t gpios);

///
/// \brief Ends an spi transaction by disabling the peripheral and managing NSS if needed.
///
/// \param[in] dev           The spi controller device.
/// \param[in] gpio_port     The gpio port identifier.
/// \param[in] gpios         The gpio pin identifiers. If multiple pins are to be changed,
///                          use bitwise OR '|' to separate them.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_end(const struct spi_ctrl_dev *const dev, const uint32_t gpio_port,
                            const uint32_t gpios);

///
/// \brief Receives the specified number of bytes over spi.
///
/// \param[in] dev           The pointer to the spi controller device.
/// \param[in] buf           The pointer to the data buffer.
/// \param[in] sz            The number of bytes to transmit.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_recv(const struct spi_ctrl_dev *const dev, uint8_t *const buf,
                             const uint32_t sz);

///
/// \brief Sends the specified number of bytes over spi.
///
/// \param[in] dev           The pointer to the spi controller device.
/// \param[in] buf           The pointer to the data buffer.
/// \param[in] sz            The number of bytes to transmit.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_send(const struct spi_ctrl_dev *const dev, const uint8_t *const buf,
                             const uint32_t sz);

///
/// \brief Sets the spi CRC polynomial value inside device.
///
/// \note  Default reset value is `0x0007`.
///
/// \param[in] dev           The spi controller device.
/// \param[in] crcpoly       The spi controller CRC polynomial value.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_crcpr(struct spi_ctrl_dev *const dev, const uint16_t crcpoly);

///
/// \brief Sets the spi clock phase index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] cpha          The spi controller clock phase index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_cpha(struct spi_ctrl_dev *const dev, const spi_ctrl_cpha_t cpha);

///
/// \brief Sets the spi clock polarity index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] cpol          The spi controller clock polarity index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_cpol(struct spi_ctrl_dev *const dev, const spi_ctrl_cpol_t cpol);

///
/// \brief Sets the spi bidirectional data mode index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] bidimode      The spi controller bidirectional data mode index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_bidimode(struct spi_ctrl_dev *const dev, const spi_ctrl_bidimode_t bidimode);

///
/// \brief Sets the spi output enable in bidirectional mode index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] bidioe        The spi controller output enable in bidirectional mode index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_bidioe(struct spi_ctrl_dev *const dev, const spi_ctrl_bidioe_t bidioe);

///
/// \brief Sets the spi receive only mode enable index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] rxonly        The spi controller receive only mode enable index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_rxonly(struct spi_ctrl_dev *const dev, const spi_ctrl_rxonly_t rxonly);

///
/// \brief Sets the spi frame format index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] lsbfirst      The spi controller frame format index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_lsbfirst(struct spi_ctrl_dev *const dev, const spi_ctrl_lsbfirst_t lsbfirst);

///
/// \brief Sets the spi hardware CRC calculation index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] crcen         The spi controller hardware CRC calculation index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_crcen(struct spi_ctrl_dev *const dev, const spi_ctrl_crcen_t crcen);

///
/// \brief Sets the spi CRC length index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] crcl          The spi controller CRC length index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_crcl(struct spi_ctrl_dev *const dev, const spi_ctrl_crcl_t crcl);

///
/// \brief Sets the spi software slave management index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ssm           The spi controller software slave management index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_ssm(struct spi_ctrl_dev *const dev, const spi_ctrl_ssm_t ssm);

///
/// \brief Sets the spi internal slave select index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ssi           The spi controller internal slave select index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_ssi(struct spi_ctrl_dev *const dev, const spi_ctrl_ssi_t ssi);

///
/// \brief Sets the spi master selection index inside dev.
///
/// \param[in] dev           The spi controller device.
/// \param[in] mstr          The spi controller master selection index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_mstr(struct spi_ctrl_dev *const dev, const spi_ctrl_mstr_t mstr);

///
/// \brief Sets the spi data size index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ds            The spi controller data size index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_ds(struct spi_ctrl_dev *const dev, const spi_ctrl_ds_t ds);

///
/// \brief Sets the spi slave select output enable index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ssoe          The spi controller slave select output enable index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_ssoe(struct spi_ctrl_dev *const dev, const spi_ctrl_ssoe_t ssoe);

///
/// \brief Sets the spi frame format inside index device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] frf           The spi controller frame format index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_frf(struct spi_ctrl_dev *const dev, const spi_ctrl_frf_t frf);

///
/// \brief Sets the spi NSS pulse mangement index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] nssp          The spi controller NSS pulse management index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_nssp(struct spi_ctrl_dev *const dev, const spi_ctrl_nssp_t nssp);

///
/// \brief Sets the spi FIFO reception threshold index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] frxth         The spi controller FIFO reception threshold index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_frxth(struct spi_ctrl_t *const dev, const spi_ctrl_frxth_t frxth);

///
/// \brief Sets the spi last DMA transfer for transmission index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ldmatx        The spi controller last DMA transfer for transmission index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_ldmatx(struct spi_ctrl_dev *const dev, const spi_ctrl_ldmatx_t ldmatx);

///
/// \brief Sets the spi last DMA transfer for reception index inside device.
///
/// \param[in] dev           The spi controller device.
/// \param[in] ldmarx        The spi controller last DMA transfer for reception index.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
spi_ctrl_res_t spi_ctrl_set_ldmarx(struct spi_ctrl_dev *const dev, const spi_ctrl_ldmarx_t ldmarx);

#endif  /* _SPI_CTRL_H */
