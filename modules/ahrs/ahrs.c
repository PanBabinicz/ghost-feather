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
static struct ahrs_dev ahrs;

///
/// \brief
///
static const float32_t rad_in_deg = (180 / M_PI);

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
struct ahrs_dev* ahrs_dev_get(void)
{
    return &ahrs;
}

void ahrs_ang_calc(int16_t x, int16_t y, int16_t z)
{
    struct ahrs_dev *dev = &ahrs;

    float32_t norm   = sqrtf((x * x) + (y * y) + (z * z));
    float32_t x_norm = x / norm;
    float32_t y_norm = y / norm;
    float32_t z_norm = z / norm;

    dev->acc.axes.roll  = atan2(y_norm, z_norm);
    dev->acc.axes.pitch = atan2((-x_norm), (sqrtf(pow(y_norm, 2) + pow(z_norm, 2))));

    dev->acc.axes.roll  *= rad_in_deg;
    dev->acc.axes.pitch *= rad_in_deg;
}
