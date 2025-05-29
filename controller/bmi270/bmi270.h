#ifndef _BMI270_H
#define _BMI270_H

#include <stdint.h>
#include <string.h>

///
/// \breif The bmi270 registers definition.
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
/// \brief The bmi270 ACC_CONF register fields.
///
#define BMI270_ACC_ODR_MASK         (0x0f << 0x00)  /*!< The accelerometer ODR mask.                        */
#define BMI270_ACC_ODR_0P78         (0x01 << 0x00)  /*!< The accelerometer ODR equal to 25/32 Hz.           */
#define BMI270_ACC_ODR_1P5          (0x02 << 0x00)  /*!< The accelerometer ODR equal to 25/16 Hz.           */
#define BMI270_ACC_ODR_3P1          (0x03 << 0x00)  /*!< The accelerometer ODR equal to 25/8  Hz.           */
#define BMI270_ACC_ODR_6P25         (0x04 << 0x00)  /*!< The accelerometer ODR equal to 25/4  Hz.           */
#define BMI270_ACC_ODR_12P5         (0x05 << 0x00)  /*!< The accelerometer ODR equal to 25/2  Hz.           */
#define BMI270_ACC_ODR_25           (0x06 << 0x00)  /*!< The accelerometer ODR equal to 25    Hz.           */
#define BMI270_ACC_ODR_50           (0x07 << 0x00)  /*!< The accelerometer ODR equal to 50    Hz.           */
#define BMI270_ACC_ODR_100          (0x08 << 0x00)  /*!< The accelerometer ODR equal to 100   Hz.           */
#define BMI270_ACC_ODR_200          (0x09 << 0x00)  /*!< The accelerometer ODR equal to 200   Hz.           */
#define BMI270_ACC_ODR_400          (0x0a << 0x00)  /*!< The accelerometer ODR equal to 400   Hz.           */
#define BMI270_ACC_ODR_800          (0x0b << 0x00)  /*!< The accelerometer ODR equal to 800   Hz.           */
#define BMI270_ACC_ODR_1k6          (0x0c << 0x00)  /*!< The accelerometer ODR equal to 1600  Hz.           */
#define BMI270_ACC_ODR_3k2          (0x0d << 0x00)  /*!< Reserved.                                          */
#define BMI270_ACC_ODR_6k4          (0x0e << 0x00)  /*!< Reserved.                                          */
#define BMI270_ACC_ODR_12k8         (0x0f << 0x00)  /*!< Reserved.                                          */
#define BMI270_ACC_BWP_MASK         (0x07 << 0x04)  /*!< The accelerometer bandwidth mask.                  */
#define BMI270_ACC_BWP_OSR4_AVG1    (0x00 << 0x04)  /*!< The accelerometer OSR4 mode / no averaging.        */
#define BMI270_ACC_BWP_OSR2_AVG2    (0x01 << 0x04)  /*!< The accelerometer OSR2 mode / average 2 samples.   */
#define BMI270_ACC_BWP_NORM_AVG4    (0x02 << 0x04)  /*!< The accelerometer normal mode / average 4 samples. */
#define BMI270_ACC_BWP_CIC_AVG8     (0x03 << 0x04)  /*!< The accelerometer CIC mode / average 8 samples.    */
#define BMI270_ACC_BWP_RES_AVG16    (0x04 << 0x04)  /*!< Reserved mode / average 16 samples.                */
#define BMI270_ACC_BWP_RES_AVG32    (0x05 << 0x04)  /*!< Reserved mode / average 32 samples.                */
#define BMI270_ACC_BWP_RES_AVG64    (0x06 << 0x04)  /*!< Reserved mode / average 64 samples.                */
#define BMI270_ACC_BWP_RES_AVG128   (0x07 << 0x04)  /*!< Reserved mode / average 128 samples.               */
#define BMI270_ACC_FILT_PERF_MASK   (0x01 << 0x07)  /*!< The accelerometer filter perfromance mask.         */
#define BMI270_ACC_FILT_PERF_ULP    (0x00 << 0x07)  /*!< The accelerometer filter power optimized mode.     */
#define BMI270_ACC_FILT_PERF_HP     (0x01 << 0x07)  /*!< The accelerometer filter perf optimized mode.      */

///
/// \brief The bmi270 ACC_RANGE register g-range field.
///
#define BMI270_ACC_RANGE_MASK       (0x03 << 0x00)  /*!< The accelerometer g-range mask.                    */
#define BMI270_ACC_RANGE_2G         (0x00 << 0x00)  /*!< The accelerometer g-range +/-2g.                   */
#define BMI270_ACC_RANGE_4G         (0x01 << 0x00)  /*!< The accelerometer g-range +/-4g.                   */
#define BMI270_ACC_RANGE_8G         (0x02 << 0x00)  /*!< The accelerometer g-range +/-8g.                   */
#define BMI270_ACC_RANGE_16G        (0x03 << 0x00)  /*!< The accelerometer g-range +/-16g.                  */

///
/// \brief The bmi270 GYR_CONF register fields.
///
#define BMI270_GYR_ODR_MASK         (0x0f << 0x00)  /*!< The gyroscope ODR mask.                            */
#define BMI270_GYR_ODR_0P78         (0x01 << 0x00)  /*!< Reserved.                                          */
#define BMI270_GYR_ODR_1P5          (0x02 << 0x00)  /*!< Reserved.                                          */
#define BMI270_GYR_ODR_3P1          (0x03 << 0x00)  /*!< Reserved.                                          */
#define BMI270_GYR_ODR_6P25         (0x04 << 0x00)  /*!< Reserved.                                          */
#define BMI270_GYR_ODR_12P5         (0x05 << 0x00)  /*!< Reserved.                                          */
#define BMI270_GYR_ODR_25           (0x06 << 0x00)  /*!< The gyroscope ODR equal to 25    Hz.               */
#define BMI270_GYR_ODR_50           (0x07 << 0x00)  /*!< The gyroscope ODR equal to 50    Hz.               */
#define BMI270_GYR_ODR_100          (0x08 << 0x00)  /*!< The gyroscope ODR equal to 100   Hz.               */
#define BMI270_GYR_ODR_200          (0x09 << 0x00)  /*!< The gyroscope ODR equal to 200   Hz.               */
#define BMI270_GYR_ODR_400          (0x0a << 0x00)  /*!< The gyroscope ODR equal to 400   Hz.               */
#define BMI270_GYR_ODR_800          (0x0b << 0x00)  /*!< The gyroscope ODR equal to 800   Hz.               */
#define BMI270_GYR_ODR_1k6          (0x0c << 0x00)  /*!< The gyroscope ODR equal to 1600  Hz.               */
#define BMI270_GYR_ODR_3k2          (0x0d << 0x00)  /*!< The gyroscope ODR equal to 3200  HZ.               */
#define BMI270_GYR_ODR_6k4          (0x0e << 0x00)  /*!< Reserved.                                          */
#define BMI270_GYR_ODR_12k8         (0x0f << 0x00)  /*!< Reserved.                                          */
#define BMI270_GYR_BWP_MASK         (0x03 << 0x04)  /*!< The gyroscope bandwidth mask.                      */
#define BMI270_GYR_BWP_OSR4         (0x00 << 0x04)  /*!< The gyroscope OSR4 mode.                           */
#define BMI270_GYR_BWP_OSR2         (0x01 << 0x04)  /*!< The gyroscope OSR2 mode.                           */
#define BMI270_GYR_BWP_NORM         (0x02 << 0x04)  /*!< The gyroscope normal mode.                         */
#define BMI270_GYR_BWP_RES          (0x03 << 0x04)  /*!< Reserved.                                          */
#define BMI270_GYR_NOISE_PERF_MASK  (0x01 << 0x06)  /*!< The gyroscope noise performance mask.              */
#define BMI270_GYR_NOISE_PERF_ULP   (0x00 << 0x06)  /*!< The gyroscope noise power optimized mode.          */
#define BMI270_GYR_NOISE_PERF_HP    (0x01 << 0x06)  /*!< The gyroscope noise perf optimized mode.           */
#define BMI270_GYR_NOISE_PERF_MASK  (0x01 << 0x07)  /*!< The gyroscope filter performance mask.             */
#define BMI270_GYR_NOISE_PERF_ULP   (0x00 << 0x07)  /*!< The gyroscope filter power optimized mode.         */
#define BMI270_GYR_NOISE_PERF_HP    (0x01 << 0x07)  /*!< The gyroscope filter perf optimized mode.          */

///
/// \brief The bmi270 GYR_RANGE register fields.
///
#define BMI270_GYR_RANGE_MASK       (0x07 << 0x00)  /*!< The gyroscope range mask.                          */
#define BMI270_GYR_RANGE_2000       (0x00 << 0x00)  /*!< The gyroscope range +/-2000dps, 16.4  LSB/dps.     */
#define BMI270_GYR_RANGE_1000       (0x01 << 0x00)  /*!< The gyroscope range +/-1000dps, 32.8  LSB/dps.     */
#define BMI270_GYR_RANGE_500        (0x02 << 0x00)  /*!< The gyroscope range +/-500 dps, 65.6  LSB/dps.     */
#define BMI270_GYR_RANGE_250        (0x03 << 0x00)  /*!< The gyroscope range +/-250 dps, 131.2 LSB/dps.     */
#define BMI270_GYR_RANGE_125        (0x04 << 0x00)  /*!< The gyroscope range +/-125 dps, 262.4 LSB/dps.     */
#define BMI270_GYR_OIS_MASK         (0x01 << 0x03)  /*!< The gyroscope ois range mask.                      */
#define BMI270_GYR_OIS_250          (0x00 << 0x03)  /*!< The gyroscope ois +/-250dps,  131.2 LSB/dps.       */
#define BMI270_GYR_OIS_2000         (0x01 << 0x03)  /*!< The gyroscope ois +/-2000dps, 16.4  LSB/dps.       */

///
/// \brief The bmi270 PWR_CONF register fields.
///
#define BMI270_PWR_CONF_APS_MASK    (0x01 << 0x00)  /*!< The power conf advanced power save mask.           */
#define BMI270_PWR_CONF_APS_OFF     (0x00 << 0x00)  /*!< The advanced power save off.                       */
#define BMI270_PWR_CONF_APS_ON      (0x01 << 0x00)  /*!< The advanced power save on.                        */
#define BMI270_PWR_CONF_FSW_MASK    (0x01 << 0x01)  /*!< The power conf FIFO read disable in lp mode mask.  */
#define BMI270_PWR_CONF_FSW_OFF     (0x00 << 0x01)  /*!< The FIFO read disabled in lp mode.                 */
#define BMI270_PWR_CONF_FSW_ON      (0x01 << 0x01)  /*!< The FIFO read enabled in lp mode after FIFO int.   */
#define BMI270_PWR_CONF_FUP_MASK    (0x01 << 0x02)  /*!< The fast power up enabled mask.                    */
#define BMI270_PWR_CONF_FUP_OFF     (0x00 << 0x02)  /*!< The fast power up disabled.                        */
#define BMI270_PWR_CONF_FUP_ON      (0x01 << 0x02)  /*!< The fast power up enabled.                         */

///
/// \brief The bmi270 PWR_CTRL register fields.
///
#define BMI270_PWR_CTRL_AUX_MASK    (0x01 << 0x00)  /*!< The bmi270 power control auxiliary sensor mask.    */
#define BMI270_PWR_CTRL_AUX_OFF     (0x00 << 0x00)  /*!< The auxiliary sensor off.                          */
#define BMI270_PWR_CTRL_AUX_ON      (0x01 << 0x00)  /*!< The auxiliary sensor on.                           */
#define BMI270_PWR_CTRL_GYR_MASK    (0x01 << 0x01)  /*!< The bmi270 power control gyroscope mask.           */
#define BMI270_PWR_CTRL_GYR_OFF     (0x00 << 0x01)  /*!< The gyroscope off.                                 */
#define BMI270_PWR_CTRL_GYR_ON      (0x01 << 0x01)  /*!< The gyroscope on.                                  */
#define BMI270_PWR_CTRL_ACC_MASK    (0x01 << 0x02)  /*!< The bmi270 power control accelerometer mask.       */
#define BMI270_PWR_CTRL_ACC_OFF     (0x00 << 0x02)  /*!< The accelerometer off.                             */
#define BMI270_PWR_CTRL_ACC_ON      (0x01 << 0x02)  /*!< The accelerometer on.                              */
#define BMI270_PWR_CTRL_TEMP_MASK   (0x01 << 0x03)  /*!< The bmi270 power control temperature sensor mask.  */
#define BMI270_PWR_CTRL_TEMP_OFF    (0x00 << 0x03)  /*!< The temperature sensor off.                        */
#define BMI270_PWR_CTRL_TEMP_ON     (0x01 << 0x03)  /*!< The temperature sensor on.                         */

///
/// \brief The bmi270 instance type.
///
typedef struct bmi270 bmi270_t;

///
/// \breif The bmi270 result type.
///
typedef enum bmi270_result
{
    BMI270_RESULT_SUCCESS = 0,
    BMI270_RESULT_ERROR,
} bmi270_result_t;

///
/// \breif The bmi270 status type.
///
typedef enum bmi270_status
{
    BMI270_STATUS_DEINIT = 0,
    BMI270_STATUS_INIT,
} bmi270_status_t;

///
/// \breif Gets the bmi270 instance.
///
/// \return bmi270_t The bmi270 instance address.
///
bmi270_t* bmi270_get_instance(void);

///
/// \breif Initializes the bmi270.
///
/// \param[in] bmi270             The bmi270 instance.
///
/// \return bmi270_result_t       The bmi270 result.
/// \retval BMI270_RESULT_SUCCESS On success.
/// \retval BMI270_RESULT_ERROR   Otherwise.
///
bmi270_result_t bmi270_init(bmi270_t *const bmi270);

///
/// \breif Deinitializes the bmi270.
///
/// \param[in] bmi270             The bmi270 instance.
///
/// \return bmi270_result_t       The bmi270 result.
/// \retval BMI270_RESULT_SUCCESS On success.
/// \retval BMI270_RESULT_ERROR   Otherwise.
///
bmi270_result_t bmi270_deinit(bmi270_t *const bmi270);

///
/// \brief Self-tests accelerometer.
///
/// \return bmi270_result_t       The bmi270 result.
/// \retval BMI270_RESULT_SUCCESS On success.
/// \retval BMI270_RESULT_ERROR   Otherwise.
///
bmi270_result_t bmi270_accel_self_test(void);

///
/// \brief Self-tests gyroscope.
///
/// \return bmi270_result_t       The bmi270 result.
/// \retval BMI270_RESULT_SUCCESS On success.
/// \retval BMI270_RESULT_ERROR   Otherwise.
///
bmi270_result_t bmi270_gyro_self_test(void);

#endif  /* _BMI270_H */
