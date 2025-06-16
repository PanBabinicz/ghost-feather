#include "bmi270.h"
#include <stdbool.h>
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The bmi270 accelerometer data type.
///
typedef struct bmi270_accel_data
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
} bmi270_accel_data_t;

///
/// \brief The bmi270 accelerometer config type.
///
typedef struct bmi270_accel_conf
{
    uint8_t filter_perf : 1;                        /*!< The filter performance mode.                       */
    uint8_t bwp         : 3;                        /*!< The bandwidth.                                     */
    uint8_t odr         : 4;                        /*!< The output data rate.                              */
} bmi270_accel_conf_t;

///
/// \brief The bmi270 accelerometer range type.
///
typedef struct bmi270_accel_range
{
    uint8_t reserved    : 6;                        /*!< Reserved.                                          */
    uint8_t acc_range   : 2;                        /*!< The accelerometer g-range.                         */
} bmi270_accel_range_t;

///
/// \brief The bmi270 accelerometer instance type.
///
typedef struct bmi270_accel
{
    bmi270_accel_data_t  data;                      /*!< The bmi270 accelerometer data.                     */
    bmi270_accel_conf_t  conf;                      /*!< The bmi270 accelerometer configuration.            */
    bmi270_accel_range_t range;                     /*!< The bmi270 accelerometer range.                    */
} bmi270_accel_t;

///
/// \brief The bmi270 gyroscope data type.
///
typedef struct bmi270_gyro_data
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
} bmi270_gyro_data_t;

///
/// \brief The bmi270 gyroscope config type.
///
typedef struct bmi270_gyro_conf
{
    uint8_t filter_perf : 1;                        /*!< The filter performance mode.                       */
    uint8_t noise_perf  : 1;                        /*!< The noise performance mode.                        */
    uint8_t bwp         : 2;                        /*!< The bandwidth coefficient.                         */
    uint8_t odr         : 4;                        /*!< The output data rate.                              */
} bmi270_gyro_conf_t;

///
/// \brief The bmi270 gyroscope range type.
///
typedef struct bmi270_gyro_range
{
    uint8_t reserved    : 4;                        /*!< Reserved.                                          */
    uint8_t ois_range   : 1;                        /*!< Pre-filtered FIFO data and OIS data.               */
    uint8_t gyr_range   : 3;                        /*!< Filtered FIFO data and DATA registers.             */
} bmi270_gyro_range_t;

///
/// \brief The bmi270 gyroscope instance type.
///
typedef struct bmi270_gyro
{
    bmi270_gyro_data_t  data;                       /*!< The bmi270 gyroscope data.                         */
    bmi270_gyro_conf_t  conf;                       /*!< The bmi270 gyroscope configuration.                */
    bmi270_gyro_range_t range;                      /*!< The bmi270 gyroscope range.                        */
} bmi270_gyro_t;

///
/// \brief The bmi270 temperature sensor instance type.
///
typedef struct bmi27_temp
{
    uint16_t data;                                  /*!< The temperature data.                              */
} bmi270_temp_t;

///
/// \brief The bmi270 instance type.
///
typedef struct bmi270
{
    bmi270_accel_t accel;                           /*!< The accelerometer instance.                        */
    bmi270_gyro_t  gyro;                            /*!< The gyroscope instance.                            */
    bmi270_temp_t  temp;                            /*!< The temperature sensor instance.                   */
    bool           is_init;                         /*!< The is initialized flag.                           */
} bmi270_t;

///
/// \breif The bmi270 power mode config type.
///
typedef sturct bmi270_power_mode_config
{
    uint8_t pwr_ctrl_mask;
    uint8_t pwr_ctrl_value;
    uint8_t acc_conf_mask;
    uint8_t acc_conf_value;
    uint8_t gyr_conf_mask;
    uint8_t gyr_conf_value;
    uint8_t pwr_conf_mask;
    uint8_t pwr_conf_value;
} bmi270_power_mode_config_t;

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \breif The bmi270 instance.
///
static bmi270_t bmi270_instance = { 0 };

///
/// \breif The bmi270 power mode configuration look-up table.
///
static const bmi270_power_mode_config_t bmi270_power_mode_configs[BMI270_POWER_MODE_TOTAL] =
{
    /* Suspend mode (lowest power mode). */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask  = (0x00),
        .acc_conf_value = (0x00),
        .gyr_conf_mask  = (0x00),
        .gyr_conf_value = (0x00),
        .pwr_conf_mask  = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_value = (BMI270_PWR_CONF_APS_ON),
    },

    /* Configuration mode. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask  = (0x00),
        .acc_conf_value = (0x00),
        .gyr_conf_mask  = (0x00),
        .gyr_conf_value = (0x00),
        .pwr_conf_mask  = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_value = (BMI270_PWR_CONF_APS_OFF),
    },

    /* Low power mode. Accelerometer only. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask  = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_value = (BMI270_ACC_FILT_PERF_ULP),
        .gyr_conf_mask  = (0x00),
        .gyr_conf_value = (0x00),
        .pwr_conf_mask  = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_value = (BMI270_PWR_CONF_APS_ON),
    },

    /* Low power mode. Gyroscope only. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask  = (0x00),
        .acc_conf_value = (0x00),
        .gyr_conf_mask  = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILTER_PERF_MASK),
        .gyr_conf_value = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILTER_PERF_ULP),
        .pwr_conf_mask  = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_value = (BMI270_PWR_CONF_APS_ON),
    },

    /* Low power mode. IMU. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask  = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_value = (BMI270_ACC_FILT_PERF_ULP),
        .gyr_conf_mask  = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILTER_PERF_MASK),
        .gyr_conf_value = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILTER_PERF_ULP),
        .pwr_conf_mask  = (BMI270_PWR_CONF_APS_MASK),
        .pwr_conf_value = (BMI270_PWR_CONF_APS_ON),
    },

    /* Normal mode. Accelerometer only. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask  = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_value = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask  = (0x00),
        .gyr_conf_value = (0x00),
        .pwr_conf_mask  = (0x00),
        .pwr_conf_value = (0x00),
    },

    /* Normal mode. Gyroscope only. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask  = (0x00),
        .acc_conf_value = (0x00),
        .gyr_conf_mask  = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILTER_PERF_MASK),
        .gyr_conf_value = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILTER_PERF_HP),
        .pwr_conf_mask  = (0x00),
        .pwr_conf_value = (0x00),
    },

    /* Normal mode. IMU. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask  = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_value = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask  = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILTER_PERF_MASK),
        .gyr_conf_value = (BMI270_GYR_NOISE_PERF_ULP | BMI270_GYR_FILTER_PERF_HP),
        .pwr_conf_mask  = (0x00),
        .pwr_conf_value = (0x00),
    },

    /* Performance mode. Accelerometer only. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_OFF),
        .acc_conf_mask  = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_value = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask  = (0x00),
        .gyr_conf_value = (0x00),
        .pwr_conf_mask  = (0x00),
        .pwr_conf_value = (0x00),
    },

    /* Performance mode. Gyroscope only. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_OFF | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask  = (0x00),
        .acc_conf_value = (0x00),
        .gyr_conf_mask  = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILTER_PERF_MASK),
        .gyr_conf_value = (BMI270_GYR_NOISE_PERF_HP | BMI270_GYR_FILTER_PERF_HP),
        .pwr_conf_mask  = (0x00),
        .pwr_conf_value = (0x00),
    },

    /* Performance mode. IMU. */
    {
        .pwr_ctrl_mask  = (BMI270_PWR_CTRL_ACC_MASK | BMI270_PWR_CTRL_GYR_MASK),
        .pwr_ctrl_value = (BMI270_PWR_CTRL_ACC_ON | BMI270_PWR_CTRL_GYR_ON),
        .acc_conf_mask  = (BMI270_ACC_FILT_PERF_MASK),
        .acc_conf_value = (BMI270_ACC_FILT_PERF_HP),
        .gyr_conf_mask  = (BMI270_GYR_NOISE_PERF_MASK | BMI270_GYR_FILTER_PERF_MASK),
        .gyr_conf_value = (BMI270_GYR_NOISE_PERF_HP | BMI270_GYR_FILTER_PERF_HP),
        .pwr_conf_mask  = (0x00),
        .pwr_conf_value = (0x00),
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
bmi270_t* bmi270_get_instance(void)
{
    return &bmi270;
}

const bmi270_power_mode_config_t* bmi270_get_power_mode_config(const bmi270_power_mode_t power_mode)
{
    if ((power_mode < BMI270_POWER_MODE_BEGIN) || (power_mode >= BMI270_POWER_MODE_TOTAL))
    {
        return NULL;
    }

    return &bmi270_power_mode_configs[power_mode];
}

bmi270_result_t bmi270_init(bmi270_t *const instance)
{
    if (instance == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    memset(instance, 0, sizeof(instance));

    /* TODO: The device initialization, needs spi. */

    instance->is_init = BMI270_STATUS_INIT;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_deinit(bmi270_t *const instance)
{
    if (instance == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    instance->is_init = BMI270_STATUS_DEINIT;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_set_power_mode(const bmi270_power_mode_config_t *const power_mode_config)
{
    if (power_mode_config == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    /* TODO: Get registers value via spi. */
    uint8_t pwr_ctrl_reg;
    uint8_t acc_conf_reg;
    uint8_t gyr_conf_reg;
    uint8_t pwr_conf_reg;

    pwr_ctrl_reg &= ~(power_mode_config->pwr_ctrl_mask);
    pwr_ctrl_reg |=  (power_mode_config->pwr_ctrl_value);

    acc_conf_reg &= ~(power_mode_config->acc_conf_mask);
    acc_conf_reg |=  (power_mode_config->acc_conf_value);

    gyr_conf_reg &= ~(power_mode_config->gyr_conf_mask);
    gyr_conf_reg |=  (power_mode_config->gyr_conf_value);

    pwr_conf_reg &= ~(power_mode_config->pwr_conf_mask);
    pwr_conf_reg |=  (power_mode_config->pwr_conf_value);

    /* TODO: Set the registers via spi. */

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_accel_self_test(void)
{
    /* TODO: The accelerometer initialization, needs spi. */
}

bmi270_result_t bmi270_gyro_self_test(void)
{
    /* TODO: The gyroscope self-test, needs spi. */
}

bmi270_result_t bmi270_accel_read(bmi270_t *const instance)
{
    if (instance == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    /* TODO: Read the accelerometer data via spi. */
    instance->accel.data.x =
    instance->accel.data.y =
    instance->accel.data.z =

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_accel_get_x(const bmi270_t *const instance, int16_t *const x)
{
    if ((instance == NULL) || (x == NULL))
    {
        return BMI270_RESULT_ERROR;
    }

    *x = instance->accel.data.x;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_accel_get_y(const bmi270_t *const instance, int16_t *const y)
{
    if ((instance == NULL) || (y == NULL))
    {
        return BMI270_RESULT_ERROR;
    }

    *y = instance->accel.data.y;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_accel_get_z(const bmi270_t *const instance, int16_t *const z)
{
    if ((instance == NULL) || (z == NULL))
    {
        return BMI270_RESULT_ERROR;
    }

    *z = instance->accel.data.z;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_gyro_read(bmi270_t *const instance)
{
    if (instance == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    /* TODO: Read the gyroscope data via spi. */
    instance->gyro.data.x =
    instance->gyro.data.y =
    instance->gyro.data.z =

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_gyro_get_x(const bmi270_t *const instance, int16_t *const x)
{
    if ((instance == NULL) || (x == NULL))
    {
        return BMI270_RESULT_ERROR;
    }

    *x = instance->gyro.data.x;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_gyro_get_y(const bmi270_t *const instance, int16_t *const y)
{
    if ((instance == NULL) || (y == NULL))
    {
        return BMI270_RESULT_ERROR;
    }

    *y = instance->gyro.data.y;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_gyro_get_z(const bmi270_t *const instance, int16_t *const z)
{
    if ((instance == NULL) || (z == NULL))
    {
        return BMI270_RESULT_ERROR;
    }

    *z = instance->gyro.data.z;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_temp_read(bmi270_t *const instance)
{
    if (instance == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    /* TODO: Read the temperature data via spi. */
    instance->temp.data =

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_temp_get(const bmi270_t *const instance, int16_t *const temp)
{
    if ((instance == NULL) || (temp == NULL))
    {
        return BMI270_RESULT_ERROR;
    }

    *temp = instance->temp.data;

    return BMI270_RESULT_SUCCESS;
}
