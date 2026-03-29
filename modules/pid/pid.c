#include "pid.h"
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The PID controller error structure.
///
struct pid_err
{
    float32_t curr;
    float32_t prev;
};

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
    struct pid_err  err;
    float32_t dt;
    float32_t u;
};

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The PID controllers array.
///
static struct pid pid_arr[PID_INST_TOTAL];

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

    handle->p.k      = kp;
    handle->p.val    = 0.0f;
    handle->i.k      = ki;
    handle->i.val    = 0.0f;
    handle->d.k      = kd;
    handle->d.val    = 0.0f;
    handle->err.curr = 0.0f;
    handle->err.prev = 0.0f;
    handle->dt       = dt;
    handle->u        = 0.0f;
}

void pid_deinit(struct pid *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    handle->p.k      = 0.0f;
    handle->p.val    = 0.0f;
    handle->i.k      = 0.0f;
    handle->i.val    = 0.0f;
    handle->d.k      = 0.0f;
    handle->d.val    = 0.0f;
    handle->err.curr = 0.0f;
    handle->err.prev = 0.0f;
    handle->dt       = 0.0f;
    handle->u        = 0.0f;
}

struct pid* pid_get(const pid_inst_t inst)
{
    if ((inst < PID_INST_BEGIN) || (inst >= PID_INST_TOTAL))
    {
        return NULL;
    }

    return &pid_arr[inst];
}

float32_t pid_update(struct pid *const handle, float32_t sp, float32_t pv)
{
    if (handle == NULL)
    {
        return 0.0f;
    }

    handle->err.curr = sp - pv;

    handle->p.val  = handle->p.k * handle->err.curr;

    handle->i.val += handle->i.k * handle->err.curr * handle->dt;
    handle->i.val  = (handle->i.val >  0.15f) ?  0.15f : handle->i.val;
    handle->i.val  = (handle->i.val < -0.15f) ? -0.15f : handle->i.val;

    handle->d.val  = handle->d.k * (handle->err.curr - handle->err.prev) / handle->dt;

    handle->u = handle->p.val + handle->i.val + handle->d.val;
    handle->u = (handle->u  >  1.0f) ?  1.0f : handle->u;
    handle->u = (handle->u  < -1.0f) ? -1.0f : handle->u;

    handle->err.prev = handle->err.curr;

    return handle->u;
}
