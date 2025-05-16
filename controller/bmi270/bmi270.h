#ifndef _BMI270_H
#define _BMI270_H

#include <stdint.h>

///
/// \breif BMI270 registers definition.
///
#define BMI270_REGISTER_CHIP_ID (0x00)      /* Chip identification code.        */
#define BMI270_REGISTER_ERR_REG (0x02)      /* Reports sensor error condition.  */
#define BMI270_REGISTER_STATUS  (0x03)      /* Sensor status flags.             */
#define BMI270_REGISTER_DATA_0  (0x04)      /* AUX_X(LSB).                      */
#define BMI270_REGISTER_DATA_1  (0x05)      /* AUX_X(MSB).                      */
#define BMI270_REGISTER_DATA_2  (0x06)      /* AUX_Y(LSB).                      */ 
#define BMI270_REGISTER_DATA_3  (0x07)      /* AUX_Y(MSB).                      */
#define BMI270_REGISTER_DATA_4  (0x08)      /* AUX_Z(LSB).                      */
#define BMI270_REGISTER_DATA_5  (0x09)      /* AUX_Z(MSB).                      */
#define BMI270_REGISTER_DATA_6  (0x0a)      /* AUX_R(LSB).                      */
#define BMI270_REGISTER_DATA_7  (0x0b)      /* AUX_R(MSB).                      */
#define BMI270_REGISTER_DATA_8  (0x0c)      /* ACC_X(LSB).                      */
#define BMI270_REGISTER_DATA_9  (0x0d)      /* ACC_X(MSB).                      */
#define BMI270_REGISTER_DATA_10 (0x0e)      /* ACC_Y(LSB).                      */
#define BMI270_REGISTER_DATA_11 (0x0f)      /* ACC_Y(MSB).                      */
#define BMI270_REGISTER_DATA_12 (0x10)      /* ACC_Z(LSB).                      */
#define BMI270_REGISTER_DATA_13 (0x11)      /* ACC_Z(MSB).                      */
#define BMI270_REGISTER_DATA_14 (0x12)      /* GYR_X(LSB).                      */
#define BMI270_REGISTER_DATA_15 (0x13)      /* GYR_X(MSB).                      */
#define BMI270_REGISTER_DATA_16 (0x14)      /* GYR_Y(LSB).                      */
#define BMI270_REGISTER_DATA_17 (0x15)      /* GYR_Y(MSB).                      */
#define BMI270_REGISTER_DATA_18 (0x16)      /* GYR_Z(LSB).                      */
#define BMI270_REGISTER_DATA_19 (0x17)      /* GYR_Z(MSB).                      */

#endif  /* _BMI270_H */
