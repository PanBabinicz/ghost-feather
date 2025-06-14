#ifndef _SPI_CONTROLLER_H
#define _SPI_CONTROLLER_H

#include <stdint.h>

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
typedef enum spi_controller_clock_phase
{
    SPI_CONTROLLER_CLOCK_PHASE_BEGIN = 0,           /*!< The clock phase begin indicator.                   */
    SPI_CONTROLLER_CLOCK_PHASE_0     = 0,           /*!< Data is captured on the 1st clock edge after CS.   */
    SPI_CONTROLLER_CLOCK_PHASE_1,                   /*!< Data is captured on the 2nd clock edge after CS.   */
    SPI_CONTROLLER_CLOCK_PHASE_TOTAL,               /*!< The clock phase total indicator.                   */
} spi_controller_clock_phase_t;

///
/// \brief The spi controller clock polarity type.
///
typedef enum spi_controller_clock_polarity
{
    SPI_CONTROLLER_CLOCK_POLARITY_BEGIN = 0,        /*!< The clock polarity begin indicator.                */
    SPI_CONTROLLER_CLOCK_POLARITY_0     = 0,        /*!< The clock polarity to 0 when idle.                 */
    SPI_CONTROLLER_CLOCK_POLARITY_1,                /*!< The clock polarity to 1 when idle.                 */
    SPI_CONTROLLER_CLOCK_POLARITY_TOTAL,            /*!< The clock polarity total indicator.                */
} spi_controller_clock_polarity_t;

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
    SPI_CONTROLLER_BIDIOE_BEGIN = 0,              /*!< The OE in bidirectional mode begin indicator.        */
    SPI_CONTROLLER_BIDIOE_0     = 0,              /*!< Output disabled (receive-only mode).                 */
    SPI_CONTROLLER_BIDIOE_1,                      /*!< Output enabled (transmit-only mode).                 */
    SPI_CONTROLLER_BIDIOE_TOTAL,                  /*!< The OE in bidirectional mode total indicator.        */
} spi_controller_bidioe_t;

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
/// \param[out] instance                  The pointer to spi controller instance.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_get_instance(const spi_controller_t **instance);

///
/// \brief Sets the spi clock phase index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] clock_phase                The spi controller clock phase index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_clock_phase(spi_controller_t *const instance,
                                                       const spi_controller_clock_phase_t clock_phase);

///
/// \brief Sets the spi clock polarity index inside instance.
///
/// \param[in] instance                   The spi controller instance.
/// \param[in] clock_polarity             The spi controller clock polarity index.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_set_clock_polarity(spi_controller_t *const instance,
                                                          const spi_controller_clock_polarity_t clock_polarity);

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

#endif  /* _SPI_CONTROLLER_H */
