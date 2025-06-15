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
    uint32_t interface;                             /*!< The spi peripheral interface.                      */
    uint8_t  clock_phase    : 1;                    /*!< The clock phase index.                             */
    uint8_t  clock_polarity : 1;                    /*!< The clock polarity index.                          */
    uint8_t  bidimode       : 1;                    /*!< The bidirectional data mode index.                 */
    uint8_t  bidioe         : 1;                    /*!< The output enable in bidirectional mode index.     */  
    uint8_t  lsbfirst       : 1;                    /*!< The frame format index.                            */
    uint8_t  crcen          : 1;                    /*!< The hardware CRC calculation index.                */
    uint8_t  crcl           : 1;                    /*!< The CRC length index.                              */
    uint8_t  ssm            : 1;                    /*!< The software slave management index.               */
    bool     is_init;                               /*!< The is initialized flag.                           */
} spi_controller_t;

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The spi controller instance.
///
static spi_controller_t spi_controller_instance =
{
    .interface      = SPI1,
    .clock_phase    = SPI_CONTROLLER_CLOCK_PHASE_0,
    .clock_polarity = SPI_CONTROLLER_CLOCK_POLARITY_1,
    .bidimode       = SPI_CONTROLLER_BIDIMODE_0,
    .bidioe         = SPI_CONTROLLER_BIDIOE_0,
    .lsbfirst       = SPI_CONTROLLER_LSBFIRST_0,
    .crcen          = SPI_CONTROLLER_CRCEN_0,
    .ssm            = SPI_CONTROLLER_SSM_0,
    .is_init        = false,
};

///
/// \brief Contains function pointers that allow the clock phase to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_clock_phase_array[SPI_CONTROLLER_CLOCK_PHASE_TOTAL])(uint32_t interface) =
{
    spi_set_clock_phase_0,
    spi_set_clock_phase_1,
};

///
/// \brief Contains function pointers that allow the clock polarity to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_clock_polarity_array[SPI_CONTROLLER_CLOCK_POLARITY_TOTAL])(uint32_t interface) =
{
    spi_set_clock_polarity_0,
    spi_set_clock_polarity_1,
};

///
/// \brief Contains function pointers that allow the bidirectional data mode to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_bidimode_array[SPI_CONTROLLER_BIDIMODE_TOTAL])(uint32_t interface) =
{
    spi_set_unidirectional_mode,
    spi_set_bidirectional_mode,
};

///
/// \brief Contains function pointers that allow the output enable in bidirectional mode to be set
///        using the libopencm3 functions.
///
static void (*const spi_controller_set_bidioe_array[SPI_CONTROLLER_BIDIOE_TOTAL])(uint32_t interface) =
{
    spi_set_bidirectional_receive_only_mode,
    spi_set_bidirectional_transmit_only_mode,
};

///
/// \brief Contains function pointers that allow the frame format to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_lsbfirst_array[SPI_CONTROLLER_LSBFIRST_TOTAL])(uint32_t interface) =
{
    spi_send_msb_first,
    spi_send_lsb_first,
};

///
/// \brief Contains function pointers that allow the hardware CRC calculation to be set using the libopencm3
///        functions.
///
static void (*const spi_controller_set_crcen_array[SPI_CONTROLLER_CRCEN_TOTAL])(uint32_t interface) =
{
    spi_disable_crc,
    spi_enable_crc,
};

///
/// \brief Contains function pointers that allow the CRC length to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_crcl_array[SPI_CONTROLLER_CRCL_TOTAL])(uint32_t interface) =
{
    spi_set_crcl_8bit,
    spi_set_crcl_16bit,
};

///
/// \brief Contains function pointers that allow the software slave management to be set using the
///        libopencm3 functions.
///
static void (*const spi_controller_set_ssm_array[SPI_CONTROLLER_SSM_TOTAL])(uint32_t interface) =
{
    spi_set_crcl_8bit,
    spi_set_crcl_16bit,
};

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
spi_controller_result_t spi_controller_init(spi_controller_t *const instance)
{
    if (instance == NULL)
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    spi_disable(instance->interface);
    spi_controller_set_clock_phase_array[instance->clock_phase](instance->interface);
    spi_controller_set_clock_polarity_array[instance->clock_polarity](instance->interface);
    spi_controller_set_bidimode_array[instance->bidimode](instance->interface);
    spi_controller_set_bidioe_array[instance->bidioe](instance->interface);
    spi_controller_set_lsbfirst_array[instance->lsbfirst](instance->interface);
    spi_controller_set_crcen_array[instance->crcen](instance->interface);
    spi_controller_set_crcl_array[instance->crcl](instance->interface);
    spi_controller_set_ssm_array[instance->ssm](instance->interface);
    spi_enable(instance->interface);

    instance->is_init = true;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_deinit(spi_controller_t *const instance)
{
    if (instance == NULL)
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    spi_disable(instance->spi);
    instance->is_init = false;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_get_instance(const spi_controller_t **instance)
{
    if (instance == NULL)
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    *instance = &spi_controller_instance;
    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_clock_phase(spi_controller_t *const instance,
                                                       const spi_controller_clock_phase_t clock_phase)
{
    if ((clock_phase < SPI_CONTROLLER_CLOCK_PHASE_BEGIN) || (clock_phase >= SPI_CONTROLLER_CLOCK_PHASE_TOTAL) ||
        (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->clock_phase = clock_phase;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_clock_polarity(spi_controller_t *const instance,
                                                          const spi_controller_clock_polarity_t clock_polarity)
{
    if ((clock_polarity < SPI_CONTROLLER_CLOCK_POLARITY_BEGIN) || (clock_polarity >= SPI_CONTROLLER_CLOCK_POLARITY_TOTAL) ||
        (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->clock_polarity = clock_polarity;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_bidimode(spi_controller_t *const instance,
                                                    const spi_controller_bidimode_t bidimode)
{
    if ((bidimode < SPI_CONTROLLER_BIDIMODE_BEGIN) || (bidimode >= SPI_CONTROLLER_BIDIMODE_TOTAL) ||
        (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->bidimode = bidimode;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_bidioe(spi_controller_t *const instance, const spi_controller_bidioe_t bidioe)
{
    if ((bidioe < SPI_CONTROLLER_BIDIOE_BEGIN) || (bidioe >= SPI_CONTROLLER_BIDIOE_TOTAL) ||
        (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->bidioe = bidioe;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_lsbfirst(spi_controller_t *const instance, const spi_controller_lsbfirst_t lsbfirst)
{
    if ((lsbfirst < SPI_CONTROLLER_LSBFIRST_BEGIN) || (lsbfirst >= SPI_CONTROLLER_LSBFIRST_TOTAL) ||
        (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->lsbfirst = lsbfirst;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_crcen(spi_controller_t *const instance, const spi_controller_crcen_t crcen)
{
    if ((crcen < SPI_CONTROLLER_CRCEN_BEGIN) || (crcen >= SPI_CONTROLLER_CRCEN_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->crcen = crcen;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_crcl(spi_controller_t *const instance, const spi_controller_crcl_t crcl)
{
    if ((crcl < SPI_CONTROLLER_CRCL_BEGIN) || (crcl >= SPI_CONTROLLER_CRCL_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->crcl = crcl;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_ssm(spi_controller_t *const instance, const spi_controller_ssm_t ssm)
{
    if ((ssm < SPI_CONTROLLER_SSM_BEGIN) || (ssm >= SPI_CONTROLLER_SSM_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->ssm = ssm;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}
