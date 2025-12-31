#ifndef _LL_BMI270_H
#define _LL_BMI270_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/// TODO
/// \brief
///
struct ll_bmi270_spi_conf
{
    uint32_t spi;
    uint32_t cs_pin;
    uint32_t cs_port;
};

/// TODO
/// \brief Exchanges a single byte of data with a BMI270 register. Performs a write and read transaction for
///        one 8-bit register on the BMI270 over the configured SPI interface.
///
/// \param[in] dev  The bmi270 device.
/// \param[in] data The date to be send (8-bits).
///
/// \return uint8_t The read byte from bmi270 register.
///
uint8_t ll_bmi270_spi_reg_xfer_byte(const struct ll_bmi270_spi_conf *const conf, const uint8_t data);

/// TODO
/// \brief Reads byte from BMI270 register.
///
/// \param[in]  dev        The bmi270 device.
/// \param[in]  addr       The bmi270 register address.
/// \param[out] byte       The read byte (8-bits).
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
void ll_bmi270_spi_reg_read_byte(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        uint8_t *const byte);

/// TODO
/// \brief Reads bytes from the multiple consecutive BMI270 registers.
///        The BMI270 automatically increments the register address after each read.
///
/// \param[in]  dev        The bmi270 device.
/// \param[in]  addr       The bmi270 register address.
/// \param[out] buf        The read buffer.
/// \param[in]  sz         The read buffer size.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
void ll_bmi270_spi_reg_read_mult_bytes(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        uint8_t *const buf, uint32_t sz);

/// TODO
/// \brief Writes byte to the bmi270 register.
///
/// \param[in] dev         The bmi270 device.
/// \param[in] addr        The bmi270 register address.
/// \param[in] byte        The byte (8-bits) to be written.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
void ll_bmi270_spi_reg_write_byte(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        const uint8_t byte);

/// TODO
/// \brief Writes multiple bytes for consecutive addresses of the BMI270.
///        The BMI270 automatically increments the register address after each write.
///
/// \param[in] dev         The bmi270 device.
/// \param[in] addr        The bmi270 register address.
/// \param[in] buf         The bytes to be written to registers.
/// \param[in] sz          The buffer size.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
void ll_bmi270_spi_reg_write_mult_bytes(const struct ll_bmi270_spi_conf *const conf, uint8_t addr,
        const uint8_t *const buf, const uint32_t sz);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _LL_BMI270_H */
