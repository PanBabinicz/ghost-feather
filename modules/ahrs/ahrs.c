#include "ahrs.h"
#include <math.h>

#ifndef M_PI
#define M_PI    (3.1415926535f)
#endif  /* M_PI */

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief
///
static const float32_t rad_in_deg = (180 / M_PI);

///
/// \brief
///
static struct ahrs ahrs;

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief
///
static void ahrs_calc_acc_ang(struct ahrs *const handle, float32_t ax, float32_t ay, float32_t az);

///
/// \brief
///
static void ahrs_calc_gyr_ang(struct ahrs *const handle, float32_t gx, float32_t gy, float32_t gz);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static void ahrs_calc_acc_ang(struct ahrs *const handle, float32_t ax, float32_t ay, float32_t az)
{
    float32_t norm_sq = ((ax * ax) + (ay * ay) + (az * az));

    if ((norm_sq < 0.25f) || (norm_sq > 2.25f))
    {
        return;
    }

    handle->acc.roll  = atan2(ay, az);
    handle->acc.pitch = atan2((-ax), sqrtf((ay*ay) + (az*az)));

    handle->acc.roll  *= rad_in_deg;
    handle->acc.pitch *= rad_in_deg;
}

static void ahrs_calc_gyr_ang(struct ahrs *const handle, float32_t gx, float32_t gy, float32_t gz)
{
    handle->gyr.roll  += gx * handle->gyr.dt;
    handle->gyr.pitch += gy * handle->gyr.dt;

    if ((gz < 0.1f) && (gz > -0.1f))
    {
        gz = 0.0f;
    }

    handle->gyr.yaw += gz * handle->gyr.dt;
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void ahrs_init(struct ahrs *const handle, const float32_t acc_scale, const float32_t gyr_scale,
        const float32_t alpha, const float32_t dt)
{
    if (handle == NULL)
    {
        return;
    }

    handle->acc.roll  = 0.0f;
    handle->acc.pitch = 0.0f;
    handle->acc.scale = acc_scale;

    handle->gyr.roll  = 0.0f;
    handle->gyr.pitch = 0.0f;
    handle->gyr.yaw   = 0.0f;
    handle->gyr.scale = gyr_scale;
    handle->gyr.dt    = dt;

    handle->out.roll  = 0.0f;
    handle->out.pitch = 0.0f;
    handle->out.yaw   = 0.0f;

    handle->cf_roll  = cf_get(CF_INST_ROLL);
    handle->cf_pitch = cf_get(CF_INST_PITCH);

    cf_init(handle->cf_roll,  alpha, 0.0f);
    cf_init(handle->cf_pitch, alpha, 0.0f);
}

void ahrs_deinit(struct ahrs *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    memset(handle, 0, sizeof(struct ahrs));
}

struct ahrs* ahrs_get(void)
{
    return &ahrs;
}

void ahrs_update(struct ahrs *const handle, struct ahrs_raw_data *const data)
{
    if ((handle == NULL) || (data == NULL))
    {
        return;
    }

    float32_t axf = (float32_t)data->ax * handle->acc.scale;
    float32_t ayf = (float32_t)data->ay * handle->acc.scale;
    float32_t azf = (float32_t)data->az * handle->acc.scale;
    float32_t gxf = (float32_t)data->gx * handle->gyr.scale;
    float32_t gyf = (float32_t)data->gy * handle->gyr.scale;
    float32_t gzf = (float32_t)data->gz * handle->gyr.scale;

    handle->gyr.roll  = handle->out.roll;
    handle->gyr.pitch = handle->out.pitch;

    ahrs_calc_acc_ang(handle, axf, ayf, azf);
    ahrs_calc_gyr_ang(handle, gxf, gyf, gzf);

    cf_fuse(handle->cf_roll,  handle->gyr.roll,  handle->acc.roll);
    cf_fuse(handle->cf_pitch, handle->gyr.pitch, handle->acc.pitch);

    handle->out.roll  = cf_get_ang(handle->cf_roll);
    handle->out.pitch = cf_get_ang(handle->cf_pitch);

    handle->out.yaw = handle->gyr.yaw;

    if (handle->out.yaw > 180.0f)
    {
        handle->out.yaw -= 360.0f;
    }

    if (handle->out.yaw < -180.0f)
    {
        handle->out.yaw += 360.0f;
    }
}
