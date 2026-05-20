#include "ll_i2c.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ll_i2c_res_t ll_i2c_master_init(struct ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_INIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = handle->rtmp.cr1.r;
    handle->rmap->cr2.r     = handle->rtmp.cr2.r;
    handle->rmap->oar1.r    = handle->rtmp.oar1.r;
    handle->rmap->oar2.r    = handle->rtmp.oar2.r;
    handle->rmap->timingr.r = handle->rtmp.timingr.r;
    handle->rmap->icr.r     = handle->rtmp.icr.r;

    handle->stat = LL_I2C_STAT_INIT;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_slave_init(struct ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_INIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = handle->rtmp.cr1.r;
    handle->rmap->cr2.r     = handle->rtmp.cr2.r;
    handle->rmap->oar1.r    = handle->rtmp.oar1.r;
    handle->rmap->oar2.r    = handle->rtmp.oar2.r;
    handle->rmap->timingr.r = handle->rtmp.timingr.r;
    handle->rmap->icr.r     = handle->rtmp.icr.r;

    handle->stat = LL_I2C_STAT_INIT;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_master_deinit(struct ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_DEINIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = ll_i2c_regs_por.cr1.r;
    handle->rmap->cr2.r     = ll_i2c_regs_por.cr2.r;
    handle->rmap->oar1.r    = ll_i2c_regs_por.oar1.r;
    handle->rmap->oar2.r    = ll_i2c_regs_por.oar2.r;
    handle->rmap->timingr.r = ll_i2c_regs_por.timingr.r;
    handle->rmap->icr.r     = ll_i2c_regs_por.icr.r;

    handle->stat = LL_I2C_STAT_DEINIT;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_slave_deinit(struct ll_i2c_dev *handle)
{
    if ((handle == NULL) || (handle->stat == LL_I2C_STAT_DEINIT))
    {
        return LL_I2C_RES_ERR;
    }

    handle->rmap->cr1.r     = ll_i2c_regs_por.cr1.r;
    handle->rmap->cr2.r     = ll_i2c_regs_por.cr2.r;
    handle->rmap->oar1.r    = ll_i2c_regs_por.oar1.r;
    handle->rmap->oar2.r    = ll_i2c_regs_por.oar2.r;
    handle->rmap->timingr.r = ll_i2c_regs_por.timingr.r;
    handle->rmap->icr.r     = ll_i2c_regs_por.icr.r;

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

    if ((LL_I2C_REG_CR1(address) | LL_I2C_CR1_TXDMAEN_MASK) == 0x01)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_rxdma_enable(const uint32_t address)
{
    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_RXDMAEN_MASK;

    if ((LL_I2C_REG_CR1(address) | LL_I2C_CR1_RXDMAEN_MASK) == 0x01)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_txdma_disable(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_TXDMAEN_MASK);

    if ((LL_I2C_REG_CR1(address) | LL_I2C_CR1_TXDMAEN_MASK) == 0x00)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_rxdma_disable(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_RXDMAEN_MASK);

    if ((LL_I2C_REG_CR1(address) | LL_I2C_CR1_RXDMAEN_MASK) == 0x00)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}
