#include "ll_spi.h"
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
struct crcpr_conf
{
    uint16_t crcpoly;                               /*!< The CRC polynomial value.                          */
    bool     set;                                   /*!< The set CRC polynomial flag.                       */
};

///
/// \brief The spi CR1 config type.
///
struct cr1_conf
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
    uint8_t  br       : 3;                          /*!< The baud rate control.                             */
};

///
/// \brief The spi CR2 config type.
///
struct cr2_conf
{
    uint8_t  ds       : 4;                          /*!< The data size index.                               */
    uint8_t  ssoe     : 1;                          /*!< The slave select output enable index.              */
    uint8_t  frf      : 1;                          /*!< The frame format index.                            */
    uint8_t  nssp     : 1;                          /*!< The NSS pulse management index.                    */
    uint8_t  frxth    : 1;                          /*!< The FIFO reception threshold index.                */
    uint8_t  ldmatx   : 1;                          /*!< The last DMA transfer for transmission index.      */
    uint8_t  ldmarx   : 1;                          /*!< The last DMA transfer for reception index.         */
};

///
/// \brief The spi device type.
///
struct ll_spi_dev
{
    uint32_t          intf;                         /*!< The spi peripheral interface.                      */
    struct cr1_conf   cr1;                          /*!< The spi CR1 config.                                */
    struct cr2_conf   cr2;                          /*!< The spi CR2 config.                                */
    struct crcpr_conf crcpr;                        /*!< The spi CRCPR config.                              */
    bool              stat;                         /*!< The status flag.                                   */
};

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The spi deivce array.
///
static struct ll_spi_dev ll_spi_dev_arr[LL_SPI_INST_TOTAL] =
{
    [LL_SPI_INST_SPI1] =
    {
        .intf  = SPI1,
        .crcpr =
        {
            .crcpoly  = CRCPOLY_RES_VAL,
            .set      = false,
        },
        .cr1 =
        {
            .cpha     = LL_SPI_CPHA_0,
            .cpol     = LL_SPI_CPOL_0,
            .bidimode = LL_SPI_BIDIMODE_0,
            .bidioe   = LL_SPI_BIDIOE_0,
            .rxonly   = LL_SPI_RXONLY_0,
            .lsbfirst = LL_SPI_LSBFIRST_0,
            .crcen    = LL_SPI_CRCEN_0,
            .ssm      = LL_SPI_SSM_0,
            .ssi      = LL_SPI_SSI_0,
            .mstr     = LL_SPI_MSTR_1,
            .br       = SPI_CR1_BR_FPCLK_DIV_16,
        },
        .cr2 =
        {
            .ds       = LL_SPI_DS_8,
            .ssoe     = LL_SPI_SSOE_1,
            .frf      = LL_SPI_FRF_0,
            .nssp     = LL_SPI_NSSP_0,
            .frxth    = LL_SPI_FRXTH_1,
            .ldmatx   = LL_SPI_LDMATX_0,
            .ldmarx   = LL_SPI_LDMARX_0,
        },
        .stat = LL_SPI_STAT_DEINIT,
    },
};

///
/// \brief Contains function pointers that allow the clock phase to be set using the libopencm3 functions.
///
static void (*const ll_spi_set_cpha_arr[LL_SPI_CPHA_TOTAL])(uint32_t intf) =
{
    spi_set_clock_phase_0,
    spi_set_clock_phase_1,
};

///
/// \brief Contains function pointers that allow the clock polarity to be set using the libopencm3 functions.
///
static void (*const ll_spi_set_cpol_arr[LL_SPI_CPOL_TOTAL])(uint32_t intf) =
{
    spi_set_clock_polarity_0,
    spi_set_clock_polarity_1,
};

///
/// \brief Contains function pointers that allow the bidirectional data mode to be set using the libopencm3 functions.
///
static void (*const ll_spi_set_bidimode_arr[LL_SPI_BIDIMODE_TOTAL])(uint32_t intf) =
{
    spi_set_unidirectional_mode,
    spi_set_bidirectional_mode,
};

///
/// \brief Contains function pointers that allow the output enable in bidirectional mode to be set
///        using the libopencm3 functions.
///
static void (*const ll_spi_set_bidioe_arr[LL_SPI_BIDIOE_TOTAL])(uint32_t intf) =
{
    spi_set_bidirectional_receive_only_mode,
    spi_set_bidirectional_transmit_only_mode,
};

///
/// \brief Contains function pointers that allow the frame format to be set using the libopencm3 functions.
///
static void (*const ll_spi_set_lsbfirst_arr[LL_SPI_LSBFIRST_TOTAL])(uint32_t intf) =
{
    spi_send_msb_first,
    spi_send_lsb_first,
};

///
/// \brief Contains function pointers that allow the hardware CRC calculation to be set using the libopencm3
///        functions.
///
static void (*const ll_spi_set_crcen_arr[LL_SPI_CRCEN_TOTAL])(uint32_t intf) =
{
    spi_disable_crc,
    spi_enable_crc,
};

///
/// \brief Contains function pointers that allow the CRC length to be set using the libopencm3 functions.
///
static void (*const ll_spi_set_crcl_arr[LL_SPI_CRCL_TOTAL])(uint32_t intf) =
{
    spi_set_crcl_8bit,
    spi_set_crcl_16bit,
};

///
/// \brief Contains function pointers that allow the software slave management to be set using the
///        libopencm3 functions.
///
static void (*const ll_spi_set_ssm_arr[LL_SPI_SSM_TOTAL])(uint32_t intf) =
{
    spi_disable_software_slave_management,
    spi_enable_software_slave_management,
};

///
/// \brief Contains function pointers that allow the internal slave select to be set using the
///        libopencm3 functions.
///
static void (*const ll_spi_set_ssi_arr[LL_SPI_SSI_TOTAL])(uint32_t intf) =
{
    spi_set_nss_low,
    spi_set_nss_high,
};

///
/// \brief Contains function pointers that allow the master selection to be set using the
///        libopencm3 functions.
///
static void (*const ll_spi_set_mstr_arr[LL_SPI_MSTR_TOTAL])(uint32_t intf) =
{
    spi_set_slave_mode,
    spi_set_master_mode,
};

///
/// \brief Contains function pointers that allow the slave select output enable to be set using the
///        libopencm3 functions.
///
static void (*const ll_spi_set_ssoe_arr[LL_SPI_SSOE_TOTAL])(uint32_t intf) =
{
    spi_disable_ss_output,
    spi_enable_ss_output,
};

///
/// \brief Contains function pointers that allow the frame format to be set using the libopencm3 functions.
///
static void (*const ll_spi_set_frf_arr[LL_SPI_FRF_TOTAL])(uint32_t intf) =
{
    spi_set_frf_motorola,
    spi_set_frf_ti,
};

///
/// \brief Contains function pointers that allow the NSS pulse management to be set using the
///        libopencm3 functions.
static void (*const ll_spi_set_nssp_arr[LL_SPI_NSSP_TOTAL])(uint32_t intf) =
{
    spi_disable_nssp,
    spi_enable_nssp,
};

///
/// \brief Contains function pointers that allow the FIFO reception threshold to be set using the
///        libopencm3 functions.
static void (*const ll_spi_set_frxth_arr[LL_SPI_FRXTH_TOTAL])(uint32_t intf) =
{
    spi_fifo_reception_threshold_16bit,
    spi_fifo_reception_threshold_8bit,
};

///
/// \brief Contains function pointers that allow the last DMA transfer for transmission to be set using the
///        libopencm3 functions.
static void (*const ll_spi_set_ldmatx_arr[LL_SPI_LDMATX_TOTAL])(uint32_t intf) =
{
    spi_set_ldmatx_even,
    spi_set_ldmatx_odd,
};

///
/// \brief Contains function pointers that allow the last DMA transfer for reception to be set using the
///        libopencm3 functions.
static void (*const ll_spi_set_ldmarx_arr[LL_SPI_LDMARX_TOTAL])(uint32_t intf) =
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
/// \param[in] dev The spi device.
///
/// \return ll_spi_res_t   The spi result.
/// \retval LL_SPI_RES_OK  On success.
/// \retval LL_SPI_RES_ERR Otherwise.
///
static ll_spi_res_t ll_spi_vld_conf(const struct ll_spi_dev *const dev);

///
/// \brief Sets the CRC polynomial register.
///
/// \param[in] dev The spi device.
///
static void spi_set_crcpr(const struct ll_spi_dev *const dev);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static ll_spi_res_t ll_spi_vld_conf(const struct ll_spi_dev *const dev)
{
    /* CPHA must be cleared in NSSP mode.*/
    if ((dev->cr2.nssp == LL_SPI_NSSP_1) && (dev->cr1.cpha == LL_SPI_CPHA_1))
    {
        return LL_SPI_RES_ERR;
    }

    /* RXONLY and BIDIMODE can't be set at the same time. */
    if ((dev->cr1.rxonly == LL_SPI_RXONLY_1) &&
        (dev->cr1.bidimode == LL_SPI_BIDIMODE_1))
    {
        return LL_SPI_RES_ERR;
    }

    /* Keep CHPA and TI bits cleared in NSSP mode. */
    if (((dev->cr2.nssp == LL_SPI_NSSP_1) && (dev->cr2.frf == LL_SPI_FRF_1)) ||
        ((dev->cr2.nssp == LL_SPI_NSSP_1) && (dev->cr1.cpha == LL_SPI_CPHA_1)))
    {
        return LL_SPI_RES_ERR;
    }

    /* Keep NSSP bit cleared in TI mode. */
    if ((dev->cr2.frf == LL_SPI_FRF_1) && (dev->cr2.nssp == LL_SPI_NSSP_1))
    {
        return LL_SPI_RES_ERR;
    }

    return LL_SPI_RES_OK;
}

static void spi_set_crcpr(const struct ll_spi_dev *const dev)
{
    SPI_CRCPR(dev->intf) = dev->crcpr.crcpoly;
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ll_spi_res_t ll_spi_dev_init(const ll_spi_inst_t inst)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if (ll_spi_vld_conf(dev) != LL_SPI_RES_OK)
    {
        return LL_SPI_RES_ERR;
    }

    spi_disable(dev->intf);

    /* The CR1 configuration. */
    spi_set_baudrate_prescaler(dev->intf, (uint8_t)dev->cr1.br);
    ll_spi_set_cpha_arr[dev->cr1.cpha](dev->intf);
    ll_spi_set_cpol_arr[dev->cr1.cpol](dev->intf);
    ll_spi_set_bidimode_arr[dev->cr1.bidimode](dev->intf);
    //ll_spi_set_bidioe_arr[dev->cr1.bidioe](dev->intf);
    ll_spi_set_lsbfirst_arr[dev->cr1.lsbfirst](dev->intf);
    ll_spi_set_crcen_arr[dev->cr1.crcen](dev->intf);
    ll_spi_set_crcl_arr[dev->cr1.crcl](dev->intf);
    ll_spi_set_ssm_arr[dev->cr1.ssm](dev->intf);
    ll_spi_set_ssi_arr[dev->cr1.ssi](dev->intf);
    ll_spi_set_mstr_arr[dev->cr1.mstr](dev->intf);

    /* The CR2 configuration. */
    spi_set_data_size(dev->intf, (uint16_t)dev->cr2.ds);
    ll_spi_set_ssoe_arr[dev->cr2.ssoe](dev->intf);
    ll_spi_set_frf_arr[dev->cr2.frf](dev->intf);
    ll_spi_set_nssp_arr[dev->cr2.nssp](dev->intf);
    ll_spi_set_frxth_arr[dev->cr2.frxth](dev->intf);
    ll_spi_set_ldmatx_arr[dev->cr2.ldmatx](dev->intf);
    ll_spi_set_ldmarx_arr[dev->cr2.ldmarx](dev->intf);

    if (dev->crcpr.set == true)
    {
        spi_set_crcpr(dev);
    }

    dev->stat = LL_SPI_STAT_INIT;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_dev_deinit(const ll_spi_inst_t inst)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    spi_disable(dev->intf);
    dev->stat = LL_SPI_STAT_DEINIT;

    return LL_SPI_RES_OK;
}

struct ll_spi_dev* ll_spi_dev_get(const ll_spi_inst_t inst)
{
    return &ll_spi_dev_arr[inst];
}

ll_spi_res_t ll_spi_crcpr_set(const ll_spi_inst_t inst, const uint16_t crcpoly)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    dev->crcpr.crcpoly = crcpoly;
    dev->crcpr.set     = true;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_cpha_set(const ll_spi_inst_t inst, const ll_spi_cpha_t cpha)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((cpha < LL_SPI_CPHA_BEGIN) || (cpha >= LL_SPI_CPHA_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.cpha = cpha;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_cpol_set(const ll_spi_inst_t inst, const ll_spi_cpol_t cpol)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((cpol < LL_SPI_CPOL_BEGIN) || (cpol >= LL_SPI_CPOL_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.cpol = cpol;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_bidimode_set(const ll_spi_inst_t inst, const ll_spi_bidimode_t bidimode)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((bidimode < LL_SPI_BIDIMODE_BEGIN) || (bidimode >= LL_SPI_BIDIMODE_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.bidimode = bidimode;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_bidioe_set(const ll_spi_inst_t inst, const ll_spi_bidioe_t bidioe)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((bidioe < LL_SPI_BIDIOE_BEGIN) || (bidioe >= LL_SPI_BIDIOE_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.bidioe = bidioe;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_rxonly_set(const ll_spi_inst_t inst, const ll_spi_rxonly_t rxonly)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((rxonly < LL_SPI_RXONLY_BEGIN) || (rxonly >= LL_SPI_RXONLY_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.rxonly = rxonly;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_lsbfirst_set(const ll_spi_inst_t inst, const ll_spi_lsbfirst_t lsbfirst)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((lsbfirst < LL_SPI_LSBFIRST_BEGIN) || (lsbfirst >= LL_SPI_LSBFIRST_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.lsbfirst = lsbfirst;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_crcen_set(const ll_spi_inst_t inst, const ll_spi_crcen_t crcen)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((crcen < LL_SPI_CRCEN_BEGIN) || (crcen >= LL_SPI_CRCEN_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.crcen = crcen;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_crcl_set(const ll_spi_inst_t inst, const ll_spi_crcl_t crcl)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((crcl < LL_SPI_CRCL_BEGIN) || (crcl >= LL_SPI_CRCL_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.crcl = crcl;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_ssm_set(const ll_spi_inst_t inst, const ll_spi_ssm_t ssm)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((ssm < LL_SPI_SSM_BEGIN) || (ssm >= LL_SPI_SSM_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.ssm = ssm;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_ssi_set(const ll_spi_inst_t inst, const ll_spi_ssi_t ssi)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((ssi < LL_SPI_SSI_BEGIN) || (ssi >= LL_SPI_SSI_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.ssi = ssi;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_mstr_set(const ll_spi_inst_t inst, const ll_spi_mstr_t mstr)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((mstr < LL_SPI_MSTR_BEGIN) || (mstr >= LL_SPI_MSTR_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr1.mstr = mstr;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_ds_set(const ll_spi_inst_t inst, const ll_spi_ds_t ds)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((ds < LL_SPI_DS_BEGIN) || (ds >= LL_SPI_DS_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr2.ds = ds;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_ssoe_set(const ll_spi_inst_t inst, const ll_spi_ssoe_t ssoe)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((ssoe < LL_SPI_SSOE_BEGIN) || (ssoe >= LL_SPI_SSOE_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr2.ssoe = ssoe;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_frf_set(const ll_spi_inst_t inst, const ll_spi_frf_t frf)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((frf < LL_SPI_FRF_BEGIN) || (frf >= LL_SPI_FRF_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr2.frf = frf;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_nssp_set(const ll_spi_inst_t inst, const ll_spi_nssp_t nssp)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((nssp < LL_SPI_NSSP_BEGIN) || (nssp >= LL_SPI_NSSP_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr2.nssp = nssp;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_frxth_set(const ll_spi_inst_t inst, const ll_spi_frxth_t frxth)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((frxth < LL_SPI_FRXTH_BEGIN) || (frxth >= LL_SPI_FRXTH_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr2.frxth = frxth;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_ldmatx_set(const ll_spi_inst_t inst, const ll_spi_ldmatx_t ldmatx)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((ldmatx < LL_SPI_LDMATX_BEGIN) || (ldmatx >= LL_SPI_LDMATX_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr2.ldmatx = ldmatx;

    return LL_SPI_RES_OK;
}

ll_spi_res_t ll_spi_ldmarx_set(const ll_spi_inst_t inst, const ll_spi_ldmarx_t ldmarx)
{
    struct ll_spi_dev *dev = &ll_spi_dev_arr[inst];

    if ((ldmarx < LL_SPI_LDMARX_BEGIN) || (ldmarx >= LL_SPI_LDMARX_TOTAL))
    {
        return LL_SPI_RES_ERR;
    }

    dev->cr2.ldmarx = ldmarx;

    return LL_SPI_RES_OK;
}
