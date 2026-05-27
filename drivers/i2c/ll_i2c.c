#include "ll_i2c.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ll_i2c_res_t ll_i2c_enable_periph(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_PE_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_PE_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_periph(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_PE_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_PE_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_software_reset(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_PE_MASK);

    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_PE_MASK) == 0x00)
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

    while ((LL_I2C_REG_ISR(address) & LL_I2C_ISR_RXNE_MASK) == 0x00);

    *byte = (uint8_t)LL_I2C_REG_RXDR(address);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_transmit(const uint32_t address, const uint8_t *const byte)
{
    if (byte == NULL)
    {
        return LL_I2C_RES_ERR;
    }

    while ((LL_I2C_REG_ISR(address) & LL_I2C_ISR_TXE_MASK) == 0x00);

    LL_I2C_REG_TXDR(address) = *byte;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_txdma(const uint32_t address)
{
    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_TXDMAEN_MASK;

    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_TXDMAEN_MASK) == 0x01)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_disable_txdma(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_TXDMAEN_MASK);

    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_TXDMAEN_MASK) == 0x00)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_enable_rxdma(const uint32_t address)
{
    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_RXDMAEN_MASK;

    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_RXDMAEN_MASK) == 0x01)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_disable_rxdma(const uint32_t address)
{
    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_RXDMAEN_MASK);

    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_RXDMAEN_MASK) == 0x00)
    {
        return LL_I2C_RES_OK;
    }

    return LL_I2C_RES_ERR;
}

ll_i2c_res_t ll_i2c_enable_interrupt(const uint32_t address, const ll_i2c_interrupt_t interrupt)
{
    if ((interrupt < LL_I2C_INTERRUPT_TX) || (interrupt > LL_I2C_INTERRUPT_ERR))
    {
        return LL_I2C_RES_ERR;
    }
    else if ((LL_I2C_REG_CR1(address) & (0x01 << interrupt)) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= (0x01 << interrupt);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_interrupt(const uint32_t address, const ll_i2c_interrupt_t interrupt)
{
    if ((interrupt < LL_I2C_INTERRUPT_TX) || (interrupt > LL_I2C_INTERRUPT_TX))
    {
        return LL_I2C_RES_ERR;
    }
    else if ((LL_I2C_REG_CR1(address) & (0x01 << interrupt)) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(0x01 << interrupt);

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

ll_i2c_res_t ll_i2c_enable_anf(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_ANFOFF_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_ANFOFF_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_anf(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_ANFOFF_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_ANFOFF_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_sbc(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_SBC_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_SBC_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_sbc(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_SBC_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_SBC_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_clk_stretch(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_NOSTRETCH_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_NOSTRETCH_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_clk_stretch(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_NOSTRETCH_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_NOSTRETCH_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_general_call(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_GCEN_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_GCEN_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_general_call(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_GCEN_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_GCEN_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_smbh(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_SMBHEN_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_SMBHEN_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_smbh(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_SMBHEN_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_SMBHEN_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_smbd(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_SMBDEN_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_SMBDEN_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_smbd(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_SMBDEN_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_SMBDEN_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_alert(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_ALERTEN_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_ALERTEN_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_alert(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_ALERTEN_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_ALERTEN_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_enable_pec(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_PECEN_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) |= LL_I2C_CR1_PECEN_MASK;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_disable_pec(const uint32_t address)
{
    if ((LL_I2C_REG_CR1(address) & LL_I2C_CR1_PECEN_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR1(address) &= ~(LL_I2C_CR1_PECEN_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_set_addr_7bit(const uint32_t address, const uint32_t 7bit_addr)
{
    if ((LL_I2C_REG_CR2(address) & LL_I2C_CR2_START_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR2(address) &= ~(LL_I2C_CR2_ADD10_MASK);
    LL_I2C_REG_CR2(address) &= ~(0x00fe);
    LL_I2C_REG_CR2(address) |= (7bit_addr & 0x07f) << 0x01;

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_set_addr_10bit(const uint32_t address, const uint32_t 10bit_addr)
{
    if ((LL_I2C_REG_CR2(address) & LL_I2C_CR2_START_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR2(address) |= LL_I2C_CR2_ADD10_MASK;
    LL_I2C_REG_CR2(address) &= ~(0x03ff);
    LL_I2C_REG_CR2(address) |= (10bit_addr & 0x03ff);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_set_xfer_dir_write(const uint32_t address)
{
    if ((LL_I2C_REG_CR2(address) & LL_I2C_CR2_START_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }
    else if ((LL_I2C_REG_CR2(address) & LL_I2C_CR2_RDWRN_MASK) == 0x00)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR2(address) &= ~(LL_I2C_CR2_RDWRN_MASK);

    return LL_I2C_RES_OK;
}

ll_i2c_res_t ll_i2c_set_xfer_dir_read(const uint32_t address)
{
    if ((LL_I2C_REG_CR2(address) & LL_I2C_CR2_START_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }
    else if ((LL_I2C_REG_CR2(address) & LL_I2C_CR2_RDWRN_MASK) == 0x01)
    {
        return LL_I2C_RES_ERR;
    }

    LL_I2C_REG_CR2(address) |= LL_I2C_CR2_RDWRN_MASK;

    return LL_I2C_RES_OK;
}
