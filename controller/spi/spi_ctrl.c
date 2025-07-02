#include "spi_ctrl.h"
#include "libopencm3/stm32/spi.h"
#include "libopencm3/stm32/gpio.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The spi CRCPR config type.
///
typedef struct crcpr_conf
{
    uint16_t crcpoly;                               /*!< The CRC polynomial value.                          */
    bool     set;                                   /*!< The set CRC polynomial flag.                       */
} crcpr_conf_t;

///
/// \brief The spi CR1 config type.
///
typedef struct cr1_conf
{
    uint8_t  cpha     : 1;                          /*!< The clock phase index.                             */
    uint8_t  cpol     : 1;                          /*!< The clock polarity index.                          */
    uint8_t  bidimode : 1;                          /*!< The bidirectional data mode index.                 */
    uint8_t  bidioe   : 1;                          /*!< The output enable in bidirectional mode index.     */
    uint8_t  rxonly   : 1;                          /*!< The receive only mode enable index.                */
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
typedef struct spi_ctrl
{
    uint32_t     intf;                              /*!< The spi peripheral interface.                      */
    cr1_conf_t   cr1;                               /*!< The spi CR1 config.                                */
    cr2_conf_t   cr2;                               /*!< The spi CR2 config.                                */
    crcpr_conf_t crcpr;                             /*!< The spi CRCPR config.                              */
    bool         init;                              /*!< The is initialized flag.                           */
} spi_ctrl_t;

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The spi controller instance.
///
static spi_ctrl_t spi_ctrl_inst =
{
    .intf  = SPI1,
    .crcpr =
    {
        .crcpr    = CRCPOLY_RES_VAL,
        .set      = false,
    },
    .cr1 =
    {
        .cpha     = SPI_CTRL_CPHA_0,
        .cpol     = SPI_CTRL_CPOL_1,
        .bidimode = SPI_CTRL_BIDIMODE_0,
        .bidioe   = SPI_CTRL_BIDIOE_0,
        .rxonly   = SPI_CTRL_RXONLY_0,
        .lsbfirst = SPI_CTRL_LSBFIRST_0,
        .crcen    = SPI_CTRL_CRCEN_0,
        .ssm      = SPI_CTRL_SSM_0,
        .ssi      = SPI_CTRL_SSI_0,
        .mstr     = SPI_CTRL_MSTR_1,
    },
    .cr2 =
    {
        .ds       = SPI_CTRL_DS_8,
        .ssoe     = SPI_CTRL_SSOE_1,
        .frf      = SPI_CTRL_FRF_0,
        .nssp     = SPI_CTRL_NSSP_0,
        .frxth    = SPI_CTRL_FRXTH_0,
        .ldmatx   = SPI_CTRL_LDMATX_0,
        .ldmarx   = SPI_CTRL_LDMARX_0,
    },
    .init = SPI_CTRL_STAT_DEINIT,
};

///
/// \brief Contains function pointers that allow the clock phase to be set using the libopencm3 functions.
///
static void (*const spi_ctrl_set_cpha_arr[SPI_CTRL_CPHA_TOTAL])(uint32_t intf) =
{
    spi_set_clock_phase_0,
    spi_set_clock_phase_1,
};

///
/// \brief Contains function pointers that allow the clock polarity to be set using the libopencm3 functions.
///
static void (*const spi_ctrl_set_cpol_arr[SPI_CTRL_CPOL_TOTAL])(uint32_t intf) =
{
    spi_set_clock_polarity_0,
    spi_set_clock_polarity_1,
};

///
/// \brief Contains function pointers that allow the bidirectional data mode to be set using the libopencm3 functions.
///
static void (*const spi_ctrl_set_bidimode_arr[SPI_CTRL_BIDIMODE_TOTAL])(uint32_t intf) =
{
    spi_set_unidirectional_mode,
    spi_set_bidirectional_mode,
};

///
/// \brief Contains function pointers that allow the output enable in bidirectional mode to be set
///        using the libopencm3 functions.
///
static void (*const spi_ctrl_set_bidioe_arr[SPI_CTRL_BIDIOE_TOTAL])(uint32_t intf) =
{
    spi_set_bidirectional_receive_only_mode,
    spi_set_bidirectional_transmit_only_mode,
};

///
/// \brief Contains function pointers that allow the frame format to be set using the libopencm3 functions.
///
static void (*const spi_ctrl_set_lsbfirst_arr[SPI_CTRL_LSBFIRST_TOTAL])(uint32_t intf) =
{
    spi_send_msb_first,
    spi_send_lsb_first,
};

///
/// \brief Contains function pointers that allow the hardware CRC calculation to be set using the libopencm3
///        functions.
///
static void (*const spi_ctrl_set_crcen_arr[SPI_CTRL_CRCEN_TOTAL])(uint32_t intf) =
{
    spi_disable_crc,
    spi_enable_crc,
};

///
/// \brief Contains function pointers that allow the CRC length to be set using the libopencm3 functions.
///
static void (*const spi_ctrl_set_crcl_arr[SPI_CTRL_CRCL_TOTAL])(uint32_t intf) =
{
    spi_set_crcl_8bit,
    spi_set_crcl_16bit,
};

///
/// \brief Contains function pointers that allow the software slave management to be set using the
///        libopencm3 functions.
///
static void (*const spi_ctrl_set_ssm_arr[SPI_CTRL_SSM_TOTAL])(uint32_t intf) =
{
    spi_set_crcl_8bit,
    spi_set_crcl_16bit,
};

///
/// \brief Contains function pointers that allow the internal slave select to be set using the
///        libopencm3 functions.
///
static void (*const spi_ctrl_set_ssi_arr[SPI_CTRL_SSI_TOTAL])(uint32_t intf) =
{
    spi_set_nss_low,
    spi_set_nss_high,
};

///
/// \brief Contains function pointers that allow the master selection to be set using the
///        libopencm3 functions.
///
static void (*const spi_ctrl_set_mstr_arr[SPI_CTRL_MSTR_TOTAL])(uint32_t intf) =
{
    spi_set_slave_mode,
    spi_set_master_mode,
};

///
/// \brief Contains function pointers that allow the slave select output enable to be set using the
///        libopencm3 functions.
///
static void (*const spi_ctrl_set_ssoe_arr[SPI_CTRL_SSOE_TOTAL])(uint32_t intf) =
{
    spi_disable_ss_output,
    spi_enable_ss_output,
};

///
/// \brief Contains function pointers that allow the frame format to be set using the libopencm3 functions.
///
static void (*const spi_ctrl_set_frf_arr[SPI_CTRL_FRF_TOTAL])(uint32_t intf) =
{
    spi_set_frf_motorola,
    spi_set_frf_ti,
};

///
/// \brief Contains function pointers that allow the NSS pulse management to be set using the
///        libopencm3 functions.
static void (*const spi_ctrl_set_nssp_arr[SPI_CTRL_NSSP_TOTAL])(uint32_t intf) =
{
    spi_disable_nssp,
    spi_enable_nssp,
};

///
/// \brief Contains function pointers that allow the FIFO reception threshold to be set using the
///        libopencm3 functions.
static void (*const spi_ctrl_set_frxth_arr[SPI_CTRL_FRXTH_TOTAL])(uint32_t intf) =
{
    spi_fifo_reception_threshold_16bit,
    spi_fifo_reception_threshold_8bit,
};

///
/// \brief Contains function pointers that allow the last DMA transfer for transmission to be set using the
///        libopencm3 functions.
static void (*const spi_ctrl_set_ldmatx_arr[SPI_CTRL_LDMATX_TOTAL])(uint32_t intf) =
{
    spi_set_ldmatx_even,
    spi_set_ldmatx_odd,
};

///
/// \brief Contains function pointers that allow the last DMA transfer for reception to be set using the
///        libopencm3 functions.
static void (*const spi_ctrl_set_ldmarx_arr[SPI_CTRL_LDMARX_TOTAL])(uint32_t intf) =
{
    spi_set_ldmarx_even,
    spi_set_ldmarx_odd,
};

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief Validates the CR1 and CR2 config values.
///
/// \param[in] inst          The spi controller instance.
///
/// \return spi_ctrl_res_t   The spi controller result.
/// \retval SPI_CTRL_RES_OK  On success.
/// \retval SPI_CTRL_RES_ERR Otherwise.
///
static spi_ctrl_res_t spi_ctrl_vld_conf(const spi_ctrl_t *const inst);

///
/// \brief Sets the CRC polynomial register.
///
/// \param[in] inst The spi controller instance.
///
static void spi_set_crcpr(const spi_ctrl_t *const inst);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static spi_ctrl_res_t spi_ctrl_vld_conf(const spi_ctrl_t *const inst)
{
    /* Whether the instance is NULL was checked before. */

    /* CPHA must be cleared in NSSP mode.*/
    if ((inst->cr2.nssp == SPI_CTRL_NSSP_1) && (inst->cr1.cpha == SPI_CTRL_CPHA_1))
    {
        return SPI_CTRL_RES_ERR;
    }

    /* RXONLY and BIDIMODE can't be set at the same time. */
    if ((inst->cr1.rxonly == SPI_CTRL_RXONLY_1) &&
        (inst->cr1.bidimode == SPI_CTRL_BIDIMODE_1))
    {
        return SPI_CTRL_RES_ERR;
    }

    /* Keep CHPA and TI bits cleared in NSSP mode. */
    if (((inst->cr2.nssp == SPI_CTRL_NSSP_1) && (inst->cr2.frf == SPI_CTRL_FRF_1)) ||
        ((inst->cr2.nssp == SPI_CTRL_NSSP_1) && (inst->cr1.cpha == SPI_CTRL_CPHA_1)))
    {
        return SPI_CTRL_RES_ERR;
    }

    /* Keep NSSP bit cleared in TI mode. */
    if ((inst->cr1.frf == SPI_CTRL_FRF_1) && (inst->cr1.nssp == SPI_CTRL_NSSP_1))
    {
        return SPI_CTRL_RES_ERR;
    }

    return SPI_CTRL_RES_OK;
}

static void spi_set_crcpr(const spi_ctrl_t *const inst)
{
    /* Whether the instance is NULL was checked before. */

    SPI_CRCPR(inst->intf) = inst->crcpr.crcpoly;
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
spi_ctrl_res_t spi_ctrl_init(spi_ctrl_t *const inst)
{
    if (inst == NULL)
    {
        return SPI_CTRL_RES_ERR;
    }

    if (spi_ctrl_vld_conf(inst) != SPI_CTRL_RES_OK)
    {
        return SPI_CTRL_RES_ERR;
    }

    spi_disable(inst->intf);

    /* The CR1 configuration. */
    spi_ctrl_set_cpha_arr[inst->cr1.cpha](inst->intf);
    spi_ctrl_set_cpol_arr[inst->cr1.cpol](inst->intf);
    spi_ctrl_set_bidimode_arr[inst->cr1.bidimode](inst->intf);
    spi_ctrl_set_bidioe_arr[inst->cr1.bidioe](inst->intf);
    spi_ctrl_set_lsbfirst_arr[inst->cr1.lsbfirst](inst->intf);
    spi_ctrl_set_crcen_arr[inst->cr1.crcen](inst->intf);
    spi_ctrl_set_crcl_arr[inst->cr1.crcl](inst->intf);
    spi_ctrl_set_ssm_arr[inst->cr1.ssm](inst->intf);
    spi_ctrl_set_ssi_arr[inst->cr1.ssi](inst->intf);
    spi_ctrl_set_mstr_arr[inst->cr1.mstr](inst->intf);

    /* The CR2 configuration. */
    spi_set_data_size(inst->intf, (uint16_t)inst->cr2.ds);
    spi_ctrl_set_ssoe_arr[inst->cr2.ssoe](inst->intf);
    spi_ctrl_set_frf_arr[inst->cr2.frf](inst->intf);
    spi_ctrl_set_nssp_arr[inst->cr2.nssp](inst->intf);
    spi_ctrl_set_frxth_arr[inst->cr2.frxth](inst->intf);
    spi_ctrl_set_ldmatx_arr[inst->cr2.ldmatx](inst->intf);
    spi_ctrl_set_ldmarx_arr[inst->cr2.ldmarx](inst->intf);

    if (inst->crcpr.set == true)
    {
        spi_set_crcpr(inst);
    }

    inst->init = SPI_CTRL_STAT_INIT;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_deinit(spi_ctrl_t *const inst)
{
    if (inst == NULL)
    {
        return SPI_CTRL_RES_ERR;
    }

    spi_disable(inst->intf);
    inst->init = SPI_CTRL_STAT_DEINIT;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_get_inst(const spi_ctrl_t **inst)
{
    if (inst == NULL)
    {
        return SPI_CTRL_RES_ERR;
    }

    *inst = &spi_ctrl_inst;
    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_begin(const spi_ctrl_t *const inst, const uint32_t gpio_port, const uint32_t gpios)
{
    if (inst == NULL)
    {
        return SPI_CTRL_RES_ERR;
    }

    if (inst->cr2.ssoe == SPI_CTRL_SSOE_0)
    {
        /* Change the NSS to low state. */
        gpio_clear(gpio_port, gpios);
    }

    spi_enable(inst->intf);

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_end(const spi_ctrl_t *const inst, const uint32_t gpio_port, const uint32_t gpios)
{
    if (inst == NULL)
    {
        return SPI_CTRL_RES_ERR;
    }

    spi_disable(inst->intf);

    if (inst->cr2.ssoe == SPI_CTRL_SSOE_0)
    {
        /* Change the NSS to high state. */
        gpio_set(gpio_port, gpios);
    }

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_recv(const spi_ctrl_t *const inst, uint8_t *const buf, const uint32_t sz)
{
    if ((inst == NULL) || (buf == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    const uint8_t step  = (inst->cr2.ds <= SPI_CTRL_DS_8) ? 1 : 2;
    for (size_t i = 0; i < sz; i += step)
    {
        uint16_t data = spi_read(inst->intf);

        if (step == 2)
        {
            if ((i + 1) >= sz)
            {
                return SPI_CTRL_RES_ERR;
            }

            buf[i]     = ((data >> 8) & 0xff);
            buf[i + 1] = ((data >> 0) & 0xff);
        }
        else
        {
            buf[i] = ((data >> 0) & 0xff);
        }
    }

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_send(const spi_ctrl_t *const inst, const uint8_t *const buf, const uint32_t sz)
{
    if ((inst == NULL) || (buf == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    const uint8_t step = (inst->cr2.ds <= SPI_CTRL_DS_8) ? 1 : 2;

    for (size_t i = 0; i < sz; i += step)
    {
        uint16_t data;

        if (step == 2)
        {
            if ((i + 1) >= sz)
            {
                return SPI_CTRL_RES_ERR;
            }

            data = (((uint16_t)buf[i] << 8) | buf[i + 1]);
        }
        else
        {
            data = buf[i];
        }

        spi_send(inst->intf, data);
    }

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_crcpr(spi_ctrl_t *const inst, const uint16_t crcpoly)
{
    if (inst == NULL)
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->crcpr.crcpoly = crcpoly;
    inst->crcpr.set     = true;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_cpha(spi_ctrl_t *const inst, const spi_ctrl_cpha_t cpha)
{
    if ((cpha < SPI_CTRL_CPHA_BEGIN) || (cpha >= SPI_CTRL_CPHA_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.cpha = cpha;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_cpol(spi_ctrl_t *const inst, const spi_ctrl_cpol_t cpol)
{
    if ((cpol < SPI_CTRL_CPOL_BEGIN) || (cpol >= SPI_CTRL_CPOL_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.cpol = cpol;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_bidimode(spi_ctrl_t *const inst, const spi_ctrl_bidimode_t bidimode)
{
    if ((bidimode < SPI_CTRL_BIDIMODE_BEGIN) || (bidimode >= SPI_CTRL_BIDIMODE_TOTAL) ||
        (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.bidimode = bidimode;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_bidioe(spi_ctrl_t *const inst, const spi_ctrl_bidioe_t bidioe)
{
    if ((bidioe < SPI_CTRL_BIDIOE_BEGIN) || (bidioe >= SPI_CTRL_BIDIOE_TOTAL) ||
        (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.bidioe = bidioe;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_rxonly(spi_ctrl_t *const inst, const spi_ctrl_rxonly_t rxonly)
{
    if ((rxonly < SPI_CTRL_RXONLY_BEGIN) || (rxonly >= SPI_CTRL_RXONLY_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.rxonly = rxonly;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_lsbfirst(spi_ctrl_t *const inst, const spi_ctrl_lsbfirst_t lsbfirst)
{
    if ((lsbfirst < SPI_CTRL_LSBFIRST_BEGIN) || (lsbfirst >= SPI_CTRL_LSBFIRST_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.lsbfirst = lsbfirst;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_crcen(spi_ctrl_t *const inst, const spi_ctrl_crcen_t crcen)
{
    if ((crcen < SPI_CTRL_CRCEN_BEGIN) || (crcen >= SPI_CTRL_CRCEN_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.crcen = crcen;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_crcl(spi_ctrl_t *const inst, const spi_ctrl_crcl_t crcl)
{
    if ((crcl < SPI_CTRL_CRCL_BEGIN) || (crcl >= SPI_CTRL_CRCL_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.crcl = crcl;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_ssm(spi_ctrl_t *const inst, const spi_ctrl_ssm_t ssm)
{
    if ((ssm < SPI_CTRL_SSM_BEGIN) || (ssm >= SPI_CTRL_SSM_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.ssm = ssm;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_ssi(spi_ctrl_t *const inst, const spi_ctrl_ssi_t ssi)
{
    if ((ssi < SPI_CTRL_SSI_BEGIN) || (ssi >= SPI_CTRL_SSI_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.ssi = ssi;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_mstr(spi_ctrl_t *const inst, const spi_ctrl_mstr_t mstr)
{
    if ((mstr < SPI_CTRL_MSTR_BEGIN) || (mstr >= SPI_CTRL_MSTR_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr1.mstr = mstr;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_ds(spi_ctrl_t *const inst, const spi_ctrl_ds_t ds)
{
    if ((ds < SPI_CTRL_DS_BEGIN) || (ds >= SPI_CTRL_DS_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr2.ds = ds;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_ssoe(spi_ctrl_t *const inst, const spi_ctrl_ssoe_t ssoe)
{
    if ((ssoe < SPI_CTRL_SSOE_BEGIN) || (ssoe >= SPI_CTRL_SSOE_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr2.ssoe = ssoe;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_frf(spi_ctrl_t *const inst, const spi_ctrl_frf_t frf)
{
    if ((frf < SPI_CTRL_FRF_BEGIN) || (frf >= SPI_CTRL_FRF_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr2.frf = frf;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_nssp(spi_ctrl_t *const inst, const spi_ctrl_nssp_t nssp)
{
    if ((nssp < SPI_CTRL_NSSP_BEGIN) || (nssp >= SPI_CTRL_NSSP_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr2.nssp = nssp;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_frxth(spi_ctrl_t *const inst, const spi_ctrl_frxth_t frxth)
{
    if ((frxth < SPI_CTRL_FRXTH_BEGIN) || (frxth >= SPI_CTRL_FRXTH_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr2.frxth = frxth;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_ldmatx(spi_ctrl_t *const inst, const spi_ctrl_ldmatx_t ldmatx)
{
    if ((ldmatx < SPI_CTRL_LDMATX_BEGIN) || (ldmatx >= SPI_CTRL_LDMATX_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr2.ldmatx = ldmatx;

    return SPI_CTRL_RES_OK;
}

spi_ctrl_res_t spi_ctrl_set_ldmarx(spi_ctrl_t *const inst, const spi_ctrl_ldmarx_t ldmarx)
{
    if ((ldmarx < SPI_CTRL_LDMARX_BEGIN) || (ldmarx >= SPI_CTRL_LDMARX_TOTAL) || (inst == NULL))
    {
        return SPI_CTRL_RES_ERR;
    }

    inst->cr2.ldmarx = ldmarx;

    return SPI_CTRL_RES_OK;
}
