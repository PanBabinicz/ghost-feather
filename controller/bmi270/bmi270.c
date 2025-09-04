#include "bmi270.h"
#include "bmi270_conf.h"
#include "libopencm3/stm32/gpio.h"
#include "spi_ctrl.h"
#include <stdbool.h>
#include <string.h>

#define BMI270_US_TO_CYCLES(us)  ((uint32_t)((((us) * 10000) + 390624) / 390625))

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
    struct bmi270_acc_data data;                    /*!< The bmi270 accelerometer data.                     */
    struct bmi270_acc_conf conf;                    /*!< The bmi270 accelerometer configuration.            */
    struct bmi270_acc_rng  rng;                     /*!< The bmi270 accelerometer range.                    */
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
    struct bmi270_gyr_data data;                    /*!< The bmi270 gyroscope data.                         */
    struct bmi270_gyr_conf conf;                    /*!< The bmi270 gyroscope configuration.                */
    struct bmi270_gyr_rng  rng;                     /*!< The bmi270 gyroscope range.                        */
};

///
/// \brief The bmi270 temperature sensor instance type.
///
struct bmi270_temp
{
    int16_t data;                                   /*!< The temperature data.                              */
};

///
/// \brief The bmi270 sensor time instance type.
///
struct bmi270_time
{
    uint32_t reserved  : 8;                         /*!< Reserved.                                          */
    uint32_t data      : 24;                        /*!< The sensor time data.                              */
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
/// \brief The bmi270 device type.
///
struct bmi270_dev
{
    struct bmi270_acc   acc;                        /*!< The accelerometer instance.                        */
    struct bmi270_gyr   gyr;                        /*!< The gyroscope instance.                            */
    struct bmi270_temp  temp;                       /*!< The temperature sensor instance.                   */
    struct bmi270_time  time;                       /*!< The sensor time instance.                          */
    struct gpio_pair    gpio;                       /*!< The gpio pair.                                     */
    struct bmi270_conf  conf;                       /*!< The bmi270 config.                                 */
    struct spi_ctrl_dev *spi_ctrl;                  /*!< The spi controller device.                         */
    bool                stat;                       /*!< The status flag.                                   */
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
    .time = { 0 },
    .gpio =
    {
        .port = GPIOA,
        .pin  = GPIO4,
    },
    .conf =
    {
        .sz   = sizeof(bmi270_conf_file),
        .file = &bmi270_conf_file[0],
    },
    .spi_ctrl = NULL,
    .stat     = BMI270_STAT_DEINIT,
};

///
/// \breif The bmi270 power mode configuration look-up table.
///
static const struct bmi270_pwr_mode_conf bmi270_pwr_mode_confs[BMI270_PWR_MODE_TOTAL] =
{
    /* Suspend mode (lowest power mode). */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MSK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Configuration mode. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MSK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_OFF),
    },

    /* Low power mode. Accelerometer only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MSK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_ULP),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MSK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Low power mode. Gyroscope only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MSK | BMI270_GYR_FILT_PERF_MSK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_ULP),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MSK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Low power mode. IMU. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MSK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_ULP),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MSK | BMI270_GYR_FILT_PERF_MSK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_ULP),
        .pwr_conf_mask = (BMI270_PWR_CONF_APS_MSK),
        .pwr_conf_val  = (BMI270_PWR_CONF_APS_ON),
    },

    /* Normal mode. Accelerometer only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MSK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Normal mode. Gyroscope only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MSK | BMI270_GYR_FILT_PERF_MSK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_HP),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Normal mode. IMU. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MSK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MSK | BMI270_GYR_FILT_PERF_MSK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILT_PERF_HP),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Performance mode. Accelerometer only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MSK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (0x00),
        .gyr_conf_val  = (0x00),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Performance mode. Gyroscope only. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (0x00),
        .acc_conf_val  = (0x00),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MSK | BMI270_GYR_FILT_PERF_MSK),
        .gyr_conf_val  = (BMI270_GYR_NOISE_PERF_HP | BMI270_GYR_FILT_PERF_HP),
        .pwr_conf_mask = (0x00),
        .pwr_conf_val  = (0x00),
    },

    /* Performance mode. IMU. */
    {
        .pwr_ctrl_mask = (BMI270_PWR_CTRL_ACC_MSK | BMI270_PWR_CTRL_GYR_MSK),
        .pwr_ctrl_val  = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask = (BMI270_ACC_FILT_PERF_MSK),
        .acc_conf_val  = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask = (BMI270_GYR_NOISE_PERF_MSK | BMI270_GYR_FILT_PERF_MSK),
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
static bmi270_res_t bmi270_reg_read(const struct bmi270_dev *const dev, uint8_t adr, uint8_t *const buf,
                                    uint32_t sz);

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
static bmi270_res_t bmi270_reg_write(const struct bmi270_dev *const dev, uint8_t adr,
                                     const uint8_t *const buf, const uint32_t sz);

///
/// \breif Uploads the bmi270 configuration file.
///
/// \param[in] dev         The bmi270 device.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_upld_conf_file(const struct bmi270_dev *const dev);

///
/// \breif Validates the bmi270 configuration file.
///
/// \param[in] dev         The bmi270 device.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_vld_conf_file(const struct bmi270_dev *const dev);

///
/// \breif Delays execution for the specified number of bmi270 sensor time cycles.
///
/// \note  One cycle is equal to 39.0625us.
///
/// \param[in] dev         The bmi270 device.
/// \param[in] cycles      The number of cycles.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_wait_cycles(struct bmi270_dev *const dev, const uint32_t cycles);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static bmi270_res_t bmi270_reg_read(const struct bmi270_dev *const dev, uint8_t adr, uint8_t *const buf,
                                    uint32_t sz)
{
    /* Whether the device is NULL was checked before. */
    adr |= BMI270_OP_READ;

    /* The first byte is a dummy byte. Read two bytes. */
    sz  += 1;
    if (spi_ctrl_begin(dev->spi_ctrl, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_send(dev->spi_ctrl, &adr, sizeof(adr)) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_recv(dev->spi_ctrl, &buf[0], sz) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_end(dev->spi_ctrl, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

static bmi270_res_t bmi270_reg_write(const struct bmi270_dev *const dev, uint8_t adr,
                                     const uint8_t *const buf, const uint32_t sz)
{
    /* Whether the device is NULL was checked before. */
    uint8_t data[sz + 1];

    adr    |= BMI270_OP_WRITE;
    data[0] = adr;
    memcpy(&data[1], &buf[0], sz);
    if (spi_ctrl_begin(dev->spi_ctrl, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_send(dev->spi_ctrl, &data[0], sizeof(data)) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }
    if (spi_ctrl_end(dev->spi_ctrl, dev->gpio.port, dev->gpio.pin) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

static bmi270_res_t bmi270_upld_conf_file(const struct bmi270_dev *const dev)
{
    /* Whether the device is NULL was checked before. */
    uint8_t adr = BMI270_REG_INIT_DATA;

    if (bmi270_reg_write(dev, adr, dev->conf.file, dev->conf.sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

static bmi270_res_t bmi270_vld_conf_file(const struct bmi270_dev *const dev)
{
    /* Whether the device is NULL was checked before. */
    uint8_t adr = BMI270_REG_INIT_DATA;
    uint8_t buf[dev->conf.sz + 1];

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

static bmi270_res_t bmi270_wait_cycles(struct bmi270_dev *const dev, const uint32_t cycles)
{
    /* Whether the device is NULL was checked before. */
    uint32_t prev;
    uint32_t curr;

    if (bmi270_time_read(dev) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    prev = dev->time.data;

    do
    {
        if (bmi270_time_read(dev) != BMI270_RES_OK)
        {
            return BMI270_RES_ERR;
        }

        curr = dev->time.data;

        if (curr < prev)
        {
            /* Wrap around, the 24bit counter. */
            curr += 0x01000000;
        }
    } while ((curr - prev) < cycles);

    return BMI270_RES_OK;
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
struct bmi270_dev* bmi270_dev_get(void)
{
    return &bmi270;
}

const struct bmi270_pwr_mode_conf* bmi270_pwr_mode_get_conf(const bmi270_pwr_mode_t pwr_mode)
{
    if ((pwr_mode < BMI270_PWR_MODE_BEGIN) || (pwr_mode >= BMI270_PWR_MODE_TOTAL))
    {
        return NULL;
    }

    return &bmi270_pwr_mode_confs[pwr_mode];
}

bmi270_res_t bmi270_init(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr;
    uint8_t  buf[2] = { 0 };
    uint32_t sz;
    bool     spi_ctrl_stat;

    memset(&dev->acc,  0, sizeof(dev->acc));
    memset(&dev->gyr,  0, sizeof(dev->gyr));
    memset(&dev->temp, 0, sizeof(dev->temp));

    if (dev->spi_ctrl == NULL)
    {
        if (spi_ctrl_get_dev(&dev->spi_ctrl) == SPI_CTRL_RES_ERR)
        {
            return BMI270_RES_ERR;
        }
    }

    spi_ctrl_stat = spi_ctrl_get_stat(dev->spi_ctrl);

    if (spi_ctrl_stat == SPI_CTRL_STAT_DEINIT)
    {
        if (spi_ctrl_init(dev->spi_ctrl) == SPI_CTRL_RES_ERR)
        {
            return BMI270_RES_ERR;
        }
    }

    /* Read an arbitrary register of BMI270, discard the read response.
     * The MSB of the address is R/W indicator. */
    adr = BMI270_REG_CHIP_ID;
    sz  = 1;
    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Disable advanced power save mode: PWR_CONF.adv_power_save = 0x00. */
    adr    = BMI270_REG_PWR_CONF;
    buf[0] = 0;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Wait for 450us. */
    if (bmi270_wait_cycles(dev, BMI270_US_TO_CYCLES(450)) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Write INIT_CTRL.init_ctrl = 0x00 to prepare config load. */
    adr    = BMI270_REG_INIT_CTRL;
    buf[0] = 0;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
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
        return BMI270_RES_ERR;
    }

    /* Wait until internal status register contains the value 0b0001. */
    adr = BMI270_REG_INST;
    sz  = 1;
    while ((buf[1] & BMI270_INST_MSG_MSK) != BMI270_INST_MSG_INIT_OK)
    {
        if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
        {
            return BMI270_RES_ERR;
        }
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

/* TODO: Must not be performed while NVM writing operation is in progress. */
bmi270_res_t bmi270_soft_rst(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr = BMI270_REG_PWR_CONF;
    uint8_t  buf = BMI270_CMD_SOFTRESET;
    uint32_t sz  = 1;

    if (dev->stat != BMI270_STAT_DEINIT)
    {
        if (bmi270_reg_write(dev, adr, &buf, sz) != BMI270_RES_OK)
        {
            return BMI270_RES_ERR;
        }

        dev->stat = BMI270_STAT_DEINIT;
    }

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_pwr_mode_set(const struct bmi270_dev *const dev,
                                 const struct bmi270_pwr_mode_conf *const pwr_mode_conf)
{
    if ((dev == NULL) || (dev->spi_ctrl == NULL) || (pwr_mode_conf == NULL))
    {
        return BMI270_RES_ERR;
    }

    uint8_t pwr_ctrl_reg;
    uint8_t acc_conf_reg;
    uint8_t gyr_conf_reg;
    uint8_t pwr_conf_reg;

    uint8_t  adr;
    uint8_t  buf[3] = { 0 };
    uint32_t sz;

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
    pwr_conf_reg |=  (pwr_mode_conf->pwr_conf_val);

    pwr_ctrl_reg &= ~(pwr_mode_conf->pwr_ctrl_mask);
    pwr_ctrl_reg |=  (pwr_mode_conf->pwr_ctrl_val);

    acc_conf_reg &= ~(pwr_mode_conf->acc_conf_mask);
    acc_conf_reg |=  (pwr_mode_conf->acc_conf_val);

    gyr_conf_reg &= ~(pwr_mode_conf->gyr_conf_mask);
    gyr_conf_reg |=  (pwr_mode_conf->gyr_conf_val);

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

bmi270_res_t bmi270_spi_ctrl_asg(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    if (spi_ctrl_get_dev(&dev->spi_ctrl) != SPI_CTRL_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_stat_set(struct bmi270_dev *const dev, const bmi270_stat_t stat)
{
    if ((dev == NULL) || (stat < BMI270_STAT_BEGIN) || (stat >= BMI270_STAT_TOTAL))
    {
        return BMI270_RES_ERR;
    }

    dev->stat = stat;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_stat_get(const struct bmi270_dev *const dev, bmi270_stat_t *const stat)
{
    if ((dev == NULL) || (stat == NULL ))
    {
        return BMI270_RES_ERR;
    }

    *stat = dev->stat;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_slf_tst(struct bmi270_dev *const dev)
{
    if ((dev == NULL) || (dev->spi_ctrl == NULL))
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr;
    uint8_t  buf[2] = { 0 };
    uint32_t sz;

    int16_t pos_x, pos_y, pos_z;
    int16_t neg_x, neg_y, neg_z;

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

    /* Wait for > 2ms. */
    if (bmi270_wait_cycles(dev, BMI270_US_TO_CYCLES(2000)) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Set positive self-test polarity (ACC_SELF_TEST.acc_self_test_sign = 0x01). */
    adr    = BMI270_REG_ACC_SLF_TST;
    buf[0] = BMI270_ACC_SLF_TST_SIG_POS;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Enable self-test (ACC_SELF_TEST.acc_self_test_en = 0x01). */
    adr    = BMI270_REG_ACC_SLF_TST;
    buf[0] = BMI270_ACC_SLF_TST_EN_ON;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Wait for > 50ms. */
    if (bmi270_wait_cycles(dev, BMI270_US_TO_CYCLES(50000)) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Read and store positive acceleration value of each axis from registers DATA_8 to DATA_13. */
    bmi270_acc_read(dev);
    bmi270_acc_get_x(dev, &pos_x);
    bmi270_acc_get_y(dev, &pos_y);
    bmi270_acc_get_z(dev, &pos_z);

    /* Set negative self-test polarity (ACC_SELF_TEST.acc_self_test_sign = 0x00). */
    adr    = BMI270_REG_ACC_SLF_TST;
    buf[0] = BMI270_ACC_SLF_TST_SIG_NEG;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Enable self-test (ACC_SELF_TEST.acc_self_test_en = 0x01). */
    adr    = BMI270_REG_ACC_SLF_TST;
    buf[0] = BMI270_ACC_SLF_TST_EN_ON;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Wait for > 50ms. */
    if (bmi270_wait_cycles(dev, BMI270_US_TO_CYCLES(50000)) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Read and store negative acceleration value of each axis from registers DATA_8 to DATA_13. */
    bmi270_acc_read(dev);
    bmi270_acc_get_x(dev, &neg_x);
    bmi270_acc_get_y(dev, &neg_y);
    bmi270_acc_get_z(dev, &neg_z);

    /* TODO: Calculate difference of positive and negative acceleration values and compare against
     *       minimum difference signal values defined in the table below. */

    /* Disable self-test (ACC_SELF_TEST.acc_self_test_en = 0x01). */
    adr    = BMI270_REG_ACC_SLF_TST;
    buf[0] = BMI270_ACC_SLF_TST_EN_OFF;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_slf_tst(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr;
    uint8_t  buf[2] = { 0 };
    uint32_t sz;

    /* Issue a soft reset or a power-on reset. */
    if (bmi270_soft_rst(dev) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Initialize device. */
    if (bmi270_init(dev) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Disable APS PWR_CONF.adv_pwr_save = 0x00. */
    adr    = BMI270_REG_PWR_CONF;
    buf[0] = BMI270_PWR_CONF_APS_OFF;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Wait for 450us. */
    if (bmi270_wait_cycles(dev, BMI270_US_TO_CYCLES(450)) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Enable accelerometer PWR_CTRL.acc_en = 0x01. */
    adr    = BMI270_REG_PWR_CTRL;
    buf[0] = BMI270_PWR_CTRL_ACC_ON;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* Send g_trigger command using the register CMD. */
    adr    = BMI270_REG_CMD;
    buf[0] = BMI270_CMD_G_TRIGGER;
    sz     = 1;
    if (bmi270_reg_write(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    /* GYR_GAIN_STATUS.g_trig_status reports of a successful self-test or execution errors. */
    adr    = BMI270_REG_FEATURES_8;
    sz     = 1;
    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    if ((buf[1] & BMI270_GYR_GAIN_STAT_PRECON) ||
        (buf[1] & BMI270_GYR_GAIN_STAT_DL) ||
        (buf[1] & BMI270_GYR_GAIN_STAT_ABORT))
    {
        return BMI270_RES_ERR;
    }

    /* Self test is complete, after the device sets GYR_SELF_TEST_AXES.gyr_st_axes_done = 0x01. */
    adr    = BMI270_REG_GYR_SLF_TST_AXES;
    sz     = 1;
    while ((buf[1] & BMI270_GYR_SLF_TST_DONE_MSK) != BMI270_GYR_SLF_TST_DONE)
    {
        if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
        {
            return BMI270_RES_ERR;
        }
    }

    /* The test passed if all axes report the status "ok" by GYR_SELF_TEST_AXES.gyr_axis[xyz]_ok = 0x01. */
    if ((buf[1] & BMI270_GYR_SLF_TST_X_ERR) ||
        (buf[1] & BMI270_GYR_SLF_TST_Y_ERR) ||
        (buf[1] & BMI270_GYR_SLF_TST_Z_ERR))
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_read(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr    = BMI270_REG_DATA_8;
    uint8_t  buf[7] = { 0 };
    uint32_t sz     = 6;

    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    dev->acc.data.x = ((buf[2] << 0x08) | (buf[1] << 0x00));
    dev->acc.data.y = ((buf[4] << 0x08) | (buf[3] << 0x00));
    dev->acc.data.z = ((buf[6] << 0x08) | (buf[5] << 0x00));

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_get_x(const struct bmi270_dev *const dev, int16_t *const x)
{
    if ((dev == NULL) || (x == NULL))
    {
        return BMI270_RES_ERR;
    }

    *x = dev->acc.data.x;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_set_x(struct bmi270_dev *const dev, const int16_t x)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->acc.data.x = x;

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

bmi270_res_t bmi270_acc_set_y(struct bmi270_dev *const dev, const int16_t y)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->acc.data.y = y;

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

bmi270_res_t bmi270_acc_set_z(struct bmi270_dev *const dev, const int16_t z)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->acc.data.z = z;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_read(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr    = BMI270_REG_DATA_14;
    uint8_t  buf[7] = { 0 };
    uint32_t sz     = 6;

    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    dev->gyr.data.x = ((buf[2] << 0x08) | (buf[1] << 0x00));
    dev->gyr.data.y = ((buf[4] << 0x08) | (buf[3] << 0x00));
    dev->gyr.data.z = ((buf[6] << 0x08) | (buf[5] << 0x00));

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

bmi270_res_t bmi270_gyr_set_x(struct bmi270_dev *const dev, const int16_t x)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->gyr.data.x = x;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_get_y(const struct bmi270_dev *const dev, int16_t *const y)
{
    if ((dev == NULL) || (y == NULL))
    {
        return BMI270_RES_ERR;
    }

    *y = dev->gyr.data.y;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_set_y(struct bmi270_dev *const dev, const int16_t y)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->gyr.data.y = y;

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

bmi270_res_t bmi270_gyr_set_z(struct bmi270_dev *const dev, const int16_t z)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->gyr.data.z = z;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_temp_read(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr    = BMI270_REG_TEMPERATURE_0;
    uint8_t  buf[3] = { 0 };
    uint32_t sz     = 2;

    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    dev->temp.data = ((buf[2] << 0x08) | (buf[1] << 0x00));

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

bmi270_res_t bmi270_temp_set(struct bmi270_dev *const dev, int16_t temp)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->temp.data = temp;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_time_read(struct bmi270_dev *const dev)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t  adr    = BMI270_REG_SENSORTIME_0;
    uint8_t  buf[4] = { 0 };
    uint32_t sz     = 3;

    if (bmi270_reg_read(dev, adr, &buf[0], sz) != BMI270_RES_OK)
    {
        return BMI270_RES_ERR;
    }

    dev->time.data = ((buf[1] << 0x10) | (buf[2] << 0x08) | (buf[3] << 0x00));

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_time_get(const struct bmi270_dev *const dev, uint32_t *const time)
{
    if ((dev == NULL) || (time == NULL))
    {
        return BMI270_RES_ERR;
    }

    *time = dev->time.data;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_time_set(struct bmi270_dev *const dev, const uint32_t time)
{
    if (dev == NULL)
    {
        return BMI270_RES_ERR;
    }

    dev->time.data = time;

    return BMI270_RES_OK;
}
