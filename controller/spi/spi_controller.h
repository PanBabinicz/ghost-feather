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
    SPI_CONTROLLER_CLOCK_PHASE_BEGIN = 0,
    SPI_CONTROLLER_CLOCK_PHASE_0     = 0,
    SPI_CONTROLLER_CLOCK_PHASE_1,
    SPI_CONTROLLER_CLOCK_PHASE_TOTAL,
} spi_controller_clock_phase_t;

///
/// \brief The spi controller clock polarity type.
///
typedef enum spi_controller_clock_polarity
{
    SPI_CONTROLLER_CLOCK_POLARITY_BEGIN = 0,
    SPI_CONTROLLER_CLOCK_POLARITY_0     = 0,
    SPI_CONTROLLER_CLOCK_POLARITY_1,
    SPI_CONTROLLER_CLOCK_POLARITY_TOTAL,
} spi_controller_clock_polarity_t;

///
/// \brief Initializes the spi controller.
///
/// \param[in] spi_controller             The spi controller instance.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_init(spi_controller_t *const spi_controller);

///
/// \brief Deinitializes the spi controller.
///
/// \param[in] spi_controller             The spi controller instance.
///
/// \return spi_controller_result_t       The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS Otherwise.
///
spi_controller_result_t spi_controller_deinit(spi_controller_t *const spi_controller);

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
/// \param[in] spi_controller_clock_phase The spi controller instance.
/// \param[in] spi_controller_clock_phase The spi controller clock phase index.
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
/// \param[in] instance                      The spi controller instance.
/// \param[in] spi_controller_clock_polarity The spi controller clock polarity index.
///
/// \return spi_controller_result_t          The spi controller result.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS    On success.
/// \retval SPI_CONTROLLER_RESULT_SUCCESS    Otherwise.
///
spi_controller_result_t spi_controller_set_clock_polarity(spi_controller_t *const instance,
                                                          const spi_controller_clock_polarity_t clock_polarity);

#endif  /* _SPI_CONTROLLER_H */
