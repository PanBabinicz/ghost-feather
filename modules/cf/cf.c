#include "cf.h"

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
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The complementary filters array.
///
static struct cf cf_arr[CF_INST_TOTAL] =
{
    [CF_INST_ROLL]  = { .alpha = 0.95, .ang = 0.0 },
    [CF_INST_PITCH] = { .alpha = 0.95, .ang = 0.0 },
};

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void cf_init(const cf_inst_t inst, const float32_t alpha, const float32_t ang)
{
    struct cf *dev = &cf_arr[inst];

    dev->alpha = alpha;
    dev->ang   = ang;
}

void cf_update(const cf_inst_t inst, const float32_t gyro_rate, const float32_t accel_ang, const float32_t dt)
{
    struct cf *dev = &cf_arr[inst];
    float32_t gyro_ang = dev->ang + (gyro_rate * dt);

    dev->ang = (dev->alpha * gyro_ang) + ((1.0f - dev->alpha) * accel_ang);
}

float32_t cf_ang_get(const cf_inst_t inst)
{
    struct cf *dev = &cf_arr[inst];

    return dev->ang;
}

void cf_ang_set(const cf_inst_t inst, const float32_t ang)
{
    struct cf *dev = &cf_arr[inst];

    dev->ang = ang;
}

float32_t cf_alpha_get(const cf_inst_t inst)
{
    struct cf *dev = &cf_arr[inst];

    return dev->alpha;
}

void cf_alpha_set(const cf_inst_t inst, const float32_t alpha)
{
    struct cf *dev = &cf_arr[inst];

    dev->alpha = alpha;
}
