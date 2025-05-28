#include "bmi270.h"

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
    uint8_t        is_init;                         /*!< The is initialized flag.                           */
} bmi270_t;

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \breif The bmi270 instance.
///
static bmi270_t bmi270 = { 0 };

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

bmi270_result_t bmi270_init(bmi270_t *const bmi270)
{
    if (bmi270 == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    memset(bmi270, 0, sizeof(bmi270));

    /* TODO: The device initialization, needs spi. */

    bmi270->is_init = BMI270_STATUS_INIT;

    return BMI270_RESULT_SUCCESS;
}

bmi270_result_t bmi270_deinit(bmi270_t *const bmi270)
{
    if (bmi270 == NULL)
    {
        return BMI270_RESULT_ERROR;
    }

    bmi270->is_init = BMI270_STATUS_DEINIT;

    return BMI270_RESULT_SUCCESS;
}
