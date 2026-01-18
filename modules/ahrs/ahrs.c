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

void ahrs_acc_norm(int16_t x, int16_t y, int16_t z)
{
    struct ahrs_dev *dev = &ahrs;

    dev->arg.acc.norm = sqrtf((x * x) + (y * y) + (z * z));

    dev->arg.acc.axis.x = x / dev->arg.acc.norm;
    dev->arg.acc.axis.y = y / dev->arg.acc.norm;
    dev->arg.acc.axis.z = z / dev->arg.acc.norm;
}

void ahrs_ang_calc(void)
{
    struct ahrs_dev *dev = &ahrs;

    dev->arg.acc.ang.roll  = atan2(dev->arg.acc.axis.y, dev->arg.acc.axis.z);
    dev->arg.acc.ang.pitch = atan2((-dev->arg.acc.axis.x), (sqrtf(pow(dev->arg.acc.axis.y, 2) + pow(dev->arg.acc.axis.z, 2))));

    dev->arg.acc.ang.roll  *= rad_in_deg;
    dev->arg.acc.ang.pitch *= rad_in_deg;
}
