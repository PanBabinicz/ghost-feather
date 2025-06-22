#include "spi_controller.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The spi CR1 config type.
///
typedef struct cr1_conf
{
    uint8_t  cpha     : 1;                          /*!< The clock phase index.                             */
    uint8_t  cpol     : 1;                          /*!< The clock polarity index.                          */
    uint8_t  bidimode : 1;                          /*!< The bidirectional data mode index.                 */
    uint8_t  bidioe   : 1;                          /*!< The output enable in bidirectional mode index.     */
    uint8_t  lsbfirst : 1;                          /*!< The frame format index.                            */
    uint8_t  crcen    : 1;                          /*!< The hardware CRC calculation index.                */
    uint8_t  crcl     : 1;                          /*!< The CRC length index.                              */
    uint8_t  ssm      : 1;                          /*!< The software slave management index.               */
    uint8_t  ssi      : 1;                          /*!< The internal slave select index.                   */
    uint8_t  mstr     : 1;                          /*!< The master selection index.                        */
} cr1_conf_t;

///
/// \brief The spi CR2 config type.
///
typedef struct cr2_conf
{
    uint8_t  ds       : 4;                          /*!< The data size index.                               */
    uint8_t  ssoe     : 1;                          /*!< The slave select output enable index.              */
    uint8_t  frf      : 1;                          /*!< The frame format index.                            */
    uint8_t  nssp     : 1;                          /*!< The NSS pulse management index.                    */
    uint8_t  frxth    : 1;                          /*!< The FIFO reception threshold index.                */
    uint8_t  ldmatx   : 1;                          /*!< The last DMA transfer for transmission index.      */
    uint8_t  ldmarx   : 1;                          /*!< The last DMA transfer for reception index.         */
} cr2_conf_t;

///
/// \brief The spi controller instance type.
///
typedef struct spi_controller
{
    uint32_t   interface;                           /*!< The spi peripheral interface.                      */
    cr1_conf_t cr1;                                 /*!< The spi CR1 config.                                */
    cr2_conf_t cr2;                                 /*!< The spi CR2 config.                                */
    bool       is_init;                             /*!< The is initialized flag.                           */
} spi_controller_t;

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The spi controller instance.
///
static spi_controller_t spi_controller_instance =
{
    .interface = SPI1,
    .cr1 =
    {
        .cpha     = SPI_CONTROLLER_CLOCK_PHASE_0,
        .cpol     = SPI_CONTROLLER_CLOCK_POLARITY_1,
        .bidimode = SPI_CONTROLLER_BIDIMODE_0,
        .bidioe   = SPI_CONTROLLER_BIDIOE_0,
        .lsbfirst = SPI_CONTROLLER_LSBFIRST_0,
        .crcen    = SPI_CONTROLLER_CRCEN_0,
        .ssm      = SPI_CONTROLLER_SSM_0,
        .ssi      = SPI_CONTROLLER_SSI_0,
        .mstr     = SPI_CONTROLLER_MSTR_1,
    },
    .cr2 =
    {
        .ds       = SPI_CONTROLLER_DS_8,
        .ssoe     = SPI_CONTROLLER_SSOE_1,
        .frf      = SPI_CONTROLLER_FRF_0,
        .nssp     = SPI_CONTROLLER_NSSP_0,
        .frxth    = SPI_CONTROLLER_FRXTH_0,
        .ldmatx   = SPI_CONTROLLER_LDMATX_0,
        .ldmarx   = SPI_CONTROLLER_LDMARX_0,
    },
    .is_init = false,
};

///
/// \brief Contains function pointers that allow the clock phase to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_cpha_array[SPI_CONTROLLER_CLOCK_PHASE_TOTAL])(uint32_t interface) =
{
    spi_set_clock_phase_0,
    spi_set_clock_phase_1,
};

///
/// \brief Contains function pointers that allow the clock polarity to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_cpol_array[SPI_CONTROLLER_CLOCK_POLARITY_TOTAL])(uint32_t interface) =
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

///
/// \brief Contains function pointers that allow the internal slave select to be set using the
///        libopencm3 functions.
///
static void (*const spi_controller_set_ssi_array[SPI_CONTROLLER_SSI_TOTAL])(uint32_t interface) =
{
    spi_set_nss_low,
    spi_set_nss_high,
};

///
/// \brief Contains function pointers that allow the master selection to be set using the
///        libopencm3 functions.
///
static void (*const spi_controller_set_mstr_array[SPI_CONTROLLER_MSTR_TOTAL])(uint32_t interface) =
{
    spi_set_slave_mode,
    spi_set_master_mode,
};

///
/// \brief Contains function pointers that allow the slave select output enable to be set using the
///        libopencm3 functions.
///
static void (*const spi_controller_set_ssoe_array[SPI_CONTROLLER_SSOE_TOTAL])(uint32_t interface) =
{
    spi_disable_ss_output,
    spi_enable_ss_output,
};

///
/// \brief Contains function pointers that allow the frame format to be set using the libopencm3 functions.
///
static void (*const spi_controller_set_frf_array[SPI_CONTROLLER_FRF_TOTAL])(uint32_t interface) =
{
    spi_set_frf_motorola,
    spi_set_frf_ti,
};

///
/// \brief Contains function pointers that allow the NSS pulse management to be set using the
///        libopencm3 functions.
static void (*const spi_controller_set_nssp_array[SPI_CONTROLLER_NSSP_TOTAL])(uint32_t interface) =
{
    spi_disable_nssp,
    spi_enable_nssp,
};

///
/// \brief Contains function pointers that allow the FIFO reception threshold to be set using the
///        libopencm3 functions.
static void (*const spi_controller_set_frxth_array[SPI_CONTROLLER_FRXTH_TOTAL])(uint32_t interface) =
{
    spi_fifo_reception_threshold_16bit,
    spi_fifo_reception_threshold_8bit,
};

///
/// \brief Contains function pointers that allow the last DMA transfer for transmission to be set using the
///        libopencm3 functions.
static void (*const spi_controller_set_ldmatx_array[SPI_CONTROLLER_LDMATX_TOTAL])(uint32_t interface) =
{
    spi_set_ldmatx_even,
    spi_set_ldmatx_odd,
};

///
/// \brief Contains function pointers that allow the last DMA transfer for reception to be set using the
///        libopencm3 functions.
static void (*const spi_controller_set_ldmarx_array[SPI_CONTROLLER_LDMARX_TOTAL])(uint32_t interface) =
{
    spi_set_ldmarx_even,
    spi_set_ldmarx_odd,
};

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief Validates the CR1 config values.
///
static spi_controller_result_t spi_controller_validate_cr1(const spi_controller_t *const instance);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static spi_controller_result_t spi_controller_validate_cr1(const spi_controller_t *const instance)
{
    /* Whether the instance is NULL was checked before. */

    /* CPHA must be cleared in NSSP mode.*/
    if ((instance->cr2.nssp == SPI_CONTROLLER_NSSP_1) && (instance->cr1.cpha == SPI_CONTROLLER_CPHA_1))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

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

    /* The CR1 configuration. */
    spi_controller_set_cpha_array[instance->cr1.cpha](instance->interface);
    spi_controller_set_cpol_array[instance->cr1.cpol](instance->interface);
    spi_controller_set_bidimode_array[instance->cr1.bidimode](instance->interface);
    spi_controller_set_bidioe_array[instance->cr1.bidioe](instance->interface);
    spi_controller_set_lsbfirst_array[instance->cr1.lsbfirst](instance->interface);
    spi_controller_set_crcen_array[instance->cr1.crcen](instance->interface);
    spi_controller_set_crcl_array[instance->cr1.crcl](instance->interface);
    spi_controller_set_ssm_array[instance->cr1.ssm](instance->interface);
    spi_controller_set_ssi_array[instance->cr1.ssi](instance->interface);
    spi_controller_set_mstr_array[instance->cr1.mstr](instance->interface);

    /* The CR2 configuration. */
    spi_set_data_size(instance->interface, (uint16_t)instance->cr2.ds);
    spi_controller_set_ssoe_array[instance->cr2.ssoe](instance->interface);
    spi_controller_set_frf_array[instance->cr2.frf](instance->interface);
    spi_controller_set_nssp_array[instance->cr2.nssp](instance->interface);
    spi_controller_set_frxth_array[instance->cr2.frxth](instance->interface);
    spi_controller_set_ldmatx_array[instance->cr2.ldmatx](instance->interface);
    spi_controller_set_ldmarx_array[instance->cr2.ldmatx](instance->interface);

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

    spi_disable(instance->interface);
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

spi_controller_result_t spi_controller_set_cpha(spi_controller_t *const instance, const spi_controller_cpha_t cpha)
{
    if ((cpha < SPI_CONTROLLER_CPHA_BEGIN) || (cpha >= SPI_CONTROLLER_CPHA_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.cpha = cpha;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_cpol(spi_controller_t *const instance, const spi_controller_cpol_t cpol)
{
    if ((cpol < SPI_CONTROLLER_CPOL_BEGIN) || (cpol >= SPI_CONTROLLER_CPOL_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.cpol = cpol;

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

    instance->cr1.bidimode = bidimode;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_bidioe(spi_controller_t *const instance, const spi_controller_bidioe_t bidioe)
{
    if ((bidioe < SPI_CONTROLLER_BIDIOE_BEGIN) || (bidioe >= SPI_CONTROLLER_BIDIOE_TOTAL) ||
        (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.bidioe = bidioe;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_lsbfirst(spi_controller_t *const instance, const spi_controller_lsbfirst_t lsbfirst)
{
    if ((lsbfirst < SPI_CONTROLLER_LSBFIRST_BEGIN) || (lsbfirst >= SPI_CONTROLLER_LSBFIRST_TOTAL) ||
        (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.lsbfirst = lsbfirst;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_crcen(spi_controller_t *const instance, const spi_controller_crcen_t crcen)
{
    if ((crcen < SPI_CONTROLLER_CRCEN_BEGIN) || (crcen >= SPI_CONTROLLER_CRCEN_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.crcen = crcen;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_crcl(spi_controller_t *const instance, const spi_controller_crcl_t crcl)
{
    if ((crcl < SPI_CONTROLLER_CRCL_BEGIN) || (crcl >= SPI_CONTROLLER_CRCL_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.crcl = crcl;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_ssm(spi_controller_t *const instance, const spi_controller_ssm_t ssm)
{
    if ((ssm < SPI_CONTROLLER_SSM_BEGIN) || (ssm >= SPI_CONTROLLER_SSM_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.ssm = ssm;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_ssi(spi_controller_t *const instance, const spi_controller_ssi_t ssi)
{
    if ((ssi < SPI_CONTROLLER_SSI_BEGIN) || (ssi >= SPI_CONTROLLER_SSI_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.ssi = ssi;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_mstr(spi_controller_t *const instance, const spi_controller_mstr_t mstr)
{
    if ((mstr < SPI_CONTROLLER_MSTR_BEGIN) || (mstr >= SPI_CONTROLLER_MSTR_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr1.mstr = mstr;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_ds(spi_controller_t *const instance, const spi_controller_ds_t ds)
{
    if ((ds < SPI_CONTROLLER_DS_BEGIN) || (ds >= SPI_CONTROLLER_DS_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr2.ds = ds;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_ssoe(spi_controller_t *const instance, const spi_controller_ssoe_t ssoe)
{
    if ((ssoe < SPI_CONTROLLER_SSOE_BEGIN) || (ssoe >= SPI_CONTROLLER_SSOE_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr2.ssoe = ssoe;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_frf(spi_controller_t *const instance, const spi_controller_frf_t frf)
{
    if ((frf < SPI_CONTROLLER_FRF_BEGIN) || (frf >= SPI_CONTROLLER_FRF_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr2.frf = frf;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_nssp(spi_controller_t *const instance, const spi_controller_nssp_t nssp)
{
    if ((nssp < SPI_CONTROLLER_NSSP_BEGIN) || (nssp >= SPI_CONTROLLER_NSSP_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr2.nssp = nssp;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_frxth(spi_controller_t *const instance, const spi_controller_frxth_t frxth)
{
    if ((frxth < SPI_CONTROLLER_FRXTH_BEGIN) || (frxth >= SPI_CONTROLLER_FRXTH_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr2.frxth = frxth;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_ldmatx(spi_controller_t *const instance, const spi_controller_ldmatx_t ldmatx)
{
    if ((ldmatx < SPI_CONTROLLER_LDMATX_BEGIN) || (ldmatx >= SPI_CONTROLLER_LDMATX_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr2.ldmatx = ldmatx;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}

spi_controller_result_t spi_controller_set_ldmarx(spi_controller_t *const instance, const spi_controller_ldmarx_t ldmarx)
{
    if ((ldmarx < SPI_CONTROLLER_LDMARX_BEGIN) || (ldmarx >= SPI_CONTROLLER_LDMARX_TOTAL) || (instance == NULL))
    {
        return SPI_CONTROLLER_RESULT_ERROR;
    }

    instance->cr2.ldmarx = ldmarx;

    return SPI_CONTROLLER_RESULT_SUCCESS;
}
