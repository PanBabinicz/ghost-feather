#include "cf.h"

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The complementary filters array.
///
static struct cf cf_arr[CF_INST_TOTAL];

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

void cf_deinit(struct cf *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    handle->alpha = 0.0f;
    handle->ang   = 0.0f;
}

struct cf* cf_get(const cf_inst_t inst)
{
    if ((inst < CF_INST_BEGIN) || (inst >= CF_INST_TOTAL))
    {
        return NULL;
    }

    return &cf_arr[inst];
}

void cf_fuse(struct cf *const handle, const float32_t pred_ang, const float32_t acc_ang)
{
    if (handle == NULL)
    {
        return;
    }

    float32_t err = acc_ang - pred_ang;

    /* Wrap the error (180-degree protection). */
    if (err > 180.0f)
    {
        err -= 360.0f;
    }

    if (err < -180.0f)
    {
        err += 360.0f;
    }

    handle->ang   = pred_ang + ((1.0f - handle->alpha) * err);

    /* Final wrap. */
    if (handle->ang > 180.0f)
    {
        handle->ang -= 360.0f;
    }

    if (handle->ang < -180.0f)
    {
        handle->ang += 360.0f;
    }
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
