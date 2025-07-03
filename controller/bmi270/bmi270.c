#include "bmi270.h"
#include "spi_ctrl.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The bmi270 accelerometer data type.
///
typedef struct bmi270_acc_data
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
} bmi270_acc_data_t;

///
/// \brief The bmi270 accelerometer config type.
///
typedef struct bmi270_acc_conf
{
    uint8_t filt_perf  : 1;                         /*!< The filter performance mode.                       */
    uint8_t bwp        : 3;                         /*!< The bandwidth.                                     */
    uint8_t odr        : 4;                         /*!< The output data rate.                              */
} bmi270_acc_conf_t;

///
/// \brief The bmi270 accelerometer range type.
///
typedef struct bmi270_acc_rng
{
    uint8_t reserved   : 6;                         /*!< Reserved.                                          */
    uint8_t acc_rng    : 2;                         /*!< The accelerometer g-range.                         */
} bmi270_acc_rng_t;

///
/// \brief The bmi270 accelerometer instance type.
///
typedef struct bmi270_acc
{
    bmi270_acc_data_t data;                         /*!< The bmi270 accelerometer data.                     */
    bmi270_acc_conf_t conf;                         /*!< The bmi270 accelerometer configuration.            */
    bmi270_acc_rng_t  rng;                          /*!< The bmi270 accelerometer range.                    */
} bmi270_acc_t;

///
/// \brief The bmi270 gyroscope data type.
///
typedef struct bmi270_gyr_data
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
} bmi270_gyr_data_t;

///
/// \brief The bmi270 gyroscope config type.
///
typedef struct bmi270_gyr_conf
{
    uint8_t filt_perf  : 1;                         /*!< The filter performance mode.                       */
    uint8_t noise_perf : 1;                         /*!< The noise performance mode.                        */
    uint8_t bwp        : 2;                         /*!< The bandwidth coefficient.                         */
    uint8_t odr        : 4;                         /*!< The output data rate.                              */
} bmi270_gyr_conf_t;

///
/// \brief The bmi270 gyroscope range type.
///
typedef struct bmi270_gyr_rng
{
    uint8_t reserved   : 4;                         /*!< Reserved.                                          */
    uint8_t ois_rng    : 1;                         /*!< Pre-filtered FIFO data and OIS data.               */
    uint8_t gyr_rng    : 3;                         /*!< Filtered FIFO data and DATA registers.             */
} bmi270_gyr_rng_t;

///
/// \brief The bmi270 gyroscope instance type.
///
typedef struct bmi270_gyr
{
    bmi270_gyr_data_t data;                         /*!< The bmi270 gyroscope data.                         */
    bmi270_gyr_conf_t conf;                         /*!< The bmi270 gyroscope configuration.                */
    bmi270_gyr_rng_t  rng;                          /*!< The bmi270 gyroscope range.                        */
} bmi270_gyr_t;

///
/// \brief The bmi270 temperature sensor instance type.
///
typedef struct bmi270_temp
{
    uint16_t data;                                  /*!< The temperature data.                              */
} bmi270_temp_t;

///
/// \brief The gpio pair type.
///
typedef struct gpio_pair
{
    uint32_t port;                                  /*!< The gpio port identifier.                          */
    uint16_t pin;                                   /*!< The gpio pin identifier.                           */
} gpio_pair_t;

///
/// \brief The bmi270 instance type.
///
typedef struct bmi270
{
    bmi270_acc_t  acc;                              /*!< The accelerometer instance.                        */
    bmi270_gyr_t  gyr;                              /*!< The gyroscope instance.                            */
    bmi270_temp_t temp;                             /*!< The temperature sensor instance.                   */
    gpio_pair_t   gpio;                             /*!< The gpio pair.                                     */
    bool          init;                             /*!< The is initialized flag.                           */
} bmi270_t;

///
/// \breif The bmi270 power mode config type.
///
typedef sturct bmi270_pwr_mode_conf
{
    uint8_t pwr_ctrl_mask;
    uint8_t pwr_ctrl_val;
    uint8_t acc_conf_mask;
    uint8_t acc_conf_val;
    uint8_t gyr_conf_mask;
    uint8_t gyr_conf_val;
    uint8_t pwr_conf_mask;
    uint8_t pwr_conf_val;
} bmi270_pwr_mode_conf_t;

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \breif The bmi270 instance.
///
static bmi270_t bmi270_inst =
{
    .acc  = { 0 },
    .gyr  = { 0 },
    .temp = { 0 },
    .gpio =
    {
        .port = GPIOA,
        .pin  = GPIO4,
    },
    .init = BMI270_STAT_DEINIT,
};

///
/// \breif The bmi270 power mode configuration look-up table.
///
static const bmi270_pwr_mode_conf_t bmi270_pwr_mode_confs[BMI270_PWR_MODE_TOTAL] =
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

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
bmi270_t* bmi270_get_inst(void)
{
    return &bmi270_inst;
}

const bmi270_pwr_mode_conf_t* bmi270_get_pwr_mode_conf(const bmi270_pwr_mode_t pwr_mode)
{
    if ((pwr_mode < BMI270_PWR_MODE_BEGIN) || (pwr_mode >= BMI270_PWR_MODE_TOTAL))
    {
        return NULL;
    }

    return &bmi270_pwr_mode_confs[pwr_mode];
}

bmi270_res_t bmi270_init(bmi270_t *const inst)
{
    if (inst == NULL)
    {
        return BMI270_RES_ERR;
    }

    uint8_t    address;
    uint8_t    buffer[2];
    spi_ctrl_t *spi_ctrl_inst;

    memset(&inst->acc,  0, sizeof(inst->acc));
    memset(&inst->gyr,  0, sizeof(inst->gyr));
    memset(&inst->temp, 0, sizeof(inst->temp));

    /* TODO: The device initialization, needs spi. */
    if (spi_ctrl_get_inst(&spi_ctrl_inst) == SPI_CTRL_RES_ERR)
    {
        return BMI270_RES_ERR;
    }

    if (spi_ctrl_inst->init == SPI_CTRL_STAT_DEINIT)
    {
        if (spi_ctrl_init(spi_ctrl_inst) == SPI_CTRL_RES_ERR)
        {
            return BMI270_RES_ERR;
        }
    }

    spi_ctrl_begin(spi_ctrl_inst, inst->gpio.port, inst->gpio.pin);

    /* Read an arbitrary register of BMI270, discard the read response.
     * The MSB of the address is R/W indicator. */
    address = (BMI270_REG_CHIP_ID | BMI270_OP_READ);
    spi_ctrl_send(spi_ctrl_inst, &address, sizeof(address));
    spi_ctrl_recv(spi_ctrl_inst, &buffer, sizeof(buffer));

    /* Disable advanced power save mode. */
    address = (BMI270_REG_PWR_CONF | BMI270_OP_WRITE);
    spi_ctrl_send(spi_ctrl_ins, &address, sizeof(address));

    /* Wait for 450us (12 LSB of SENSORTIME_0). */
    address = (BMI270_REG_SENSORTIME_0 | BMI270_OP_READ);
    memset(&buffer[0], 0, sizeof(buffer));
    while (buffer[1] < 12)
    {
        spi_ctrl_send(spi_ctrl_inst, &address, sizeof(address));
        spi_ctrl_recv(spi_ctrl_inst, &buffer, sizeof(buffer));
    }

    spi_ctrl_end(spi_ctrl_inst, inst->gpio.port, inst->gpio.pin);

    inst->init = BMI270_STAT_INIT;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_deinit(bmi270_t *const inst)
{
    if (inst == NULL)
    {
        return BMI270_RES_ERR;
    }

    inst->init = BMI270_STAT_DEINIT;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_set_pwr_mode(const bmi270_pwr_mode_conf_t *const pwr_mode_conf)
{
    if (pwr_mode_conf == NULL)
    {
        return BMI270_RES_ERR;
    }

    /* TODO: Get registers value via spi. */
    uint8_t pwr_ctrl_reg;
    uint8_t acc_conf_reg;
    uint8_t gyr_conf_reg;
    uint8_t pwr_conf_reg;

    pwr_ctrl_reg &= ~(pwr_mode_conf->pwr_ctrl_mask);
    pwr_ctrl_reg |=  (pwr_mode_conf->pwr_ctrl_value);

    acc_conf_reg &= ~(pwr_mode_conf->acc_conf_mask);
    acc_conf_reg |=  (pwr_mode_conf->acc_conf_value);

    gyr_conf_reg &= ~(pwr_mode_conf->gyr_conf_mask);
    gyr_conf_reg |=  (pwr_mode_conf->gyr_conf_value);

    pwr_conf_reg &= ~(pwr_mode_conf->pwr_conf_mask);
    pwr_conf_reg |=  (pwr_mode_conf->pwr_conf_value);

    /* TODO: Set the registers via spi. */

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_self_test(void)
{
    /* TODO: The accelerometer self-test, needs spi. */
}

bmi270_res_t bmi270_gyr_self_test(void)
{
    /* TODO: The gyroscope self-test, needs spi. */
}

bmi270_res_t bmi270_acc_read(bmi270_t *const inst);
{
    if (inst == NULL)
    {
        return BMI270_RES_ERR;
    }

    /* TODO: Read the accelerometer data via spi. */
    inst->acc.data.x =
    inst->acc.data.y =
    inst->acc.data.z =

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_get_x(const bmi270_t *const inst, int16_t *const x);
{
    if ((inst == NULL) || (x == NULL))
    {
        return BMI270_RES_ERR;
    }

    *x = inst->acc.data.x;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_get_y(const bmi270_t *const inst, int16_t *const y);
{
    if ((inst == NULL) || (y == NULL))
    {
        return BMI270_RES_ERR;
    }

    *y = inst->acc.data.y;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_acc_get_z(const bmi270_t *const inst, int16_t *const z)
{
    if ((inst == NULL) || (z == NULL))
    {
        return BMI270_RES_ERR;
    }

    *z = inst->acc.data.z;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_read(bmi270_t *const inst);
{
    if (inst == NULL)
    {
        return BMI270_RES_ERR;
    }

    /* TODO: Read the gyroscope data via spi. */
    inst->gyr.data.x =
    inst->gyr.data.y =
    inst->gyr.data.z =

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_get_x(const bmi270_t *const inst, int16_t *const x)
{
    if ((inst == NULL) || (x == NULL))
    {
        return BMI270_RES_ERR;
    }

    *x = inst->gyr.data.x;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_get_y(const bmi270_t *const inst, int16_t *const y)
{
    if ((inst == NULL) || (y == NULL))
    {
        return BMI270_RES_ERR;
    }

    *y = inst->gyr.data.y;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_gyr_get_z(const bmi270_t *const inst, int16_t *const z)
{
    if ((inst == NULL) || (z == NULL))
    {
        return BMI270_RES_ERR;
    }

    *z = inst->gyr.data.z;

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_temp_read(bmi270_t *const inst);
{
    if (inst == NULL)
    {
        return BMI270_RES_ERR;
    }

    /* TODO: Read the temperature data via spi. */
    inst->temp.data =

    return BMI270_RES_OK;
}

bmi270_res_t bmi270_temp_get(const bmi270_t *const inst, int16_t *const temp)
{
    if ((inst == NULL) || (temp == NULL))
    {
        return BMI270_RES_ERR;
    }

    *temp = inst->temp.data;

    return BMI270_RES_OK;
}
