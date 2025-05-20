#ifndef _BMI270_H
#define _BMI270_H

#include <stdint.h>

///
/// \breif BMI270 registers definition.
///
#define BMI270_REG_CHIP_ID              (0x00)      /*!< Chip identification code.                          */
#define BMI270_REG_ERR_REG              (0x02)      /*!< Reports sensor error condition.                    */
#define BMI270_REG_STATUS               (0x03)      /*!< Sensor status flags.                               */
#define BMI270_REG_DATA_0               (0x04)      /*!< AUX_X(LSB).                                        */
#define BMI270_REG_DATA_1               (0x05)      /*!< AUX_X(MSB).                                        */
#define BMI270_REG_DATA_2               (0x06)      /*!< AUX_Y(LSB).                                        */
#define BMI270_REG_DATA_3               (0x07)      /*!< AUX_Y(MSB).                                        */
#define BMI270_REG_DATA_4               (0x08)      /*!< AUX_Z(LSB).                                        */
#define BMI270_REG_DATA_5               (0x09)      /*!< AUX_Z(MSB).                                        */
#define BMI270_REG_DATA_6               (0x0a)      /*!< AUX_R(LSB).                                        */
#define BMI270_REG_DATA_7               (0x0b)      /*!< AUX_R(MSB).                                        */
#define BMI270_REG_DATA_8               (0x0c)      /*!< ACC_X(LSB).                                        */
#define BMI270_REG_DATA_9               (0x0d)      /*!< ACC_X(MSB).                                        */
#define BMI270_REG_DATA_10              (0x0e)      /*!< ACC_Y(LSB).                                        */
#define BMI270_REG_DATA_11              (0x0f)      /*!< ACC_Y(MSB).                                        */
#define BMI270_REG_DATA_12              (0x10)      /*!< ACC_Z(LSB).                                        */
#define BMI270_REG_DATA_13              (0x11)      /*!< ACC_Z(MSB).                                        */
#define BMI270_REG_DATA_14              (0x12)      /*!< GYR_X(LSB).                                        */
#define BMI270_REG_DATA_15              (0x13)      /*!< GYR_X(MSB).                                        */
#define BMI270_REG_DATA_16              (0x14)      /*!< GYR_Y(LSB).                                        */
#define BMI270_REG_DATA_17              (0x15)      /*!< GYR_Y(MSB).                                        */
#define BMI270_REG_DATA_18              (0x16)      /*!< GYR_Z(LSB).                                        */
#define BMI270_REG_DATA_19              (0x17)      /*!< GYR_Z(MSB).                                        */
#define BMI270_REG_SENSORTIME_0         (0x18)      /*!< Sensor time <7:0>.                                 */
#define BMI270_REG_SENSORTIME_1         (0x19)      /*!< Sensor time <15:8>.                                */
#define BMI270_REG_SENSORTIME_2         (0x1a)      /*!< Sensor time <23:16>.                               */
#define BMI270_REG_EVENT                (0x1b)      /*!< Sensor event flags.                                */
#define BMI270_REG_INT_STATUS_0         (0x1c)      /*!< Interrupt/Feature status.                          */
#define BMI270_REG_INT_STATUS_1         (0x1d)      /*!< Interrupt status 1.                                */
#define BMI270_REG_SC_OUT_0             (0x1e)      /*!< Step counting value byte-0.                        */
#define BMI270_REG_SC_OUT_1             (0x1f)      /*!< Step counting value byte-1.                        */
#define BMI270_REG_WR_GEST_ACT          (0x20)      /*!< Wrist gesture and activity detection output.       */
#define BMI270_REG_INTERNAL_STATUS      (0x21)      /*!< Error bits and messge indicating internal status.  */
#define BMI270_REG_TEMPERATURE_0        (0x22)      /*!< Temperature (LSB).                                 */
#define BMI270_REG_TEMPERATURE_1        (0x23)      /*!< Temperature (MSB).                                 */
#define BMI270_REG_FIFO_LENGTH_0        (0x24)      /*!< FIFO byte count register (LSB).                    */
#define BMI270_REG_FIFO_LENGTH_1        (0x25)      /*!< FIFO byte count register (MSB).                    */
#define BMI270_REG_FIFO_DATA            (0x26)      /*!< FIFO data output register.                         */
#define BMI270_REG_FEAT_PAGE            (0x2f)      /*!< Feature config/output page selector.               */
#define BMI270_REG_FEATURES_0           (0x30)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_1           (0x31)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_2           (0x32)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_3           (0x33)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_4           (0x34)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_5           (0x35)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_6           (0x36)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_7           (0x37)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_8           (0x38)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_9           (0x39)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_10          (0x3a)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_11          (0x3b)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_12          (0x3c)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_13          (0x3d)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_14          (0x3e)      /*!< Input register for feature configuration.          */
#define BMI270_REG_FEATURES_15          (0x3f)      /*!< Input register for feature configuration.          */
#define BMI270_REG_ACC_CONF             (0x40)      /*!< Accelerometer ODR, bandwidth, mode config.         */
#define BMI270_REG_ACC_RANGE            (0x41)      /*!< Selection of the accelerometer g-range.            */
#define BMI270_REG_GYRO_CONF            (0x42)      /*!< Gyroscope ODR, bandwidth, mode config.             */
#define BMI270_REG_GYRO_RANGE           (0x43)      /*!< Gyroscope angular rate measurement range.          */
#define BMI270_REG_AUX_CONF             (0x44)      /*!< Auxiliary sensor interface ODR.                    */
#define BMI270_REG_FIFO_DOWNS           (0x45)      /*!< Gyroe and accel downsampling rates for FIFO.       */
#define BMI270_REG_FIFO_WTM_0           (0x46)      /*!< FIFO watermark level (LSB).                        */
#define BMI270_REG_FIFO_WTM_1           (0x47)      /*!< FIFO watermark level (MSB) and frame content conf. */
#define BMI270_REG_FIFO_CONFIG_0        (0x48)      /*!< FIFO frame content configuration.                  */
#define BMI270_REG_FIFO_CONFIG_1        (0x49)      /*!< FIFO frame content configuration.                  */
#define BMI270_REG_SATURATION           (0x4a)      /*!< Saturation information.                            */
#define BMI270_REG_AUX_DEV_ID           (0x4b)      /*!< Auxiliary interface device id.                     */
#define BMI270_REG_AUX_IF_CONF          (0x4c)      /*!< Auxiliary interface configuration register.        */
#define BMI270_REG_AUX_RD_ADDR          (0x4d)      /*!< Auxiliray interface read address.                  */
#define BMI270_REG_AUX_WR_ADDR          (0x4e)      /*!< Auxiliary include write address.                   */
#define BMI270_REG_AUX_WR_DATA          (0x4f)      /*!< Auxiliary include write data.                      */
#define BMI270_REG_ERR_REG_MSK          (0x52)      /*!< Error flag which triggers error interrupt.         */
#define BMI270_REG_INT1_IO_CTRL         (0x53)      /*!< Electrical behavior of the interrupt pin INT1.     */
#define BMI270_REG_INT2_IO_CTRL         (0x54)      /*!< Electrical behavior of the interrupt pin INT2.     */
#define BMI270_REG_INT_LATCH            (0x55)      /*!< Interrupt latch modes.                             */
#define BMI270_REG_INT1_MAP_FEAT        (0x56)      /*!< Interrupt/feature mapping on INT1.                 */
#define BMI270_REG_INT2_MAP_FEAT        (0x57)      /*!< Interrupt/feature mapping on INT2.                 */
#define BMI270_REG_INT_MAP_DATA         (0x58)      /*!< Data interrupt mapping for both INT pins.          */
#define BMI270_REG_INIT_CTRL            (0x59)      /*!< Start initialization.                              */
#define BMI270_REG_INIT_ADDR_0          (0x5b)      /*!< Base address of the initialization data.           */
#define BMI270_REG_INIT_ADDR_1          (0x5c)      /*!< Base address of the initialization data.           */
#define BMI270_REG_INIT_DATA            (0x5e)      /*!< Initialization register.                           */
#define BMI270_REG_INTERNAL_ERROR       (0x5f)      /*!< Internal error flags.                              */
#define BMI270_REG_AUX_IF_TRIM          (0x68)      /*!< Auxiliary interface trim register (NVM backend).   */
#define BMI270_REG_GYR_CRT_CONF         (0x69)      /*!< Component retrimming for gyroscope.                */
#define BMI270_REG_NVM_CONF             (0x6a)      /*!< NVM configuration.                                 */
#define BMI270_REG_IF_CONF              (0x6b)      /*!< Serial interface settings.                         */
#define BMI270_REG_DRV                  (0x6c)      /*!< Drive strenght control register (NVM backend).     */
#define BMI270_REG_ACC_SELF_TEST        (0x6d)      /*!< Accelerometer self-test configuration and trigger. */
#define BMI270_REG_GYR_SELF_TEST_AXES   (0x6e)      /*!< Gyro axes self-test configuration and trigger.     */
#define BMI270_REG_NV_CONF              (0x70)      /*!< NVM backend configuration bits.                    */
#define BMI270_REG_OFFSET_0             (0x71)      /*!< Offset compensation for accelerometer X-axis.      */
#define BMI270_REG_OFFSET_1             (0x72)      /*!< Offset compensation for accelerometer Y-axis.      */
#define BMI270_REG_OFFSET_2             (0x73)      /*!< Offset compensation for accelerometer Z-axis.      */
#define BMI270_REG_OFFSET_3             (0x74)      /*!< Offset compensation for gyroscope X-axis.          */
#define BMI270_REG_OFFSET_4             (0x75)      /*!< Offset compensation for gyroscope Y-axis.          */
#define BMI270_REG_OFFSET_5             (0x76)      /*!< Offset compensation for gyroscope Z-axis.          */
#define BMI270_REG_OFFSET_6             (0x77)      /*!< Offset copmensation (MSB gyroscope, enables).      */
#define BMI270_REG_PWR_CONF             (0x7c)      /*!< Power mode configuration register.                 */
#define BMI270_REG_PWR_CTRL             (0x7d)      /*!< Power mode control register.                       */
#define BMI270_REG_CMD                  (0x7e)      /*!< Command register.                                  */

///
/// \brief The bmi270 accelerometer data.
///
typedef struct
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
} bmi270_accel_data_t;

///
/// \brief The bmi270 accelerometer config.
///
typedef struct
{
    uint8_t filter_perf : 1;                        /*!< The filter performance mode.                       */
    uint8_t bwp         : 3;                        /*!< The bandwidth.                                     */
    uint8_t odr         : 4;                        /*!< The output data rate.                              */
} bmi270_accel_conf_t;

///
/// \brief The bmi270 accelerometer range.
///
typedef struct
{
    uint8_t reserved    : 6;                        /*!< Reserved.                                          */
    uint8_t acc_range   : 2;                        /*!< The accelerometer g-range.                         */
} bmi270_accel_range_t;

///
/// \brief The bmi270 accelerometer instance.
///
typedef struct
{
    bmi270_accel_data_t  data;                      /*!< The bmi270 accelerometer data.                     */
    bmi270_accel_conf_t  conf;                      /*!< The bmi270 accelerometer configuration.            */
    bmi270_accel_range_t range;                     /*!< The bmi270 accelerometer range.                    */
} bmi270_accel_t;

///
/// \brief The bmi270 gyroscope data.
///
typedef struct
{
    uint16_t x;                                     /*!< The x-axis value.                                  */
    uint16_t y;                                     /*!< The y-axis value.                                  */
    uint16_t z;                                     /*!< The z-axis value.                                  */
} bmi270_gyro_data_t;

///
/// \brief The bmi270 gyroscope config.
///
typedef struct
{
    uint8_t filter_perf : 1;                        /*!< The filter performance mode.                       */
    uint8_t noise_perf  : 1;                        /*!< The noise performance mode.                        */
    uint8_t bwp         : 2;                        /*!< The bandwidth coefficient.                         */
    uint8_t odr         : 4;                        /*!< The output data rate.                              */
} bmi270_gyro_conf_t;

///
/// \brief The bmi270 gyroscope range.
///
typedef struct
{
    uint8_t reserved    : 4;                        /*!< Reserved.                                          */
    uint8_t ois_range   : 1;                        /*!< Pre-filtered FIFO data and OIS data.               */
    uint8_t gyr_range   : 3;                        /*!< Filtered FIFO data and DATA registers.             */
} bmi270_gyro_range_t;

///
/// \brief The bmi270 gyroscope instance.
///
typedef struct
{
    bmi270_gyro_data_t  data;                       /*!< The bmi270 gyroscope data.                         */
    bmi270_gyro_conf_t  conf;                       /*!< The bmi270 gyroscope configuration.                */
    bmi270_gyro_range_t range;                      /*!< The bmi270 gyroscope range.                        */
} bmi270_gyro_t;

///
/// \brief The bmi270 temperature sensor instance.
///
typedef struct
{
    uint16_t value;                                 /*!< The temperature value.                             */
} bmi270_temp_t;

///
/// \brief The bmi270 imu instance.
///
typedef struct
{
    bmi270_accel_t accel;                           /*!< The accelerometer instance.                        */
    bmi270_gyro_t  gyro;                            /*!< The gyroscope instance.                            */
    bmi270_temp_t  temp;                            /*!< The temperature sensor instance.                   */
    uint8_t        is_init;                         /*!< The is initialized flag.                           */
} bmi270_t;

#endif  /* _BMI270_H */
