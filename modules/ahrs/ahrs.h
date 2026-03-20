#ifndef _AHRS_H
#define _AHRS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef float float32_t;

///
/// \brief The AHRS axis type.
///
typedef enum ahrs_rot_axis
{
    AHRS_ROT_AXIS_ROLL = 0,
    AHRS_ROT_AXIS_PITCH,
    AHRS_ROT_AXIS_YAW,
} ahrs_rot_axis_t;

///
/// \brief
///
struct ahrs_rot_axes
{
    float32_t roll;
    float32_t pitch;
    float32_t yaw;
};

///
/// \brief
///
struct ahrs_acc
{
    struct ahrs_rot_axes axes;
};

///
/// \brief
///
struct ahrs_gyr
{
    struct ahrs_rot_axes axes;
};

///
/// \brief
///
struct ahrs_dev
{
    struct ahrs_acc acc;
    struct ahrs_gyr gyr;
};

///
/// brief
///
struct ahrs_dev* ahrs_dev_get(void);

///
/// brief
///
void ahrs_ang_calc(int16_t x, int16_t y, int16_t z);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _AHRS_H */
