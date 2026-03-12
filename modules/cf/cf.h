#ifndef _CF_H
#define _CF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef float float32_t;

///
/// \brief The complementary filter instance type.
///
typedef enum cf_inst
{
    CF_INST_BEGIN = 0,
    CF_INST_ROLL  = 0,
    CF_INST_PITCH,
    CF_INST_TOTAL,
} cf_inst_t;

///
/// \brief Initializes the complementary filter instance.
///
/// Sets the internal state of the complementary filter and prepares the
/// instance for angle estimation. This function should be called once before
/// using the filter.
///
/// \param[in] inst  The complementary filter instance.
/// \param[in] alpha The initial alpha value.
/// \param[in] ang   The initial angle value.
///
void cf_init(const cf_inst_t inst, const float32_t alpha, const float32_t ang);

///
/// \brief Updates the complementary filter with new sensor measuremets.
///
/// Performs one update step of the complementary filter using the gyroscope
/// angular rate and the accelerometer-derived angle. The gyroscope data is
/// integrated over time while the accelerometer provides long-term correction.
///
/// \param[in] inst      The complementary filter instance.
/// \param[in] gyro_rate The angular rate from gyroscope.
/// \param[in] accel_ang The angle estimated from accelerometer.
/// \param[in] dt        The time step since the last update in seconds.
///
void cf_update(const cf_inst_t inst, const float32_t gyro_rate, const float32_t accel_ang, const float32_t dt);

///
/// \brief Gets the angle of the complementary filter instance.
///
/// \param[in] inst The complementary filter instance.
///
/// \return float32_t The estimated angle.
///
float32_t cf_ang_get(const cf_inst_t inst);

///
/// \brief Sets the angle of the complementary filter instance.
///
/// \param[in] inst The complementary filter instance.
/// \param[in] ang  The angle value.
///
void cf_ang_set(const cf_inst_t inst, const float32_t ang);

///
/// \brief Gets the alpha of the complementary filter instance.
///
/// \param[in] inst The complementary filter instance.
///
/// \return float32_t The alpha coefficient.
///
float32_t cf_alpha_get(const cf_inst_t inst);

///
/// \brief Sets the alpha of the complementary filter instance.
///
/// \param[in] inst  The complementary filter instance.
/// \param[in] alpha The alpha coefficient.
///
void cf_alpha_set(const cf_inst_t inst, const float32_t alpha);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _CF_H */
