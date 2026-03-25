#include "motor.h"
#include "rc.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The motor devices array.
///
static struct motor motor_arr[MOTOR_INST_TOTAL];

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void motor_init(struct motor *const handle, const tim_inst_t inst, const ll_tim_ccr_ch_t ch)
{
    if (handle == NULL)
    {
        return;
    }

    /* TODO: Change tim_dev_arr_get() to tim_get() */
    struct tim_dev *tim_dev_arr = tim_dev_arr_get();

    handle->tim    = &tim_dev_arr[inst];
    handle->ccr_ch = ch;
}

void motor_deinit(struct motor *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    memset(handle, 0, sizeof(struct motor));
}

struct motor* motor_get(const motor_inst_t inst)
{
    if ((inst < MOTOR_INST_BEGIN) || (inst >= MOTOR_INST_TOTAL))
    {
        return NULL;
    }

    return &motor_arr[inst];
}

void motor_update(const struct motor *const handle, const uint32_t pwm)
{
    if (handle == NULL)
    {
        return;
    }

    handle->tim->ccr_set(handle->tim->tim, handle->ccr_ch, pwm);
}
