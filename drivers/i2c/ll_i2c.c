#include "ll_i2c.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief Default register configuration for I2C after power-on reset.
///
/// This constant structure represents the expected reset (POR) state of the
/// I2C registers. It is used as a known-good baseline for initialization and
/// for restoring registers to their default values before applying custom
/// configuration.
///
static const struct ll_tim_adv6_tim18_regs ll_tim_adv6_tim18_por =
{
    .cr1 =
    {
        .bf =
        {
            .pe        = 0x00,
            .txie      = 0x00,
            .rxie      = 0x00,
            .addrie    = 0x00,
            .nackie    = 0x00,
            .stopie    = 0x00,
            .tcie      = 0x00,
            .errie     = 0x00,
            .dnf       = 0x00,
            .anfoff    = 0x00,
            .txdmaen   = 0x00,
            .rxdmaen   = 0x00,
            .sbc       = 0x00,
            .nostretch = 0x00,
            .gcen      = 0x00,
            .smbhen    = 0x00,
            .smbden    = 0x00,
            .alerten   = 0x00,
            .pcen      = 0x00,
        },
    },

    .cr2 =
    {
        .bf =
        {
            .sadd    = 0x00,
            .rdwrn   = 0x00,
            .add10   = 0x00,
            .head10r = 0x00,
            .start   = 0x00,
            .stop    = 0x00,
            .nack    = 0x00,
            .nbytes  = 0x00,
            .reload  = 0x00,
            .autoend = 0x00,
            .pecbyte = 0x00,
        },
    },

    .oar1 =
    {
        .bf =
        {
            .oa1_0   = 0x00,
            .oa1_71  = 0x00,
            .oa1_98  = 0x00,
            .oa1mode = 0x00,
            .oa1en   = 0x00,
        },
    },

    .oar2 =
    {
        .bf =
        {
            .oa2_71 = 0x00,
            .oa2msk = 0x00,
            .oa2en  = 0x00,
        },
    },

    .timingr =
    {
        .bf =
        {
            .scll   = 0x00,
            .sclh   = 0x00,
            .sdadel = 0x00,
            .scldel = 0x00,
            .presc  = 0x00,
        },
    },

    .timeoutr =
    {
        .bf =
        {
            .timeouta = 0x00,
            .tidle    = 0x00,
            .timouten = 0x00,
            .timeoutb = 0x00,
            .texten   = 0x00,
        },
    },

    .isr =
    {
        .bf =
        {
            .txe     = 0x00,
            .txis    = 0x00,
            .rxne    = 0x00,
            .addr    = 0x00,
            .nackf   = 0x00,
            .stopf   = 0x00,
            .tc      = 0x00,
            .tcr     = 0x00,
            .berr    = 0x00,
            .arlo    = 0x00,
            .ovr     = 0x00,
            .pecerr  = 0x00,
            .timeout = 0x00,
            .alert   = 0x00,
            .busy    = 0x00,
            .dir     = 0x00,
            .addcode = 0x00,
        },
    },

    .icr =
    {
        .bf =
        {
            .addrcf   = 0x00,
            .nackcf   = 0x00,
            .stopcf   = 0x00,
            .berrcf   = 0x00,
            .arlocf   = 0x00,
            .ovrcf    = 0x00,
            .peccf    = 0x00,
            .timoutcf = 0x00,
            .alertcf  = 0x00,
        },
    },

    .pecr =
    {
        .bf =
        {
            .pec = 0x00,
        },
    },

    .rxdr =
    {
        .bf =
        {
            .rxdata = 0x00,
        },
    },

    .txdr =
    {
        .bf =
        {
            .txdata = 0x00,
        },
    },

}

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ll_i2c_res_t ll_i2c_master_init(ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_INIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = handle->rtmp->cr1.r;
    handle->rmap->cr2.r     = handle->rtmp->cr2.r;
    handle->rmap->oar1.r    = handle->rtmp->oar1.r;
    handle->rmap->oar2.r    = handle->rtmp->oar2.r;
    handle->rmap->timingr.r = handle->rtmp->timingr.r;
    handle->rmap->icr.r     = handle->rtmp->icr.r;

    handle->stat = LL_I2C_STAT_INIT;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_slave_init(ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_INIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = handle->rtmp->cr1.r;
    handle->rmap->cr2.r     = handle->rtmp->cr2.r;
    handle->rmap->oar1.r    = handle->rtmp->oar1.r;
    handle->rmap->oar2.r    = handle->rtmp->oar2.r;
    handle->rmap->timingr.r = handle->rtmp->timingr.r;
    handle->rmap->icr.r     = handle->rtmp->icr.r;

    handle->stat = LL_I2C_STAT_INIT;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_master_deinit(ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_DEINIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = ll_i2c_por.cr1.r;
    handle->rmap->cr2.r     = ll_i2c_por.cr2.r;
    handle->rmap->oar1.r    = ll_i2c_por.oar1.r;
    handle->rmap->oar2.r    = ll_i2c_por.oar2.r;
    handle->rmap->timingr.r = ll_i2c_por.timingr.r;
    handle->rmap->icr.r     = ll_i2c_por.icr.r;

    handle->stat = LL_I2C_STAT_DEINIT;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_slave_deinit(ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_DEINIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = ll_i2c_por.cr1.r;
    handle->rmap->cr2.r     = ll_i2c_por.cr2.r;
    handle->rmap->oar1.r    = ll_i2c_por.oar1.r;
    handle->rmap->oar2.r    = ll_i2c_por.oar2.r;
    handle->rmap->timingr.r = ll_i2c_por.timingr.r;
    handle->rmap->icr.r     = ll_i2c_por.icr.r;

    handle->stat = LL_I2C_STAT_DEINIT;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_software_reset(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_PE_MASK);

    if ((LL_I2C_REG_CR1(address) | LL_I2C_CR1_PE_MASK) == 0x00)
    {
        LL_I2C_REG_CR1(address) |= LL_I2C_CR1_PE_MASK;
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_receive(const uint32_t address, uint8_t *const byte)
{
    if (byte == NULL)
    {
        return LL_I2C_RES_ERR;
    }

    while ((LL_I2C_REG_ISR(address) | LL_I2C_ISR_RXNE_MASK) == 0x00);

    *byte = (uint8_t)LL_I2C_REG_RXDR(address);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_transmit(const uint32_t address, const uint8_t *const byte)
{
    if (byte == NULL)
    {
        return LL_I2C_RES_ERR;
    }

    while ((LL_I2C_REG_ISR(address) | LL_I2C_ISR_TXE_MASK) == 0x00);

    LL_I2C_REG_TXDR(address) = *byte;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_txdma_enable(const uint32_t address)
{
    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_TXDMAEN_MASK;

    if (LL_I2C_REG_CR1(address) | LL_I2C_CR1_TXDMAEN_MASK) == 0x01)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_rxdma_enable(const uint32_t address)
{
    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_RXDMAEN_MASK;

    if (LL_I2C_REG_CR1(address) | LL_I2C_CR1_RXDMAEN_MASK) == 0x01)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_txdma_disable(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_TXDMAEN_MASK);

    if (LL_I2C_REG_CR1(address) | LL_I2C_CR1_TXDMAEN_MASK) == 0x00)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_rxdma_disable(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_RXDMAEN_MASK);

    if (LL_I2C_REG_CR1(address) | LL_I2C_CR1_RXDMAEN_MASK) == 0x00)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}
