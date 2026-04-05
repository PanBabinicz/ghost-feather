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
/// \brief The ahrs accelerometer related processed data with scale settings.
///
struct ahrs_acc
{
    float32_t roll;
    float32_t pitch;
    float32_t scale;
};

///
/// \brief The ahrs gyroscope related processed data with scale settings and time step.
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
/// \brief The ahrs output angles.
///
struct ahrs_out
{
    float32_t roll;
    float32_t pitch;
    float32_t yaw;
};

///
/// \brief The ahrs accelerometer and gyroscope raw data.
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
/// \brief The ahrs gyroscope calibration data.
///
struct ahrs_calib
{
    int16_t gx;
    int16_t gy;
    int16_t gz;
};

///
/// \brief The ahrs struct containing sensor data, outputs, and filter instances.
///
struct ahrs
{
    struct ahrs_acc acc;
    struct ahrs_gyr gyr;
    struct ahrs_out out;
    struct cf *cf_roll;
    struct cf *cf_pitch;
};

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief Gets the output roll angle.
///
/// \param[in] The pointer to ahrs.
///
/// \return float32_t The output roll angle.
///
static inline float32_t ahrs_get_roll_ang(const struct ahrs *const handle);

///
/// \brief Gets the output pitch angle.
///
/// \param[in] The pointer to ahrs.
///
/// \return float32_t The output pitch angle.
///
static inline float32_t ahrs_get_pitch_ang(const struct ahrs *const handle);

///
/// \brief Gets the output yaw angle.
///
/// \param[in] The pointer to ahrs.
///
/// \return float32_t The output yaw angle.
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
/// \brief Initializes the ahrs.
///
/// \param[in] handle    The pointer to ahrs.
/// \param[in] acc_scale The scale factor for accelerometer.
/// \param[in] gyr_scale The scale factor for gyroscope.
/// \param[in] alpha     The alpha factor for complementary filter.
/// \param[in] dt        The time step.
///
void ahrs_init(struct ahrs *const handle, const float32_t acc_scale, const float32_t gyr_scale,
        const float32_t alpha, const float32_t dt);

///
/// \brief Deinitializes the ahrs. The ahrs is zero initialized.
///
/// \param[in] handle The pointer to ahrs.
///
void ahrs_deinit(struct ahrs *const handle);

///
/// \brief Gets the ahrs object.
///
/// \return struct ahrs* The ahrs object.
///
struct ahrs* ahrs_get(void);

///
/// \brief Updates the ahrs output.
///
/// \param[in] handle The pointer to ahrs.
/// \param[in] data   The ahrs accelerometer and gyroscope raw data.
///
void ahrs_update(struct ahrs *const handle, struct ahrs_raw_data *const data);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _AHRS_H */
