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
#define BMI270_REG_ACC_CONF             (0x40)      /*!< Accel ODR, bandwidth, and mode config.             */
#define BMI270_REG_ACC_RANGE            (0x41)      /*!< Selection of the accelerometer g-range.            */
#define BMI270_REG_GYRO_CONF            (0x42)      /*!< .                      */
#define BMI270_REG_GYRO_RANGE           (0x43)      /*!< .                      */
#define BMI270_REG_AUX_CONF             (0x44)      /*!< .                      */
#define BMI270_REG_FIFO_DOWNS           (0x45)      /*!< .                      */
#define BMI270_REG_FIFO_WTM_0           (0x46)      /*!< .                      */
#define BMI270_REG_FIFO_WTM_1           (0x47)      /*!< .                      */
#define BMI270_REG_FIFO_FIG_0           (0x48)      /*!< .                      */
#define BMI270_REG_FIFO_FIG_1           (0x49)      /*!< .                      */
#define BMI270_REG_SATURATION           (0x4a)      /*!< .                      */
#define BMI270_REG_AUX_DEV_ID           (0x4b)      /*!< .                      */
#define BMI270_REG_AUX_IF_CONF          (0x4c)      /*!< .                      */
#define BMI270_REG_AUX_RD_ADDR          (0x4d)      /*!< .                      */
#define BMI270_REG_AUX_WR_ADDR          (0x4e)      /*!< .                      */
#define BMI270_REG_AUX_WR_DATA          (0x4f)      /*!< .                      */
#define BMI270_REG_ERR_REG_MSK          (0x52)      /*!< .                      */
#define BMI270_REG_INT1_IO_CTRL         (0x53)      /*!< .                      */
#define BMI270_REG_INT2_IO_CTRL         (0x54)      /*!< .                      */
#define BMI270_REG_INT_LATCH            (0x55)      /*!< .                      */
#define BMI270_REG_INT1_MAP_FEAT        (0x56)      /*!< .                      */
#define BMI270_REG_INT2_MAP_FEAT        (0x57)      /*!< .                      */
#define BMI270_REG_INT_MAP_DATA         (0x58)      /*!< .                      */
#define BMI270_REG_INIT_CTRL            (0x59)      /*!< .                      */
#define BMI270_REG_INIT_ADDR_0          (0x5b)      /*!< .                      */
#define BMI270_REG_INIT_ADDR_1          (0x5c)      /*!< .                      */
#define BMI270_REG_INIT_DATA            (0x5e)      /*!< .                      */
#define BMI270_REG_INTERNAL_ERROR       (0x5f)      /*!< .                      */
#define BMI270_REG_AUX_IF_TRIM          (0x68)      /*!< .                      */
#define BMI270_REG_GYR_CRT_CONF         (0x69)      /*!< .                      */
#define BMI270_REG_NVM_CONF             (0x6a)      /*!< .                      */
#define BMI270_REG_IF_CONF              (0x6b)      /*!< .                      */
#define BMI270_REG_DRV                  (0x6c)      /*!< .                      */
#define BMI270_REG_ACC_SELF_TEST        (0x6d)      /*!< .                      */
#define BMI270_REG_GYR_SELF_TEST_AXES   (0x6e)      /*!< .                      */
#define BMI270_REG_NV_CONF              (0x70)      /*!< .                      */
#define BMI270_REG_OFFSET_0             (0x71)      /*!< .                      */
#define BMI270_REG_OFFSET_1             (0x72)      /*!< .                      */
#define BMI270_REG_OFFSET_2             (0x73)      /*!< .                      */
#define BMI270_REG_OFFSET_3             (0x74)      /*!< .                      */
#define BMI270_REG_OFFSET_4             (0x75)      /*!< .                      */
#define BMI270_REG_OFFSET_5             (0x76)      /*!< .                      */
#define BMI270_REG_OFFSET_6             (0x77)      /*!< .                      */
#define BMI270_REG_PWR_CONF             (0x7c)      /*!< .                      */
#define BMI270_REG_PWR_CTRL             (0x7d)      /*!< .                      */
#define BMI270_REG_CMD                  (0x7e)      /*!< .                      */

#endif  /* _BMI270_H */
