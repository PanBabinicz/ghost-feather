#include "bmi270.h"
#include "bmi270_conf.h"
#include "ll_bmi270_spi.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/spi.h"
#include "timing.h"
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
    struct bmi270_acc  acc;                         /*!< The accelerometer instance.                        */
    struct bmi270_gyr  gyr;                         /*!< The gyroscope instance.                            */
    struct bmi270_temp temp;                        /*!< The temperature sensor instance.                   */
    struct bmi270_time time;                        /*!< The sensor time instance.                          */
    struct ll_bmi270_spi_conf spi_conf;             /*!< The spi configuration structure.                   */
    struct bmi270_conf conf;                        /*!< The bmi270 config.                                 */
    bool stat;                                      /*!< The status flag.                                   */
};

///
/// \brief The bmi270 power mode config type.
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
/// \brief The bmi270 device.
///
static struct bmi270_dev bmi270 =
{
    .acc  = { 0 },
    .gyr  = { 0 },
    .temp = { 0 },
    .time = { 0 },
    .spi_conf =
    {
        .spi     = SPI1,
        .cs_port = GPIOA,
        .cs_pin  = GPIO4,
    },
    .conf =
    {
        .sz   = sizeof(bmi270_conf_file),
        .file = &bmi270_conf_file[0],
    },
    .stat = BMI270_STAT_DEINIT,
};

///
/// \brief The bmi270 power mode configuration look-up table.
///
static const struct bmi270_pwr_mode_conf bmi270_pwr_mode_conf_arr[BMI270_PWR_MODE_TOTAL] =
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
/// \brief Uploads the bmi270 configuration file.
///
/// \param[in] dev         The bmi270 device.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static void bmi270_upld_conf_file(const struct bmi270_dev *const dev);

///
/// \brief Validates the bmi270 configuration file.
///
/// \param[in] dev         The bmi270 device.
///
/// \return bmi270_res_t   The bmi270 result.
/// \retval BMI270_RES_OK  On success.
/// \retval BMI270_RES_ERR Otherwise.
///
static bmi270_res_t bmi270_vld_conf_file(const struct bmi270_dev *const dev);

///
/// \brief Delays execution for the specified number of bmi270 sensor time cycles.
///
/// \note  One cycle is equal to 39.0625us.
///
/// \param[in] dev         The bmi270 device.
/// \param[in] cycles      The number of cycles.
///
static void bmi270_wait_cycles(struct bmi270_dev *const dev, const uint32_t cycles);

///
/// \brief Sends given command to the bmi270 device.
///
/// \param[in] dev         The bmi270 device.
/// \param[in] cmd         The bmi270 command to be sent.
///
static void bmi270_cmd_send(struct bmi270_dev *const dev, const uint8_t cmd);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static void bmi270_upld_conf_file(const struct bmi270_dev *const dev)
{
    /* Whether the device is NULL was checked before. */
    uint8_t adr = BMI270_REG_INIT_DATA;
    ll_bmi270_spi_reg_write_mult_bytes(&dev->spi_conf, adr, dev->conf.file, dev->conf.sz);
}

static bmi270_res_t bmi270_vld_conf_file(const struct bmi270_dev *const dev)
{
    /* Whether the device is NULL was checked before. */
    uint8_t addr = BMI270_REG_INIT_DATA;
    uint8_t buf[dev->conf.sz];

    ll_bmi270_spi_reg_read_mult_bytes(&dev->spi_conf, addr, &buf[0], sizeof(buf));

    if (memcmp(dev->conf.file, &buf[0], dev->conf.sz) != 0)
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

static void bmi270_wait_cycles(struct bmi270_dev *const dev, const uint32_t cycles)
{
    /* Whether the device is NULL was checked before. */
    uint32_t prev;
    uint32_t curr;

    bmi270_time_read();

    prev = dev->time.data;
    do
    {
        bmi270_time_read();

        curr = dev->time.data;
        if (curr < prev)
        {
            /* Wrap around, the 24bit counter. */
            curr += 0x01000000;
        }
    } while ((curr - prev) < cycles);
}

static void bmi270_cmd_send(struct bmi270_dev *const dev, const uint8_t cmd)
{
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, BMI270_REG_CMD, cmd);
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

    return &bmi270_pwr_mode_conf_arr[pwr_mode];
}

bmi270_res_t bmi270_init(void)
{
    struct bmi270_dev *dev = &bmi270;

    uint8_t addr;
    uint8_t byte;

    memset(&dev->acc,  0, sizeof(dev->acc));
    memset(&dev->gyr,  0, sizeof(dev->gyr));
    memset(&dev->temp, 0, sizeof(dev->temp));

    /* Read an arbitrary register of BMI270, discard the read response.
     * The MSB of the address is R/W indicator. */
    addr = BMI270_REG_CHIP_ID;
    ll_bmi270_spi_reg_read_byte(&dev->spi_conf, addr, &byte);
    if (byte != BMI270_POR_CHIP_ID)
    {
        return BMI270_RES_ERR;
    }

    /* Disable advanced power save mode: PWR_CONF.adv_power_save = 0x00. */
    addr = BMI270_REG_PWR_CONF;
    byte = BMI270_POR_PWR_CONF;
    byte &= ~BMI270_PWR_CONF_APS_MSK;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Wait for at least 450us. */
    timing_delay_us(500);

    /* Write INIT_CTRL.init_ctrl = 0x00 to prepare config load. */
    addr = BMI270_REG_INIT_CTRL;
    byte = 0x00;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Upload configuration file. */
    bmi270_upld_conf_file(dev);
#if (defined(BMI270_VLD_CONF_FILE) && (BMI270_VLD_CONF_FILE == 1))
    /* Optionally: Check config file correctness by comparing it to data written to the register
     * in previous step. */
    if (bmi270_vld_conf_file(dev) != BMI270_RES_OK)
    {
        return BMI270_RES_VLD_ERR;
    }
#endif

    /* Write INIT_CTRL.init_ctrl = 0x01 to complete config load.
     * NOTE: This operation must not be performed more than once after POR
     *       or soft reset. */
    addr = BMI270_REG_INIT_CTRL;
    byte = 0x01;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Wait until internal status register contains the value 0b0001. */
    addr = BMI270_REG_INST;
    do
    {
        ll_bmi270_spi_reg_read_byte(&dev->spi_conf, addr, &byte);
    } while ((byte & BMI270_INST_MSG_MSK) != BMI270_INST_MSG_INIT_OK);

    dev->stat = BMI270_STAT_INIT;

    return BMI270_RES_OK;
}

void bmi270_deinit(void)
{
    struct bmi270_dev *dev = &bmi270;
    dev->stat = BMI270_STAT_DEINIT;
}

/* TODO: Must not be performed while NVM writing operation is in progress. */
void bmi270_soft_rst(void)
{
    struct bmi270_dev *dev = &bmi270;
    bmi270_cmd_send(dev, BMI270_CMD_SOFTRESET);
}

void bmi270_pwr_mode_set(bmi270_pwr_mode_t pwr_mode)
{
    struct bmi270_dev *dev = &bmi270;
    struct bmi270_pwr_mode_conf *pwr_mode_conf = &bmi270_pwr_mode_conf_arr[pwr_mode];

    uint8_t addr;
    uint8_t buf[2] = { 0 };
    uint8_t pwr_ctrl_reg;
    uint8_t acc_conf_reg;
    uint8_t gyr_conf_reg;
    uint8_t pwr_conf_reg;

    /* Read the PWR_CONF and PWR_CTRL registers values. */
    addr = BMI270_REG_PWR_CONF;
    ll_bmi270_spi_reg_read_mult_bytes(&dev->spi_conf, addr, &buf[0], sizeof(buf));

    pwr_conf_reg = buf[0];
    pwr_ctrl_reg = buf[1];

    /* Read the ACC_CONF register value. */
    addr = BMI270_REG_ACC_CONF;
    ll_bmi270_spi_reg_read_byte(&dev->spi_conf, addr, &buf[0]);

    acc_conf_reg = buf[0];

    /* Read the GYR_CONF register value. */
    addr = BMI270_REG_GYR_CONF;
    ll_bmi270_spi_reg_read_byte(&dev->spi_conf, addr, &buf[0]);

    gyr_conf_reg = buf[0];

    pwr_conf_reg &= ~(pwr_mode_conf->pwr_conf_mask);
    pwr_conf_reg |=  (pwr_mode_conf->pwr_conf_val);

    pwr_ctrl_reg &= ~(pwr_mode_conf->pwr_ctrl_mask);
    pwr_ctrl_reg |=  (pwr_mode_conf->pwr_ctrl_val);

    acc_conf_reg &= ~(pwr_mode_conf->acc_conf_mask);
    acc_conf_reg |=  (pwr_mode_conf->acc_conf_val);

    gyr_conf_reg &= ~(pwr_mode_conf->gyr_conf_mask);
    gyr_conf_reg |=  (pwr_mode_conf->gyr_conf_val);

    /* Write the PWR_CONF and PWR_CTRL registers values. */
    addr   = BMI270_REG_PWR_CONF;
    buf[0] = pwr_conf_reg;
    buf[1] = pwr_ctrl_reg;
    ll_bmi270_spi_reg_write_mult_bytes(&dev->spi_conf, addr, &buf[0], sizeof(buf));

    /* Write the ACC_CONF register value. */
    addr   = BMI270_REG_ACC_CONF;
    buf[0] = acc_conf_reg;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, buf[0]);

    /* Write the GYR_CONF register value. */
    addr   = BMI270_REG_GYR_CONF;
    buf[0] = gyr_conf_reg;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, buf[0]);
}

void bmi270_stat_set(const bmi270_stat_t stat)
{
    struct bmi270_dev *dev = &bmi270;
    dev->stat = stat;
}

bmi270_stat_t bmi270_stat_get(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->stat;
}

bmi270_res_t bmi270_acc_slf_tst(void)
{
    struct bmi270_dev *dev = &bmi270;

    uint8_t addr;
    uint8_t byte;
    uint8_t acc_slf_tst_reg = 0;

    int16_t pos_x, pos_y, pos_z;
    int16_t neg_x, neg_y, neg_z;

    /* Enable accelerometer with register PWR_CTRL.acc_en = 0x01. */
    addr = BMI270_REG_PWR_CTRL;
    byte = 0x01;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Set +/-16g range in register ACC_RANGE.acc_range. */
    addr = BMI270_REG_ACC_RANGE;
    byte = BMI270_ACC_RANGE_16G;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Set self test amplitude to high by settign ACC_SELF_TEST.acc_self_test_amp = 0x01. */
    acc_slf_tst_reg = BMI270_ACC_SLF_TST_AMP_HIGH;
    addr = BMI270_REG_ACC_SLF_TST;
    byte = acc_slf_tst_reg;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Wait for > 2ms. */
    timing_delay_us(3000);

    /* Set positive self-test polarity (ACC_SELF_TEST.acc_self_test_sign = 0x01). */
    acc_slf_tst_reg |= BMI270_ACC_SLF_TST_SIG_POS;
    addr = BMI270_REG_ACC_SLF_TST;
    byte = acc_slf_tst_reg;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Enable self-test (ACC_SELF_TEST.acc_self_test_en = 0x01). */
    acc_slf_tst_reg |= BMI270_ACC_SLF_TST_EN_ON;
    addr = BMI270_REG_ACC_SLF_TST;
    byte = acc_slf_tst_reg;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Wait for > 50ms. */
    timing_delay_us(55000);

    /* Read and store positive acceleration value of each axis from registers DATA_8 to DATA_13. */
    bmi270_acc_read();
    pos_x = bmi270_acc_get_x();
    pos_y = bmi270_acc_get_y();
    pos_z = bmi270_acc_get_z();

    /* Set negative self-test polarity (ACC_SELF_TEST.acc_self_test_sign = 0x00). */
    acc_slf_tst_reg &= ~(BMI270_ACC_SLF_TST_SIG_POS | BMI270_ACC_SLF_TST_EN_ON);
    addr = BMI270_REG_ACC_SLF_TST;
    byte = acc_slf_tst_reg;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Enable self-test (ACC_SELF_TEST.acc_self_test_en = 0x01). */
    acc_slf_tst_reg |= BMI270_ACC_SLF_TST_EN_ON;
    addr = BMI270_REG_ACC_SLF_TST;
    byte = acc_slf_tst_reg;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Wait for > 50ms. */
    timing_delay_us(55000);

    /* Read and store negative acceleration value of each axis from registers DATA_8 to DATA_13. */
    bmi270_acc_read();
    neg_x = bmi270_acc_get_x();
    neg_y = bmi270_acc_get_y();
    neg_z = bmi270_acc_get_z();

    /* TODO: Calculate difference of positive and negative acceleration values and compare against
     *       minimum difference signal values defined in the table below. */

    /* Disable self-test (ACC_SELF_TEST.acc_self_test_en = 0x01). */
    addr = BMI270_REG_ACC_SLF_TST;
    byte = BMI270_ACC_SLF_TST_EN_OFF;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_slf_tst(void)
{
    struct bmi270_dev *dev = &bmi270;

    uint8_t addr;
    uint8_t byte;

    /* Issue a soft reset or a power-on reset. */
    bmi270_soft_rst();

    /* Initialize device. */
    bmi270_init();

    /* Disable APS PWR_CONF.adv_pwr_save = 0x00. */
    addr = BMI270_REG_PWR_CONF;
    byte = BMI270_PWR_CONF_APS_OFF;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Wait for 450us. */
    timing_delay_us(500);

    /* Enable accelerometer PWR_CTRL.acc_en = 0x01. */
    addr = BMI270_REG_PWR_CTRL;
    byte = BMI270_PWR_CTRL_ACC_ON;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* Send g_trigger command using the register CMD. */
    addr = BMI270_REG_CMD;
    byte = BMI270_CMD_G_TRIGGER;
    ll_bmi270_spi_reg_write_byte(&dev->spi_conf, addr, byte);

    /* GYR_GAIN_STATUS.g_trig_status reports of a successful self-test or execution errors. */
    addr = BMI270_REG_FEATURES_8;
    ll_bmi270_spi_reg_read_byte(&dev->spi_conf, addr, &byte);

    if ((byte & BMI270_GYR_GAIN_STAT_PRECON) ||
        (byte & BMI270_GYR_GAIN_STAT_DL) ||
        (byte & BMI270_GYR_GAIN_STAT_ABORT))
    {
        return BMI270_RES_ERR;
    }

    /* Self test is complete, after the device sets GYR_SELF_TEST_AXES.gyr_st_axes_done = 0x01. */
    addr = BMI270_REG_GYR_SLF_TST_AXES;
    while ((byte & BMI270_GYR_SLF_TST_DONE_MSK) != BMI270_GYR_SLF_TST_DONE)
    {
        ll_bmi270_spi_reg_read_byte(&dev->spi_conf, addr, &byte);
    }

    /* The test passed if all axes report the status "ok" by GYR_SELF_TEST_AXES.gyr_axis[xyz]_ok = 0x01. */
    if ((byte & BMI270_GYR_SLF_TST_X_ERR) ||
        (byte & BMI270_GYR_SLF_TST_Y_ERR) ||
        (byte & BMI270_GYR_SLF_TST_Z_ERR))
    {
        return BMI270_RES_ERR;
    }

    return BMI270_RES_OK;
}

void bmi270_acc_read(void)
{
    struct bmi270_dev *dev = &bmi270;

    uint8_t addr   = BMI270_REG_DATA_8;
    uint8_t buf[6] = { 0 };

    ll_bmi270_spi_reg_read_mult_bytes(&dev->spi_conf, addr, &buf[0], sizeof(buf));

    dev->acc.data.x = ((buf[1] << 0x08) | (buf[0] << 0x00));
    dev->acc.data.y = ((buf[3] << 0x08) | (buf[2] << 0x00));
    dev->acc.data.z = ((buf[5] << 0x08) | (buf[4] << 0x00));
}

int16_t bmi270_acc_get_x(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->acc.data.x;
}

void bmi270_acc_set_x(const int16_t x)
{
    struct bmi270_dev *dev = &bmi270;
    dev->acc.data.x = x;
}

int16_t bmi270_acc_get_y(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->acc.data.y;
}

void bmi270_acc_set_y(const int16_t y)
{
    struct bmi270_dev *dev = &bmi270;
    dev->acc.data.y = y;
}

int16_t bmi270_acc_get_z(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->acc.data.z;
}

void bmi270_acc_set_z(const int16_t z)
{
    struct bmi270_dev *dev = &bmi270;
    dev->acc.data.z = z;
}

void bmi270_gyr_read(void)
{
    struct bmi270_dev *dev = &bmi270;

    uint8_t addr   = BMI270_REG_DATA_14;
    uint8_t buf[6] = { 0 };

    ll_bmi270_spi_reg_read_mult_bytes(&dev->spi_conf, addr, &buf[0], sizeof(buf));

    dev->gyr.data.x = ((buf[1] << 0x08) | (buf[0] << 0x00));
    dev->gyr.data.y = ((buf[3] << 0x08) | (buf[2] << 0x00));
    dev->gyr.data.z = ((buf[5] << 0x08) | (buf[4] << 0x00));
}

int16_t bmi270_gyr_get_x(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->gyr.data.x;
}

void bmi270_gyr_set_x(const int16_t x)
{
    struct bmi270_dev *dev = &bmi270;
    dev->gyr.data.x = x;
}

int16_t bmi270_gyr_get_y(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->gyr.data.y;
}

void bmi270_gyr_set_y(const int16_t y)
{
    struct bmi270_dev *dev = &bmi270;
    dev->gyr.data.y = y;
}

int16_t bmi270_gyr_get_z(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->gyr.data.z;
}

void bmi270_gyr_set_z(const int16_t z)
{
    struct bmi270_dev *dev = &bmi270;
    dev->gyr.data.z = z;
}

void bmi270_temp_read(void)
{
    struct bmi270_dev *dev = &bmi270;

    uint8_t addr   = BMI270_REG_TEMPERATURE_0;
    uint8_t buf[2] = { 0 };

    ll_bmi270_spi_reg_read_mult_bytes(&dev->spi_conf, addr, &buf[0], sizeof(buf));

    dev->temp.data = ((buf[2] << 0x08) | (buf[1] << 0x00));
}

int16_t bmi270_temp_get(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->temp.data;
}

void bmi270_temp_set(int16_t temp)
{
    struct bmi270_dev *dev = &bmi270;
    dev->temp.data = temp;
}

void bmi270_time_read(void)
{
    struct bmi270_dev *dev = &bmi270;

    uint8_t addr   = BMI270_REG_SENSORTIME_0;
    uint8_t buf[2] = { 0 };

    ll_bmi270_spi_reg_read_mult_bytes(&dev->spi_conf, addr, &buf[0], sizeof(buf));
    dev->time.data = (((buf[1] & 0x00ff) << 0x10) | (buf[0] & 0xff00) | (buf[0] & 0x00ff));
}

uint32_t bmi270_time_get(void)
{
    struct bmi270_dev *dev = &bmi270;
    return dev->time.data;
}

void bmi270_time_set(const uint32_t time)
{
    struct bmi270_dev *dev = &bmi270;
    dev->time.data = time;
}
