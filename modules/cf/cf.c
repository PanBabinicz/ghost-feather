#include "cf.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief
///
struct cf
{
    float alpha;
    float ang;
};

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief
///
static struct cf cf_arr[CF_INST_TOTAL] =
{
    [CF_INST_ROLL]  = { .alpha = 0.95, .ang = 0.0 },
    [CF_INST_PITCH] = { .alpha = 0.95, .ang = 0.0 },
};

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
cf_res_t cf_init(const cf_inst_t inst, const float alpha, const float ang)
{
    if ((inst < CF_INST_BEGIN) || (inst >= CF_INST_TOTAL))
    {
        return CF_STAT_ERR;
    }

    struct cf *dev = &cf_arr[inst];

    dev->alpha = alpha;
    dev->ang   = ang;

    return CF_STAT_OK;
}
