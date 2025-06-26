#ifndef _SPI_CONTROLLER_H
#define _SPI_CONTROLLER_H

#include <stdint.h>

#define CRCPOLY_RESET_VALUE (0x0007)

///
/// \brief The spi controller instance type.
///
typedef struct spi_controller spi_controller_t;

///
/// \brief The spi controller result type.
///
typedef enum spi_controller_result
{
    SPI_CONTROLLER_RESULT_SUCCESS = 0,
    SPI_CONTROLLER_RESULT_ERROR,
} spi_controller_result_t;

///
/// \brief The spi controller clock phase type.
///
typedef enum spi_controller_cpha
{
    SPI_CONTROLLER_CPHA_BEGIN = 0,                  /*!< The clock phase begin indicator.                   */
    SPI_CONTROLLER_CPHA_0     = 0,                  /*!< Data is captured on the 1st clock edge after CS.   */
    SPI_CONTROLLER_CPHA_1,                          /*!< Data is captured on the 2nd clock edge after CS.   */
    SPI_CONTROLLER_CPHA_TOTAL,                      /*!< The clock phase total indicator.                   */
} spi_controller_cpha_t;

///
/// \brief The spi controller clock polarity type.
///
typedef enum spi_controller_cpol
{
    SPI_CONTROLLER_CPOL_BEGIN = 0,                  /*!< The clock polarity begin indicator.                */
    SPI_CONTROLLER_CPOL_0     = 0,                  /*!< The clock polarity to 0 when idle.                 */
    SPI_CONTROLLER_CPOL_1,                          /*!< The clock polarity to 1 when idle.                 */
    SPI_CONTROLLER_CPOL_TOTAL,                      /*!< The clock polarity total indicator.                */
} spi_controller_cpol_t;

///
/// \brief The spi controller bidirectional data mode type.
///
typedef enum spi_controller_bidimode
{
    SPI_CONTROLLER_BIDIMODE_BEGIN = 0,              /*!< The bidirectional data mode begin indicator.       */
    SPI_CONTROLLER_BIDIMODE_0     = 0,              /*!< 2-line unidirectional data mode selected.          */
    SPI_CONTROLLER_BIDIMODE_1,                      /*!< 1-line bidirectional data mode selected.           */
    SPI_CONTROLLER_BIDIMODE_TOTAL,                  /*!< The bidirectional data mode total indicator.       */
} spi_controller_bidimode_t;

///
/// \brief The spi controller output enable in bidirectional mode type.
///
typedef enum spi_controller_bidioe
{
    SPI_CONTROLLER_BIDIOE_BEGIN = 0,                /*!< The OE in bidirectional mode begin indicator.      */
    SPI_CONTROLLER_BIDIOE_0     = 0,                /*!< Output disabled (receive-only mode).               */
    SPI_CONTROLLER_BIDIOE_1,                        /*!< Output enabled (transmit-only mode).               */
    SPI_CONTROLLER_BIDIOE_TOTAL,                    /*!< The OE in bidirectional mode total indicator.      */
} spi_controller_bidioe_t;

///
/// \brief The spi controller receive only mode enable type.
///
typedef enum spi_controller_rxonly
{
    SPI_CONTROLLER_RXONLY_BEGIN = 0,                /*!< The receive only mode enable begin indicator.      */
    SPI_CONTROLLER_RXONLY_0     = 0,                /*!< Full-duplex (transmit and receive).                */
    SPI_CONTROLLER_RXONLY_1,                        /*!< Output disabled (receive-only mode).               */
    SPI_CONTROLLER_RXONLY_TOTAL,                    /*!< The receive only mode enable total indicator.      */
} spi_controller_rxonly_t;

///
/// \brief The spi controller frame format type.
///
typedef enum spi_controller_lsbfirst
{
    SPI_CONTROLLER_LSBFIRST_BEGIN = 0,              /*!< The frame format begin indicator.                  */
    SPI_CONTROLLER_LSBFIRST_0     = 0,              /*!< The data is transmitted/received with MSB first.   */
    SPI_CONTROLLER_LSBFIRST_1,                      /*!< The data is transmitted/received with LSB first.   */
    SPI_CONTROLLER_LSBFIRST_TOTAL,                  /*!< The frame format total indicator.                  */
} spi_controller_lsbfirst_t;

///
/// \brief The spi controller hardware CRC calculation type.
///
typedef enum spi_controller_crcen
{
    SPI_CONTROLLER_CRCEN_BEGIN = 0,                 /*!< The hardware CRC calc enable begin indicator.      */
    SPI_CONTROLLER_CRCEN_0     = 0,                 /*!< The hardware CRC calc disabled.                    */
    SPI_CONTROLLER_CRCEN_1,                         /*!< The hardware CRC calc enabled.                     */
    SPI_CONTROLLER_CRCEN_TOTAL,                     /*!< The hardware CRC calc enable total indicator.      */
} spi_controller_crcen_t;

///
/// \brief The spi controller CRC length type.
///
typedef enum spi_controller_crcl
{
    SPI_CONTROLLER_CRCL_BEGIN = 0,                  /*!< The hardware CRC length begin indicator.           */
    SPI_CONTROLLER_CRCL_0     = 0,                  /*!< The hardware CRC length set to 8-bits.             */
    SPI_CONTROLLER_CRCL_1,                          /*!< The hardware CRC length set to 16-bits.            */
    SPI_CONTROLLER_CRCL_TOTAL,                      /*!< The hardware CRC length total indicator.           */
} spi_controller_crcl_t;

///
/// \brief The spi controller software slave management type.
///
typedef enum spi_controller_ssm
{
    SPI_CONTROLLER_SSM_BEGIN = 0,                   /*!< The software slave management begin indicator.     */
    SPI_CONTROLLER_SSM_0     = 0,                   /*!< The software slave management disabled.            */
    SPI_CONTROLLER_SSM_1,                           /*!< The software slave management enabled.             */
    SPI_CONTROLLER_SSM_TOTAL,                       /*!< The software slave management total indicator.     */
} spi_controller_ssm_t;

///
/// \brief The spi controller internal slave select type.
///
typedef enum spi_controller_ssi
{
    SPI_CONTROLLER_SSI_BEGIN = 0,                   /*!< The internal slave select begin indicator.         */
    SPI_CONTROLLER_SSI_0     = 0,                   /*!< The internal slave select disabled.                */
    SPI_CONTROLLER_SSI_1,                           /*!< The internal slave select enabled.                 */
    SPI_CONTROLLER_SSI_TOTAL,                       /*!< The internal slave select total indicator.         */
} spi_controller_ssi_t;

///
/// \brief The spi controller master selection type.
///
typedef enum spi_controller_mstr
{
    SPI_CONTROLLER_MSTR_BEGIN = 0,                  /*!< The master selection begin indicator.              */
    SPI_CONTROLLER_MSTR_0     = 0,                  /*!< The slave configuration.                           */
    SPI_CONTROLLER_MSTR_1,                          /*!< The master configuration.                          */
    SPI_CONTROLLER_MSTR_TOTAL,                      /*!< The master selection total indicator.              */
} spi_controller_mstr_t;

///
/// \brief The spi controller internal slave select type.
///
typedef enum spi_controller_ds
{
    SPI_CONTROLLER_DS_BEGIN = 3,                    /*!< The data size begin indicator.                     */
    SPI_CONTROLLER_DS_4     = 3,                    /*!< The 4-bit data size.                               */
    SPI_CONTROLLER_DS_5,                            /*!< The 5-bit data size.                               */
    SPI_CONTROLLER_DS_6,                            /*!< The 6-bit data size.                               */
    SPI_CONTROLLER_DS_7,                            /*!< The 7-bit data size.                               */
    SPI_CONTROLLER_DS_8,                            /*!< The 8-bit data size.                               */
    SPI_CONTROLLER_DS_9,                            /*!< The 9-bit data size.                               */
    SPI_CONTROLLER_DS_10,                           /*!< The 10-bit data size.                              */
    SPI_CONTROLLER_DS_11,                           /*!< The 11-bit data size.                              */
    SPI_CONTROLLER_DS_12,                           /*!< The 12-bit data size.                              */
    SPI_CONTROLLER_DS_13,                           /*!< The 13-bit data size.                              */
    SPI_CONTROLLER_DS_14,                           /*!< The 14-bit data size.                              */
    SPI_CONTROLLER_DS_15,                           /*!< The 15-bit data size.                              */
    SPI_CONTROLLER_DS_16,                           /*!< The 16-bit data size.                              */
    SPI_CONTROLLER_DS_TOTAL,                        /*!< The data size total indicator.                     */
} spi_controller_ds_t;

///
/// \brief The spi controller slave select output enable type.
///
typedef enum spi_controller_ssoe
{
    SPI_CONTROLLER_SSOE_BEGIN = 0,                  /*!< The slave select output enable begin indicator.    */
    SPI_CONTROLLER_SSOE_0     = 0,                  /*!< The slave select is disabled in master mode.       */
    SPI_CONTROLLER_SSOE_1,                          /*!< The slave select is enabled in master mode.        */
    SPI_CONTROLLER_SSOE_TOTAL,                      /*!< The slave select output enable total indicator.    */
} spi_controller_ssoe_t;

///
/// \brief The spi controller frame format type.
///
/// \note  Set the FRF bit if the TI protocol is required (keep NSSP bit cleared in TI mode).
///
typedef enum spi_controller_frf
{
    SPI_CONTROLLER_FRF_BEGIN = 0,                   /*!< The frame format begin indicator.                  */
    SPI_CONTROLLER_FRF_0     = 0,                   /*!< The frame format set to motorola.                  */
    SPI_CONTROLLER_FRF_1,                           /*!< The frame format set to TI.                        */
    SPI_CONTROLLER_FRF_TOTAL,                       /*!< The frame format total indicator.                  */
} spi_controller_frf_t;

///
/// \brief The spi controller NSS pulse management type.
///
/// \note  This bit must be written only when the SPI is disabled (SPE=0).
///        This bit is not used in I2S mode and SPI TI mode.
///
typedef enum spi_controller_nssp
{
    SPI_CONTROLLER_NSSP_BEGIN = 0,                  /*!< The NSS pulse management begin indicator.          */
    SPI_CONTROLLER_NSSP_0     = 0,                  /*!< The NSS pulse management is disabled.              */
    SPI_CONTROLLER_NSSP_1,                          /*!< The NSS pulse management is enabled.               */
    SPI_CONTROLLER_NSSP_TOTAL,                      /*!< The NSS pulse management total indicator.          */
} spi_controller_nssp_t;

///
/// \brief The spi controller FIFO reception threshold type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum spi_controller_frxth
{
    SPI_CONTROLLER_FRXTH_BEGIN = 0,                 /*!< The FIFO reception threshold begin indicator.      */
    SPI_CONTROLLER_FRXTH_0     = 0,                 /*!< When the FIFO level >= 1/2, generate RXNE event.   */
    SPI_CONTROLLER_FRXTH_1,                         /*!< When the FIFO level >= 1/4, generate RXNE event.   */
    SPI_CONTROLLER_FRXTH_TOTAL,                     /*!< The FIFO reception threshold total indicator.      */
} spi_controller_frxth_t;

///
/// \brief The spi controller last DMA transfer for transmission type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum spi_controller_ldmatx
{
    SPI_CONTROLLER_LDMATX_BEGIN = 0,                /*!< LDMA transfer for transmission begin indicator.    */
    SPI_CONTROLLER_LDMATX_0     = 0,                /*!< Number of data to transfer is even.                */
    SPI_CONTROLLER_LDMATX_1,                        /*!< Number of data to transfer is odd.                 */
    SPI_CONTROLLER_LDMATX_TOTAL,                    /*!< LDMA transfer for transmission total indicator.    */
} spi_controller_ldmatx_t;

///
/// \brief The spi controller last DMA transfer for reception type.
///
/// \note  This bit is not used in I2S mode.
///
typedef enum spi_controller_ldmarx
{
    SPI_CONTROLLER_LDMARX_BEGIN = 0,                /*!< LDMA transfer for reception begin indicator.       */
    SPI_CONTROLLER_LDMARX_0     = 0,                /*!< Number of data to transfer is even.                */
    SPI_CONTROLLER_LDMARX_1,                        /*!< Number of data to transfer is odd.                 */
    SPI_CONTROLLER_LDMARX_TOTAL,                    /*!< LDMA transfer for reception total indicator.       */
} spi_controller_ldmarx_t;

///
/// \brief Initializes the spi controller.
///
/// \param[in] instance                   The spi controller instance.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_init(spi_controller_t *const instance);

///
/// \brief Deinitializes the spi controller.
///
/// \param[in] instance                   The spi controller instance.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_deinit(spi_controller_t *const instance);

///
/// \brief Gets the spi instance.
///
/// \param[out] instance                  The pointer to the spi controller instance.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_get_instance(const spi_controller_t **instance);

///
/// \brief Receives the specified number of bytes over spi.
///
/// \param[in]  instance                  The pointer to the spi controller instance.
/// \param[out] data                      The pointer to the data buffer.
/// \param[in]  size                      The number of bytes to receive.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_receive(const spi_controller_t *const instance, uint8_t *const data,
                                               const uint32_t size);

///
/// \brief Transmits the specified number of bytes over spi.
///
/// \param[in] instance                   The pointer to the spi controller instance.
/// \param[in] data                       The pointer to the data buffer.
/// \param[in] size                       The number of bytes to transmit.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_receive(const spi_controller_t *const instance,
                                               const uint8_t *const data, const uint32_t size);

///
/// \brief Sets the spi CRC polynomial value inside instance.
///
/// \note  Default reset value is `0x0007`.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] crcpoly                    The spi controller CRC polynomial value.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_crcpr(spi_controller_t *const instance, const uint16_t crcpoly);

///
/// \brief Sets the spi clock phase index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] cpha                       The spi controller clock phase index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_cpha(spi_controller_t *const instance, const spi_controller_cpha_t cpha);

///
/// \brief Sets the spi clock polarity index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] cpol                       The spi controller clock polarity index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_cpol(spi_controller_t *const instance, const spi_controller_cpol_t cpol);

///
/// \brief Sets the spi bidirectional data mode index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] bidimode                   The spi controller bidirectional data mode index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_bidimode(spi_controller_t *const instance,
                                                    const spi_controller_bidimode_t bidimode);

///
/// \brief Sets the spi output enable in bidirectional mode index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] bidioe                     The spi controller output enable in bidirectional mode index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_bidioe(spi_controller_t *const instance, const spi_controller_bidioe_t bidioe);

///
/// \brief Sets the spi receive only mode enable index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] rxonly                     The spi controller receive only mode enable index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_rxonly(spi_controller_t *const instance, const spi_controller_rxonly_t rxonly);

///
/// \brief Sets the spi frame format index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] lsbfirst                   The spi controller frame format index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_lsbfirst(spi_controller_t *const instance, const spi_controller_lsbfirst_t lsbfirst);

///
/// \brief Sets the spi hardware CRC calculation index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] crcen                      The spi controller hardware CRC calculation index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_crcen(spi_controller_t *const instance, const spi_controller_crcen_t crcen);

///
/// \brief Sets the spi CRC length index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] crcl                       The spi controller CRC length index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_crcl(spi_controller_t *const instance, const spi_controller_crcl_t crcl);

///
/// \brief Sets the spi software slave management index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] ssm                        The spi controller software slave management index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_ssm(spi_controller_t *const instance, const spi_controller_ssm_t ssm);

///
/// \brief Sets the spi internal slave select index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] ssi                        The spi controller internal slave select index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_ssi(spi_controller_t *const instance, const spi_controller_ssi_t ssi);

///
/// \brief Sets the spi master selection index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] mstr                       The spi controller master selection index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_mstr(spi_controller_t *const instance, const spi_controller_mstr_t mstr);

///
/// \brief Sets the spi data size index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] ds                         The spi controller data size index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_ds(spi_controller_t *const instance, const spi_controller_ds_t ds);

///
/// \brief Sets the spi slave select output enable index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] ssoe                       The spi controller slave select output enable index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_ssoe(spi_controller_t *const instance, const spi_controller_ssoe_t ssoe);

///
/// \brief Sets the spi frame format inside index instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] frf                        The spi controller frame format index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_frf(spi_controller_t *const instance, const spi_controller_frf_t frf);

///
/// \brief Sets the spi NSS pulse mangement index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] nssp                       The spi controller NSS pulse management index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_nssp(spi_controller_t *const instance, const spi_controller_nssp_t nssp);

///
/// \brief Sets the spi FIFO reception threshold index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] frxth                      The spi controller FIFO reception threshold index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_frxth(spi_controller_t *const instance, const spi_controller_frxth_t frxth);

///
/// \brief Sets the spi last DMA transfer for transmission index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] ldmatx                     The spi controller last DMA transfer for transmission index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_ldmatx(spi_controller_t *const instance, const spi_controller_ldmatx_t ldmatx);

///
/// \brief Sets the spi last DMA transfer for reception index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] ldmarx                     The spi controller last DMA transfer for reception index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_ldmarx(spi_controller_t *const instance, const spi_controller_ldmarx_t ldmarx);

#endif  /* _SPI_CONTROLLER_H */
