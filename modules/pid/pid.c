#include "pid.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief The PID controller struct.
///
struct pid
{
    float32_t kp;
    float32_t ki;
    float32_t kd;
    float32_t err;
    float32_t out;
};

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The PID controllers array.
///
static struct pid pid_arr[PID_INST_TOTAL] =
{
    [PID_INST_ROLL]  = { .kp = 0.0f, .ki = 0.0f, .kd = 0.0f, .err = 0.0f },
    [PID_INST_PITCH] = { .kp = 0.0f, .ki = 0.0f, .kd = 0.0f, .err = 0.0f },
};

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void pid_init(const pid_inst_t inst, const float32_t kp, const float32_t ki, const float32_t kd)
{
    struct pid *dev = &pid_arr[inst];

    dev->kp = kp;
    dev->ki = ki;
    dev->kd = kd;
}

void pid_deinit(const pid_inst_t inst)
{
    struct pid *dev = &pid_arr[inst];

    dev->kp = 0.0f;
    dev->ki = 0.0f;
    dev->kd = 0.0f;
}

float32_t pid_update(const pid_inst_t inst, float32_t err)
{
    struct pid *dev = &pid_arr[inst];

    dev->out = (dev->kp * err) + (dev->ki * err * dt) + 
}
