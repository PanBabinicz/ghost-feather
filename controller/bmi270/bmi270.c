#include "bmi270.h"
#include "bmi270_conf.h"
#include "spi_ctrl.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The bmi270 accelerometer data type.
///
struct bmi270_acc_data
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
};

///
/// \brief The bmi270 accelerometer config type.
///
struct bmi270_acc_conf
{
    uint8_t filt_perf  : 1;                         /*!< The filter performance mode.                       */
    uint8_t bwp        : 3;                         /*!< The bandwidth.                                     */
    uint8_t odr        : 4;                         /*!< The output data rate.                              */
};

///
/// \brief The bmi270 accelerometer range type.
///
struct bmi270_acc_rng
{
    uint8_t reserved   : 6;                         /*!< Reserved.                                          */
    uint8_t acc_rng    : 2;                         /*!< The accelerometer g-range.                         */
};

///
/// \brief The bmi270 accelerometer instance type.
///
struct bmi270_acc
{
    bmi270_acc_data_t data;                         /*!< The bmi270 accelerometer data.                     */
    bmi270_acc_conf_t conf;                         /*!< The bmi270 accelerometer configuration.            */
    bmi270_acc_rng_t  rng;                          /*!< The bmi270 accelerometer range.                    */
};

///
/// \brief The bmi270 gyroscope data type.
///
struct bmi270_gyr_data
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
};

///
/// \brief The bmi270 gyroscope config type.
///
struct bmi270_gyr_conf
{
    uint8_t filt_perf  : 1;                         /*!< The filter performance mode.                       */
    uint8_t noise_perf : 1;                         /*!< The noise performance mode.                        */
    uint8_t bwp        : 2;                         /*!< The bandwidth coefficient.                         */
    uint8_t odr        : 4;                         /*!< The output data rate.                              */
};

///
/// \brief The bmi270 gyroscope range type.
///
struct bmi270_gyr_rng
{
    uint8_t reserved   : 4;                         /*!< Reserved.                                          */
    uint8_t ois_rng    : 1;                         /*!< Pre-filtered FIFO data and OIS data.               */
    uint8_t gyr_rng    : 3;                         /*!< Filtered FIFO data and DATA registers.             */
};

///
/// \brief The bmi270 gyroscope instance type.
///
struct bmi270_gyr
{
    bmi270_gyr_data_t data;                         /*!< The bmi270 gyroscope data.                         */
    bmi270_gyr_conf_t conf;                         /*!< The bmi270 gyroscope configuration.                */
    bmi270_gyr_rng_t  rng;                          /*!< The bmi270 gyroscope range.                        */
};

///
/// \brief The bmi270 temperature sensor instance type.
///
struct bmi270_temp
{
    uint16_t data;                                  /*!< The temperature data.                              */
};

///
/// \brief The gpio pair type.
///
struct gpio_pair
{
    uint32_t port;                                  /*!< The gpio port identifier.                          */
    uint16_t pin;                                   /*!< The gpio pin identifier.                           */
};

///
/// \brief The bmi270 configuration type.
///
struct bmi270_conf
{
    uint32_t      sz;                               /*!< The bmi270 config file size.                       */
    const uint8_t *file;                            /*!< The bmi270 config file.                            */
};

///
/// \brief The bmi270 instance type.
///
struct bmi270_dev
{
    struct bmi270_acc  acc;                         /*!< The accelerometer instance.                        */
    struct bmi270_gyr  gyr;                         /*!< The gyroscope instance.                            */
    struct bmi270_temp temp;                        /*!< The temperature sensor instance.                   */
    struct gpio_pair   gpio;                        /*!< The gpio pair.                                     */
    struct bmi270_conf conf;                        /*!< The bmi270 config.                                 */
    struct spi_ctrl    *spi_ctrl_inst               /*!< The spi controller instance.                       */
    bool               stat;                        /*!< The status flag.                                   */
};

///
/// \breif The bmi270 power mode config type.
///
struct bmi270_pwr_mode_conf
{
    uint8_t pwr_ctrl_mask;
    uint8_t pwr_ctrl_val;
    uint8_t acc_conf_mask;
    uint8_t acc_conf_val;
    uint8_t gyr_conf_mask;
    uint8_t gyr_conf_val;
    uint8_t pwr_conf_mask;
    uint8_t pwr_conf_val;
};

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************

///
/// \breif The bmi270 device.
///
static struct bmi270_dev bmi270 =
{
    .acc  = { 0 },
    .gyr  = { 0 },
    .temp = { 0 },
    .gpio =
    {
        .port = GPIOA,
        .pin  = GPIO4,
    },
    .conf =
    {
        .sz   = sizeof(bmi270_config_file);
        .file = &bmi270_config_file[0];
    }
    .spi_ctrl_inst = NULL,
    .init = BMI270_STAT_DEINIT,
};

///
/// \breif The bmi270 power mode configuration look-up table.
///
static const struct bmi270_pwr_mode_conf bmi270_pwr_mode_confs[BMI270_PWR_MODE_TOTAL] =
{
    /* Suspend mode (lowest power mode). */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Configuration mode. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_OFF),
    },

    /* Low power mode. Accelerometer only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_ULP),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Low power mode. Gyroscope only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILT_PERF_MASK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_ULP),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Low power mode. IMU. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_ULP),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILT_PERF_MASK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_ULP),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Normal mode. Accelerometer only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Normal mode. Gyroscope only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILT_PERF_MASK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_HP),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Normal mode. IMU. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILT_PERF_MASK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_HP),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Performance mode. Accelerometer only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Performance mode. Gyroscope only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILT_PERF_MASK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_HP | BMI270_GYR_FILT_PERF_HP),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Performance mode. IMU. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILT_PERF_MASK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_HP | BMI270_GYR_FILT_PERF_HP),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },
};

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \breif Reads the register data from bmi270.
///
/// \param[in]  dev        The bmi270 device.
/// \param[in]  adr        The bmi270 register address.
/// \param[out] buf        The read buffer.
/// \param[in]  sz         The read buffer size.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_reg_read(const struct bmi270_dev *const dev, const uint8_t adr, uint8_t *const buf,
                                    const uint32_t sz);

///
/// \breif Writes data to the bmi270 register.
///
/// \param[in] dev         The bmi270 device.
/// \param[in] adr         The bmi270 register address.
/// \param[in] buf         The write buffer.
/// \param[in] sz          The write buffer size.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_reg_write(const struct bmi270_dev *const dev, const uint8_t adr,
                                     const uint8_t *const buf, const uint32_t sz);

///
/// \breif Performs power-on-reset (POR).
///
/// \param[in] dev         The bmi270 device.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_por(const struct bmi270_dev *const dev);

///
/// \breif Uploads the bmi270 configuration file.
///
/// \param[in] dev         The bmi270 device.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_upld_conf_file(const bm270_dev *const dev);

///
/// \breif Validates the bmi270 configuration file.
///
/// \param[in] dev         The bmi270 device.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_vld_conf_file(const bm270_dev *const dev);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static bmi270_res_t bmi270_reg_read(const struct bmi270_dev *const dev, const uint8_t adr, uint8_t *const buf,
                                    const uint32_t sz)
{
    /* Whether the device is NULL was checked before. */
    adr |= BMI270_OP_READ;

    /* The first byte is a dummy byte. Read two bytes. */
    sz  += 1;
    if (spi_ctrl_begin(dev->spi_ctrl_inst, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_send(dev->spi_ctrl_inst, &adr, sizeof(adr)) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_recv(dev->spi_ctrl_inst, &buf[0], sz) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_end(dev->spi_ctrl_inst, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

static bmi270_res_t bmi270_reg_write(const struct bmi270_dev *const dev, const uint8_t adr,
                                     const uint8_t *const buf, const uint32_t sz)
{
    /* Whether the device is NULL was checked before. */
    uint8_t data[sz + 1];

    adr    |= BMI270_OP_WRITE;
    data[0] = adr;
    memcpy(&data[1], &buf[0], sz);
    if (spi_ctrl_begin(dev->spi_ctrl_inst, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_send(dev->spi_ctrl_inst, &data[0], sizeof(data)) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_end(dev->spi_ctrl_inst, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

static bmi270_res_t bmi270_por(const struct bmi270_dev *const dev)
{
    /* Whether the device is NULL was checked before. */

    uint8_t  adr;
    uint8_t  buf[2] = { 0 };
    uint32_t sz;

    /* Read an arbitrary register of BMI270, discard the read response.
     * The MSB of the address is R/W indicator. */
    adr = BMI270_REG_CHIP_ID;
    sz  = 1;
    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        retrun BMI270_RES_ERR;
    }

    /* Disable advanced power save mode: PWR_CONF.adv_power_save = 0x00. */
    adr    = BMI270_REG_PWR_CONF;
    buf[0] = 0x00;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        retrun BMI270_RES_ERR;
    }

    /* Wait for 450us (12 LSB of SENSORTIME_0). */
    adr = BMI270_REG_SENSORTIME_0;
    sz  = 1;
    while (buf[1] < 12)
    {
        if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
        {
            retrun BMI270_RES_ERR;
        }
    }

    /* Write INIT_CTRL.init_ctrl = 0x00 to prepare config load. */
    adr    = BMI270_REG_INIT_CTRL;
    buf[0] = 0x00;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        retrun BMI270_RES_ERR;
    }

    /* Upload configuration file. */
    if (bmi270_upld_conf_file(dev) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }
#if (defined(BMI270_VLD_CONF_FILE) && (BMI270_VLD_CONF_FILE == 1))
    /* Optionally: Check config file correctness by comparing it to data written to the register
     * in previous step. */
    if (bmi270_vld_conf_file(dev) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }
#endif

    /* Write INIT_CTRL.init_ctrl = 0x01 to complete config load.
     * NOTE: This operation must not be performed more than once after POR
     *       or soft reset. */
    adr    = BMI270_REG_INIT_CTRL;
    buf[0] = 0x01;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        retrun BMI270_RES_ERR;
    }

    /* Wait until internal status register contains the value 0b0001. */
    adr = BMI270_REG_INTERNAL_STATUS;
    sz  = 1;
    while ((buf[1] & BMI270_INST_MSG_MSK) != BMI270_INST_MSG_INIT_OK)
    {
        if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
        {
            retrun BMI270_RES_ERR;
        }
    }

    return BMI270_RES_OK;
}

static bmi270_res_t bmi270_upld_conf_file(const bm270_dev *const dev)
{
    /* Whether the device is NULL was checked before. */
    if (dev->spi_ctrl_inst->stat != SPI_CTRL_STAT_RUN)
    {
        return BMI270_RES_ERR;
    }

    uint8_t adr = BMI270_REG_INIT_DATA;

    if (bmi270_reg_write(dev, adr, dev->conf.file, dev->conf.sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

static bmi270_res_t bmi270_vld_conf_file(const bm270_dev *const dev)
{
    /* Whether the device is NULL was checked before. */
    if (dev->spi_ctrl_inst->stat != SPI_CTRL_STAT_RUN)
    {
        return BMI270_RES_ERR;
    }

    uint8_t adr = BMI270_REG_INIT_DATA;
    uint8_t buf[dev->conf.sz + 1] = { 0 };

    if (bmi270_reg_read(dev, adr, &buf[0], sizeof(buf)) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    if (memcmp(dev->conf.file, &buf[1], dev->conf.sz) != 0)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
struct bmi270_dev* bmi270_get_dev(void)
{
    return &bmi270;
}

const bmi270_pwr_mode_conf_t* bmi270_get_pwr_mode_conf(const bmi270_pwr_mode_t pwr_mode)
{
    if ((pwr_mode < BMI270_PWR_MODE_BEGIN) || (pwr_mode >= BMI270_PWR_MODE_TOTAL))
    {
        return NULL;
    }

    return &bmi270_pwr_mode_confs[pwr_mode];
}

bmi270_res_t bmi270_init(struct bmi270_dev *const dev);
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    memset(&dev->acc,  0, sizeof(dev->acc));
    memset(&dev->gyr,  0, sizeof(dev->gyr));
    memset(&dev->temp, 0, sizeof(dev->temp));

    if (dev->spi_ctrl_inst == NULL)
    {
        if (spi_ctrl_get_inst(dev->spi_ctrl_inst) == SPI_CTRL_RES_ERR)
        {
            return BMI270_RES_ERR;
        }
    }

    if (dev->spi_ctrl_inst->stat == SPI_CTRL_STAT_DEINIT)
    {
        if (spi_ctrl_init(dev->spi_ctrl_inst) == SPI_CTRL_RES_ERR)
        {
            return BMI270_RES_ERR;
        }
    }

    if (bmi270_por(dev) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    dev->stat = BMI270_STAT_INIT;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_deinit(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->stat = BMI270_STAT_DEINIT;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_set_pwr_mode(const struct bmi270_dev *const dev,
                                 const struct bmi270_pwr_mode_conf *const pwr_mode_conf)
{
    if ((pwr_mode_conf == NULL) || (dev->spi_ctrl_inst == NULL))
    {
        return BMI270_RES_ERR;
    }

    uint8_t pwr_ctrl_reg;
    uint8_t acc_conf_reg;
    uint8_t gyr_conf_reg;
    uint8_t pwr_conf_reg;

    uint8_t buf[3] = { 0 };
    uint8_t adr;
    uint8_t sz;

    /* Read the PWR_CONF and PWR_CTRL registers values. */
    adr = BMI270_REG_PWR_CONF;
    sz  = 2;
    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    else
    {
        pwr_conf_reg = buf[1];
        pwr_ctrl_reg = buf[2];
    }

    /* Read the ACC_CONF register value. */
    adr = BMI270_REG_ACC_CONF;
    sz  = 1;
    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    else
    {
        acc_conf_reg = buf[1];
    }

    /* Read the GYR_CONF register value. */
    adr = BMI270_REG_GYR_CONF;
    sz  = 1;
    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    else
    {
        gyr_conf_reg = buf[1];
    }

    pwr_conf_reg &= ~(pwr_mode_conf->pwr_conf_mask);
    pwr_conf_reg |=  (pwr_mode_conf->pwr_conf_value);

    pwr_ctrl_reg &= ~(pwr_mode_conf->pwr_ctrl_mask);
    pwr_ctrl_reg |=  (pwr_mode_conf->pwr_ctrl_value);

    acc_conf_reg &= ~(pwr_mode_conf->acc_conf_mask);
    acc_conf_reg |=  (pwr_mode_conf->acc_conf_value);

    gyr_conf_reg &= ~(pwr_mode_conf->gyr_conf_mask);
    gyr_conf_reg |=  (pwr_mode_conf->gyr_conf_value);

    /* Write the PWR_CONF and PWR_CTRL registers values. */
    adr    = BMI270_REG_PWR_CONF;
    buf[0] = pwr_conf_reg;
    buf[1] = pwr_ctrl_reg;
    sz     = 2;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Write the ACC_CONF register value. */
    adr    = BMI270_REG_ACC_CONF;
    buf[0] = acc_conf_reg;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Write the GYR_CONF register value. */
    adr    = BMI270_REG_ACC_CONF;
    buf[0] = gyr_conf_reg;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

/* TODO: Finished here. */

bmi270_res_t bmi270_acc_slf_tst(const struct bmi270_dev *const dev)
{
    if ((dev == NULL) || (dev->spi_ctrl_inst == NULL))
    {
        return BMI270_RES_ERR;
    }

    uint8_t adr;
    uint8_t sz;
    uint8_t buf[2];

    /* Enable accelerometer with register PWR_CTRL.acc_en = 0x01. */
    adr    = BMI270_REG_PWR_CTRL;
    buf[0] = 1;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Set +/-16g range in register ACC_RANGE.acc_range. */
    adr    = BMI270_REG_ACC_RANGE;
    buf[0] = BMI270_ACC_RANGE_16G;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Set self test amplitude to high by settign ACC_SELF_TEST.acc_self_test_amp = 0x01. */
    adr    = BMI270_REG_ACC_SLF_TST;
    buf[0] = BMI270_ACC_SLF_TST_AMP_HIGH;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_slf_tst(void)
{
    /* TODO: The gyroscope self-test, needs spi. */
}

bmi270_res_t bmi270_acc_read(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    /* TODO: Read the accelerometer data via spi. */
    dev->acc.data.x =
    dev->acc.data.y =
    dev->acc.data.z =

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_get_x(const struct bmi270_dev *const dev, int16_t *const x);
{
    if ((dev == NULL) || (x == NULL))
    {
        return BMI270_RES_ERR;
    }

    *x = dev->acc.data.x;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_get_y(const struct bmi270_dev *const dev, int16_t *const y)
{
    if ((dev == NULL) || (y == NULL))
    {
        return BMI270_RES_ERR;
    }

    *y = dev->acc.data.y;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_get_z(const struct bmi270_dev *const dev, int16_t *const z)
{
    if ((dev == NULL) || (z == NULL))
    {
        return BMI270_RES_ERR;
    }

    *z = dev->acc.data.z;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_read(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    /* TODO: Read the gyroscope data via spi. */
    dev->gyr.data.x =
    dev->gyr.data.y =
    dev->gyr.data.z =

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_get_x(const struct bmi270_dev *const dev, int16_t *const x)
{
    if ((dev == NULL) || (x == NULL))
    {
        return BMI270_RES_ERR;
    }

    *x = dev->gyr.data.x;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_get_y(const struct bmi270_dev *const dev, int16_t *const y)
{
    if ((inst == NULL) || (y == NULL))
    {
        return BMI270_RES_ERR;
    }

    *y = inst->gyr.data.y;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_get_z(const struct bmi270_dev *const dev, int16_t *const z)
{
    if ((dev == NULL) || (z == NULL))
    {
        return BMI270_RES_ERR;
    }

    *z = dev->gyr.data.z;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_temp_read(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    /* TODO: Read the temperature data via spi. */
    dev->temp.data =

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_temp_get(const struct bmi270_dev *const dev, int16_t *const temp)
{
    if ((dev == NULL) || (temp == NULL))
    {
        return BMI270_RES_ERR;
    }

    *temp = dev->temp.data;

    return BMI270_RES_OK;
}
