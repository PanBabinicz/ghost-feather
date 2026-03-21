#ifndef _CF_H
#define _CF_H

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef float float32_t;

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The complementary filter struct.
///
struct cf
{
    float32_t alpha;
    float32_t ang;
};

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
///
/// \brief Gets the angle of the complementary filter instance.
///
/// \param[in] handle The pointer to complementary filter.
///
/// \return float32_t The estimated angle.
///
static inline float32_t cf_get_ang(const struct cf *const handle)
{
    if (handle == NULL)
    {
        return 0.0f;
    }

    return handle->ang;
}

///
/// \brief Gets the alpha of the complementary filter instance.
///
/// \param[in] handle The pointer to complementary filter.
///
/// \return float32_t The alpha coefficient.
///
static inline float32_t cf_get_alpha(const struct cf *const handle)
{
    if (handle == NULL)
    {
        return 0.0f;
    }

    return handle->alpha;
}


///***********************************************************************************************************
/// Global functions - declaration.
///***********************************************************************************************************
///
/// \brief Initializes the complementary filter instance.
///
/// Sets the internal state of the complementary filter and prepares the
/// instance for angle estimation. This function should be called once before
/// using the filter.
///
/// \param[in] handle The pointer to complementary filter.
/// \param[in] alpha  The initial alpha value.
/// \param[in] ang    The initial angle value.
///
void cf_init(struct cf *const handle, const float32_t alpha, const float32_t ang);

///
/// \brief Updates the complementary filter with new sensor measuremets.
///
/// Performs one update step of the complementary filter using the gyroscope
/// angular rate and the accelerometer-derived angle. The gyroscope data is
/// integrated over time while the accelerometer provides long-term correction.
///
/// \param[in] handle    The pointer to complementary filter.
/// \param[in] gyro_rate The angular rate from gyroscope.
/// \param[in] accel_ang The angle estimated from accelerometer.
/// \param[in] dt        The time step since the last update in seconds.
///
void cf_update(struct cf *const handle, const float32_t gyro_rate, const float32_t accel_ang, const float32_t dt);

///
/// \brief Sets the angle of the complementary filter instance.
///
/// \param[in] handle The pointer to complementary filter.
/// \param[in] ang    The angle value.
///
void cf_set_ang(struct cf *const handle, const float32_t ang);

///
/// \brief Sets the alpha of the complementary filter instance.
///
/// \param[in] handle The pointer to complementary filter.
/// \param[in] alpha  The alpha coefficient.
///
void cf_set_alpha(struct cf *const handle, const float32_t alpha);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _CF_H */
