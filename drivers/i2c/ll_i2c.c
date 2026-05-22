#include "ll_i2c.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ll_i2c_res_t ll_i2c_periph_enable(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) | LL_I2C_CR1_PE_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_PE_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_periph_disable(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) | LL_I2C_CR1_PE_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_PE_MASK);

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

ll_i2c_res_t ll_i2c_interrupt_enable(const uint32_t address, const ll_i2c_cr1_mask interrupt)
{
    if ((interrupt < LL_I2C_CR1_TXIE_MASK) || (interrupt > LL_I2C_CR1_ERRIE_MASK))
    {
        return LL_I2C_RES_ERR;
    }
    else if ((LL_I2C_REG_CR1(address) | interrupt) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= interrupt;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_interrupt_disable(const uint32_t address, const ll_i2c_cr1_mask interrupt)
{
    if ((interrupt < LL_I2C_CR1_TXIE_MASK) || (interrupt > LL_I2C_CR1_ERRIE_MASK))
    {
        return LL_I2C_RES_ERR;
    }
    else if ((LL_I2C_REG_CR1(address) | interrupt) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(interrupt);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_set_dnf(const uint32_t address, const ll_i2c_dnf_t dnf)
{
    if ((dnf < LL_I2C_DNF_DISABLE) || (dnf > LL_I2C_DNF_15TCLK))
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= (dnf << LL_I2C_CR1_DNF_MASK);

    return LL_I2C_RES_OK;
}
