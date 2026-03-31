#ifndef _GHF_H
#define _GHF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The ghf time structure.
///
struct ghf_time
{
    uint32_t start;
    uint32_t stop;
    uint32_t total;
};

///
/// \brief The ghf data structure.
///
struct ghf_data
{
    struct ghf_time time;
    float32_t roll;
    float32_t pitch;
    float32_t throttle;
    float32_t yaw;
    uint32_t  pwm1;
    uint32_t  pwm2;
    uint32_t  pwm3;
    uint32_t  pwm4;
    struct ahrs_raw_data raw_data;
    struct ahrs_calib calib;
};

///
/// \brief The ghf config structure.
///
struct ghf_config
{
    float32_t kp;
    float32_t ki;
    float32_t kd;
    float32_t acc_scale;
    float32_t gyr_scale;
    float32_t alpha;
    float32_t dt;
};

///
/// \brief The ghf module structure.
///
struct ghf_module
{
    struct ahrs  *ahrs;
    struct rc    *rc_1;
    struct rc    *rc_2;
    struct rc    *rc_3;
    struct rc    *rc_4;
    struct rc    *rc_5;
    struct rc    *rc_6;
    struct motor *motor_1;
    struct motor *motor_2;
    struct motor *motor_3;
    struct motor *motor_4;
    struct pid   *pid_roll;
    struct pid   *pid_pitch;
    struct pid   *pid_yaw;
};

///
/// \brief The ghf structure.
///
struct ghf
{
    struct ghf_module module;
    struct ghf_config config;
    struct ghf_data   data;
};

///
/// \brief The 32-bit floating-ponit type.
///
typedef float float32_t;

///
/// \brief Initializes the ghf.
///
/// \param[in] The pointer to ghf.
///
void ghf_init(struct ghf *const handle);

///
/// \brief Deinitializes the ghf.
///
/// \param[in] The pointer to ghf.
///
void ghf_deinit(struct ghf *const handle);

///
/// \brief Setups the ghf.
///
/// \param[in] The pointer to ghf.
///
void ghf_setup(struct ghf *const handle);

///
/// \brief Gets the ghf.
///
/// \return struct ghf* The ghf pointer.
///
struct ghf* ghf_get(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _GHF_H */

