#include "pid.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The PID controller term structure.
///
struct pid_term
{
    float32_t k;
    float32_t val;
};

///
/// \brief The PID controller struct.
///
struct pid
{
    struct pid_term p;
    struct pid_term i;
    struct pid_term d;
    float32_t dt;
    float32_t err;
    float32_t u;
};

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void pid_init(struct pid *const handle, const float32_t kp, const float32_t ki, const float32_t kd,
        const float32_t dt)
{
    if (handle == NULL)
    {
        return;
    }

    handle->p.k   = kp;
    handle->p.val = 0.0f;
    handle->i.k   = ki;
    handle->i.val = 0.0f;
    handle->d.k   = kd;
    handle->d.val = 0.0f;
    handle->dt    = dt;
    handle->err   = 0.0f;
    handle->u     = 0.0f;
}

void pid_deinit(struct pid *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    handle->p.k   = 0.0f;
    handle->p.val = 0.0f;
    handle->i.k   = 0.0f;
    handle->i.val = 0.0f;
    handle->d.k   = 0.0f;
    handle->d.val = 0.0f;
    handle->dt    = 0.0f;
    handle->err   = 0.0f;
    handle->u     = 0.0f;
}

float32_t pid_update(struct pid *const handle, float32_t sp, float32_t pv)
{
    if (handle == NULL)
    {
        return 0.0f;
    }

    handle->err = sp - pv;

    handle->p.val  = handle->p.k * handle->err;
    handle->i.val += handle->i.k * handle->err * handle->dt;
    handle->d.val  = handle->d.k * handle->err / handle->dt;

    handle->u = handle->p.val + handle->i.val + handle->d.val;

    return handle->u;
}
