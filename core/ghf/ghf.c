#include "ghf.h"
#include <string.h>

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief
///
struct ghf_dev ghf;

///***********************************************************************************************************
/// Private functions - declaration.
///***********************************************************************************************************
///
/// \brief
///
static void ghf_cap_upd(struct ghf_dev *const ghf, rf_ctrl_ch_t rf_ch, struct tim_ctrl_ccr_data *const ccr_data);

///
/// \brief
///
static void ghf_cap_to_sig(struct ghf_dev *const ghf, struct tim_ctrl_ccr_data *const ccr_data, uint32_t *const sig);

///
/// \brief
///
static void ghf_launch_proc_is_step_0(struct ghf_dev *const ghf);

///
/// \brief
///
static void ghf_launch_proc_is_step_1();

///
/// \brief
///
static void ghf_launch_proc_is_step_2();

///
/// \brief
///
static void ghf_launch_proc_is_step_3();

///***********************************************************************************************************
/// Private functions - definition.
///***********************************************************************************************************
static void ghf_cap_upd(struct ghf_dev *const ghf, rf_ctrl_ch_t rf_ch, struct tim_ctrl_ccr_data *const ccr_data)
{
    (void)rf_ctrl_ccr_data_get(ghf->sys.rf[rf_ch], ccr_data);
}

static void ghf_cap_to_sig(struct ghf_dev *const ghf, struct tim_ctrl_ccr_data *const ccr_data, uint32_t *const sig)
{
    if (ccr_data->curr > ccr_data->prev)
    {
        *sig = ((ccr_data->curr - ccr_data->prev) < 2200) ? (ccr_data->curr - ccr_data->prev) : *sig;
    }
}

/*
static void ghf_launch_proc_is_step_0(struct ghf_dev *const ghf)
{

}
*/

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
ghf_res_t ghf_dev_init(struct ghf_dev *const ghf)
{
    if (ghf == NULL)
    {
        return GHF_RES_ERR;
    }

    struct rf_ctrl_dev *rf_ctrl_dev_arr = rf_ctrl_dev_arr_get();

    ghf->sys.rf[RF_CTRL_CH_0] = &rf_ctrl_dev_arr[RF_CTRL_CH_0];
    ghf->sys.rf[RF_CTRL_CH_1] = &rf_ctrl_dev_arr[RF_CTRL_CH_1];
    ghf->sys.rf[RF_CTRL_CH_2] = &rf_ctrl_dev_arr[RF_CTRL_CH_2];
    ghf->sys.rf[RF_CTRL_CH_3] = &rf_ctrl_dev_arr[RF_CTRL_CH_3];
    ghf->sys.rf[RF_CTRL_CH_4] = &rf_ctrl_dev_arr[RF_CTRL_CH_4];
    ghf->sys.rf[RF_CTRL_CH_5] = &rf_ctrl_dev_arr[RF_CTRL_CH_5];

    return GHF_RES_OK;
}

ghf_res_t ghf_launch_proc(struct ghf_dev *const ghf)
{
    if (ghf == NULL)
    {
        return GHF_RES_ERR;
    }

    if (ghf->op.stat == GHF_STAT_OFF)
    {
        switch (ghf->op.launch_step)
        {
            case GHF_LAUNCH_STEP_1:
                ghf_cap_upd(ghf, RF_CTRL_CH_1, &ghf->ctrl.pitch.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.pitch.ccr_data, &ghf->ctrl.pitch.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);

                if (ghf->ctrl.pitch.sig_raw > 900 && ghf->ctrl.pitch.sig_raw < 1100 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.launch_step = GHF_LAUNCH_STEP_2;
                }

                break;

            case GHF_LAUNCH_STEP_2:
                ghf_cap_upd(ghf, RF_CTRL_CH_0, &ghf->ctrl.roll.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.roll.ccr_data, &ghf->ctrl.roll.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);
                
                if (ghf->ctrl.roll.sig_raw > 900 && ghf->ctrl.roll.sig_raw < 1100 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.launch_step = GHF_LAUNCH_STEP_3;
                }

                break;

            case GHF_LAUNCH_STEP_3:
                ghf_cap_upd(ghf, RF_CTRL_CH_0, &ghf->ctrl.roll.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.roll.ccr_data, &ghf->ctrl.roll.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);

                if (ghf->ctrl.roll.sig_raw > 1450 && ghf->ctrl.roll.sig_raw < 1550 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.launch_step = GHF_LAUNCH_STEP_4;
                }

                break;

            case GHF_LAUNCH_STEP_4:
                ghf_cap_upd(ghf, RF_CTRL_CH_1, &ghf->ctrl.pitch.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.pitch.ccr_data, &ghf->ctrl.pitch.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);

                if (ghf->ctrl.pitch.sig_raw > 1450 && ghf->ctrl.pitch.sig_raw < 1550 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.launch_step = GHF_LAUNCH_STEP_1;
                    ghf->op.stat = GHF_STAT_ON;
                }

                break;

            default:
                break;
        }
    }

    return GHF_RES_OK;
}

ghf_res_t ghf_land_proc(struct ghf_dev *const ghf)
{
    if (ghf == NULL)
    {
        return GHF_RES_ERR;
    }

    if (ghf->op.stat == GHF_STAT_ON)
    {
        switch (ghf->op.land_step)
        {
            case GHF_LAND_STEP_1:
                ghf_cap_upd(ghf, RF_CTRL_CH_1, &ghf->ctrl.pitch.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.pitch.ccr_data, &ghf->ctrl.pitch.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);

                if (ghf->ctrl.pitch.sig_raw > 900 && ghf->ctrl.pitch.sig_raw < 1100 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.land_step = GHF_LAND_STEP_2;
                }

                break;

            case GHF_LAND_STEP_2:
                ghf_cap_upd(ghf, RF_CTRL_CH_0, &ghf->ctrl.roll.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.roll.ccr_data, &ghf->ctrl.roll.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);

                if (ghf->ctrl.roll.sig_raw > 900 && ghf->ctrl.roll.sig_raw < 1100 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.land_step = GHF_LAND_STEP_3;
                }

                break;

            case GHF_LAND_STEP_3:
                ghf_cap_upd(ghf, RF_CTRL_CH_0, &ghf->ctrl.roll.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.roll.ccr_data, &ghf->ctrl.roll.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);

                if (ghf->ctrl.roll.sig_raw > 1450 && ghf->ctrl.roll.sig_raw < 1550 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.land_step = GHF_LAND_STEP_4;
                }

                break;

            case GHF_LAND_STEP_4:
                ghf_cap_upd(ghf, RF_CTRL_CH_1, &ghf->ctrl.pitch.ccr_data);
                ghf_cap_upd(ghf, RF_CTRL_CH_2, &ghf->ctrl.throttle.ccr_data);
                ghf_cap_to_sig(ghf, &ghf->ctrl.pitch.ccr_data, &ghf->ctrl.pitch.sig_raw);
                ghf_cap_to_sig(ghf, &ghf->ctrl.throttle.ccr_data, &ghf->ctrl.throttle.sig_raw);

                if (ghf->ctrl.pitch.sig_raw > 1450 && ghf->ctrl.pitch.sig_raw < 1550 &&
                    ghf->ctrl.throttle.sig_raw > 900 && ghf->ctrl.throttle.sig_raw < 1100)
                {
                    ghf->op.land_step = GHF_LAUNCH_STEP_1;
                    ghf->op.stat = GHF_STAT_OFF;
                }

                break;

            default:
                break;
        }
    }

    return GHF_RES_OK;
}
