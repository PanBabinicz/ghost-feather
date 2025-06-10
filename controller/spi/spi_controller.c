#include "spi_controller.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The spi controller instance type.
///
typedef struct spi_controller
{
    bool is_init;                                   /*!< The is initialized flag.                           */
} spi_controller_t;

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
static spi_controller_t spi_controller;

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
spi_controller_result_t spi_controller_init(spi_controller_t *const spi_controller)
{
    if (spi_controller == NULL)
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    spi_controller->is_init = true;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_deinit(spi_controller_t *const spi_controller)
{
    if (spi_controller == NULL)
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    spi_controller->is_init = false;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}
