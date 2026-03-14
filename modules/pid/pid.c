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
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The PID controllers array.
///
static struct pid pid_arr[PID_INST_TOTAL] =
{
    [PID_INST_ROLL]  = { 0 },
    [PID_INST_PITCH] = { 0 },
};

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void pid_init(const pid_inst_t inst, const float32_t kp, const float32_t ki, const float32_t kd
        const float32_t dt)
{
    struct pid *dev = &pid_arr[inst];

    dev->p.k = kp;
    dev->i.k = ki;
    dev->d.k = kd;
    dev->dt  = dt;
}

void pid_deinit(const pid_inst_t inst)
{
    struct pid *dev = &pid_arr[inst];

    dev->p.k = 0.0f;
    dev->i.k = 0.0f;
    dev->d.k = 0.0f;
    dev->dt  = 0.0f;
    dev->err = 0.0f;
    dev->u   = 0.0f;
}

float32_t pid_update(const pid_inst_t inst, float32_t sp, float32_t pv)
{
    struct pid *dev = &pid_arr[inst];

    dev->err = sp - pv;

    dev->p.val  = dev->p.k * dev->err;
    dev->i.val += dev->i.k * dev->err * dev->dt;
    dev->d.val  = dev->d.k * dev->err / dev->dt;

    dev->u = dev->p.val + dev->i.val + dev->d.val;

    return dev->u;
}
