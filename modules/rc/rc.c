#include "rc.h"
#include <string.h>

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief The RC channels array.
///
static struct rc rc_arr[RC_CH_TOTAL];

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief Normalizes the input value to an asymmetric range defined by the given minimum and maximum limits.
///
/// \param[in] min The minimum normalization limit.
/// \param[in] max The maximum normalization limit.
/// \param[in] val The input value to be normalized.
///
/// \return Asymmetrically normalized 32-bit floating-point value.
///
static float32_t norm_asym_f32(const float32_t min, const float32_t max, const float32_t val);

///
/// \brief Normalizes the input value to a symmetric range defined by the given minimum and maximum limits.
///
/// \param[in] min The minimum normalization limit.
/// \param[in] max The maximum normalization limit.
/// \param[in] val The input value to be normalized.
///
/// \return Symmetrically normalized 32-bit floating-point value.
///
static float32_t norm_sym_f32(const float32_t min, const float32_t max, const float32_t val);

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static float32_t norm_asym_f32(const float32_t min, const float32_t max, const float32_t val)
{
    return ((val - min) / (max - min));
}

static float32_t norm_sym_f32(const float32_t min, const float32_t max, const float32_t val)
{
    return ((2 * ((val - min) / (max - min))) - 1);
}

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void rc_init(struct rc *const handle, const tim_inst_t inst, const ll_tim_ccr_ch_t ch)
{
    if (inst == NULL)
    {
        return;
    }

    /* TODO: Change tim_dev_arr_get() to tim_get() */
    struct tim_dev *tim_dev_arr = tim_dev_arr_get();

    handle->tim    = &tim_dev_arr[inst];
    handle->ccr_ch = ch;
}

void rc_deinit(struct rc *const handle)
{
    if (inst == NULL)
    {
        return;
    }

    memset(handle, 0, sizeof(struct rc));
}

struct rc* rc_get(const rc_ch_t ch)
{
    if ((ch < RC_CH_BEGIN) || (ch >= RC_CH_TOTAL))
    {
        return NULL;
    }

    return &rc_arr[ch];
}

void rc_sig_raw_gen(struct rc *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    handle->tim->ccr_data_get(handle->tim->tim, handle->ccr_ch, &handle->ccr_data);

    if (handle->ccr_data.curr > handle->ccr_data.prev)
    {
        handle->sig.raw = ((handle->ccr_data.curr - handle->ccr_data.prev) < 2200)
                        ? handle->ccr_data.curr - handle->ccr_data.prev : handle->sig.raw;
    }
}

void rc_sig_norm(struct rc *const handle)
{
    if (handle == NULL)
    {
        return;
    }

    if (handle->sig.raw < 1000)
    {
        handle->sig.norm = 1000.0;
    }
    else if (handle->sig.raw > 2000)
    {
        handle->sig.norm = 2000.0;
    }
    else
    {
        handle->sig.norm = (float32_t)handle->sig.raw;
    }

    switch (ch)
    {
        case RC_CH_1:
            handle->sig.norm = norm_sym_f32(1000.0, 2000.0, handle->sig.norm);
            break;

        case RC_CH_2:
            handle->sig.norm = norm_sym_f32(1000.0, 2000.0, handle->sig.norm);
            break;

        case RC_CH_3:
            handle->sig.norm = norm_asym_f32(1000.0, 2000.0, handle->sig.norm);
            break;

        case RC_CH_4:
            handle->sig.norm = norm_sym_f32(1000.0, 2000.0, handle->sig.norm);
            break;

        case RC_CH_5:
            handle->sig.norm = norm_asym_f32(1000.0, 2000.0, handle->sig.norm);
            break;

        case RC_CH_6:
            handle->sig.norm = norm_asym_f32(1000.0, 2000.0, handle->sig.norm);
            break;
    }
}
