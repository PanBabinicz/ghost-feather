#ifndef _AHRS_H
#define _AHRS_H

#include <stdint.h>
#include "cf.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef float float32_t;

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief
///
struct ahrs_acc
{
    float32_t roll;
    float32_t pitch;
    float32_t scale;
};

///
/// \brief
///
struct ahrs_gyr
{
    float32_t roll;
    float32_t pitch;
    float32_t yaw;
    float32_t scale;
    float32_t dt;
};

///
/// \brief
///
struct ahrs_out
{
    float32_t roll;
    float32_t pitch;
    float32_t yaw;
}

///
/// \brief
///
struct ahrs_raw_data
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
};

///
/// \brief
///
struct ahrs
{
    struct ahrs_acc acc;
    struct ahrs_gyr gyr;
    struct ahrs_out out;
    struct cf cf_roll;
    struct cf cf_pitch;
};

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief
///
static inline float32_t ahrs_get_roll_ang(const struct ahrs *const handle);

///
/// \brief
///
static inline float32_t ahrs_get_pitch_ang(const struct ahrs *const handle);

///
/// \brief
///
static inline float32_t ahrs_get_yaw_ang(const struct ahrs *const handle);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static inline float32_t ahrs_get_roll_ang(const struct ahrs *const handle)
{
    if (handle == NULL)
    {
        return 0.0f;
    }

    return handle->out.roll;
}

static inline float32_t ahrs_get_pitch_ang(const struct ahrs *const handle)
{
    if (handle == NULL)
    {
        return 0.0f;
    }

    return handle->out.pitch;
}

static inline float32_t ahrs_get_yaw_ang(const struct ahrs *const handle)
{
    if (handle == NULL)
    {
        return 0.0f;
    }

    return handle->out.yaw;
}

///***********************************************************************************************************
/// Global functions - declaration.
///***********************************************************************************************************
///
/// \brief
///
void ahrs_init(struct ahrs *const handle, const float32_t acc_scale, const float32_t gyr_scale,
        const float32_t alpha, const float32_t dt);

///
/// \brief
///
void ahrs_deinit(struct ahrs *const handle);

///
/// \brief
///
void ahrs_update(struct ahrs *const handle, struct ahrs_raw_data *const data);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _AHRS_H */
