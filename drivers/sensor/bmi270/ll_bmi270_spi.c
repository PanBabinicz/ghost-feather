#include "ll_bmi270_spi.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/spi.h"

#define BMI270_OP_WRITE (0x00 << 0x07)  /*!< The write operation indicator */
#define BMI270_OP_READ  (0x01 << 0x07)  /*!< The read operation indicator  */

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
uint8_t ll_bmi270_spi_reg_xfer_byte(const struct ll_bmi270_spi_conf *const conf, const uint8_t data)
{
    uint8_t byte;

    spi_send8(conf->spi, data);
    byte = spi_read8(conf->spi);

    return byte;
}

void ll_bmi270_spi_reg_read_byte(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        uint8_t *const byte)
{
    uint8_t dummy = 0x00;

    addr |= BMI270_OP_READ;

    gpio_clear(conf->cs_port, conf->cs_pin);
    spi_enable(conf->spi);

    ll_bmi270_spi_reg_xfer_byte(conf, addr);
    ll_bmi270_spi_reg_xfer_byte(conf, dummy);
    *byte = ll_bmi270_spi_reg_xfer_byte(conf, dummy);

    spi_disable(conf->spi);
    gpio_set(conf->cs_port, conf->cs_pin);
}

void ll_bmi270_spi_reg_read_mult_bytes(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        uint8_t *const buf, uint32_t sz)
{
    uint8_t dummy = 0x00;

    addr |= BMI270_OP_READ;

    gpio_clear(conf->cs_port, conf->cs_pin);
    spi_enable(conf->spi);

    ll_bmi270_spi_reg_xfer_byte(conf, addr);
    ll_bmi270_spi_reg_xfer_byte(conf, dummy);

    for (uint32_t i = 0; i < sz; i++)
    {
        buf[i] = ll_bmi270_spi_reg_xfer_byte(conf, dummy);
    }

    spi_disable(conf->spi);
    gpio_set(conf->cs_port, conf->cs_pin);
}

void ll_bmi270_spi_reg_write_byte(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        const uint8_t byte)
{
    addr |= BMI270_OP_WRITE;

    gpio_clear(conf->cs_port, conf->cs_pin);
    spi_enable(conf->spi);

    ll_bmi270_spi_reg_xfer_byte(conf, addr);
    ll_bmi270_spi_reg_xfer_byte(conf, byte);

    spi_disable(conf->spi);
    gpio_set(conf->cs_port, conf->cs_pin);
}

void ll_bmi270_spi_reg_write_mult_bytes(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        const uint8_t *const buf, const uint32_t sz)
{
    addr |= BMI270_OP_WRITE;

    gpio_clear(conf->cs_port, conf->cs_pin);
    spi_enable(conf->spi);

    ll_bmi270_spi_reg_xfer_byte(conf, addr);
    for (uint32_t i = 0; i < sz; i++)
    {
        ll_bmi270_spi_reg_xfer_byte(conf, buf[i]);
    }

    spi_disable(conf->spi);
    gpio_set(conf->cs_port, conf->cs_pin);
}
