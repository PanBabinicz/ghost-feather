#ifndef _AHRS_H
#define _AHRS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef float float32_t;

///
/// \brief
///
struct ahrs_ang
{
    float32_t roll;
    float32_t pitch;
    float32_t yaw;
};

///
/// \brief
///
struct ahrs_axis
{
    float32_t x;
    float32_t y;
    float32_t z;
};

///
/// \brief
///
struct ahrs_acc
{
    struct ahrs_ang ang;
    struct ahrs_axis axis;
    float32_t norm;
};

///
/// \brief
///
struct ahrs_gyr
{
    struct ahrs_ang ang;
    struct ahrs_axis axis;
};

///
/// \brief
///
struct ahrs_arg
{
    struct ahrs_acc acc;
    struct ahrs_gyr gyr;
};

///
/// \brief
///
struct ahrs_dev
{
    struct ahrs_arg arg;
};

///
/// brief
///
struct ahrs_dev* ahrs_dev_get(void);

///
/// brief
///
void ahrs_acc_norm(int16_t x, int16_t y, int16_t z);

///
/// brief
///
void ahrs_ang_calc(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _AHRS_H */
