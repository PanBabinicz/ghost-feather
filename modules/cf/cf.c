#include "cf.h"

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void cf_init(struct cf *const handle, const float32_t alpha, const float32_t ang)
{
    if (handle == NULL)
    {
        return;
    }

    handle->alpha = alpha;
    handle->ang   = ang;
}

void cf_update(struct cf *const handle, const float32_t gyro_rate, const float32_t accel_ang, const float32_t dt)
{
    if (handle == NULL)
    {
        return;
    }

    float32_t gyro_ang = handle->ang + (gyro_rate * dt);

    handle->ang = (handle->alpha * gyro_ang) + ((1.0f - handle->alpha) * accel_ang);
}

void cf_set_ang(struct cf *const handle, const float32_t ang)
{
    if (handle == NULL)
    {
        return;
    }

    handle->ang = ang;
}


void cf_set_alpha(struct cf *const handle, const float32_t alpha)
{
    if (handle == NULL)
    {
        return;
    }

    handle->alpha = alpha;
}
