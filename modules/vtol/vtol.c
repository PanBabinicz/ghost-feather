#include "vtol.h"
#include "rc.h"

///***********************************************************************************************************
/// Private objects - declaration.
///***********************************************************************************************************
///
/// \brief
///
struct vtol_step
{
    vtol_take_off_step_t take_off;
    vtol_land_step_t land;
};

///
/// \brief
///
struct vtol_phase
{
    struct vtol_step step;
    vtol_stat_t stat;
};

///***********************************************************************************************************
/// Private objects - definition.
///***********************************************************************************************************
///
/// \brief
///
static struct vtol_phase ghf_vtol_phase;

///***********************************************************************************************************
/// Global functions - definition.
///***********************************************************************************************************
void vtol_take_off_proc(void)
{
    struct vtol_phase *phase = &ghf_vtol_phase;
    struct rc_dev* rc_dev_arr = rc_dev_arr_get();

    struct rc_sig *roll;
    struct rc_sig *pitch;
    struct rc_sig *throttle;

    rc_sig_raw_gen(RC_CH_1);
    rc_sig_raw_gen(RC_CH_2);
    rc_sig_raw_gen(RC_CH_3);

    roll     = &rc_dev_arr[RC_CH_1].sig;
    pitch    = &rc_dev_arr[RC_CH_2].sig;
    throttle = &rc_dev_arr[RC_CH_3].sig;
    
    if (phase->stat == VTOL_STAT_OFF)
    {
        switch (phase->step.take_off)
        {
            case VTOL_TAKE_OFF_STEP_0:
                if ((pitch->raw > 900) && (pitch->raw < 1200) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.take_off = VTOL_TAKE_OFF_STEP_1;
                }
                break;

            case VTOL_TAKE_OFF_STEP_1:
                if ((roll->raw > 900) && (roll->raw < 1200) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.take_off = VTOL_TAKE_OFF_STEP_2;
                }
                break;

            case VTOL_TAKE_OFF_STEP_2:
                if ((roll->raw > 1450) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.take_off = VTOL_TAKE_OFF_STEP_3;
                }
                break;

            case VTOL_TAKE_OFF_STEP_3:
                if ((pitch->raw > 1450) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.take_off = VTOL_TAKE_OFF_STEP_0;
                    phase->stat = VTOL_STAT_ON;
                }
                break;

            default:
                break;
        }
    }
}

void vtol_land_proc(void)
{
    struct vtol_phase *phase = &ghf_vtol_phase;
    struct rc_dev* rc_dev_arr = rc_dev_arr_get();

    struct rc_sig *roll;
    struct rc_sig *pitch;
    struct rc_sig *throttle;

    rc_sig_raw_gen(RC_CH_1);
    rc_sig_raw_gen(RC_CH_2);
    rc_sig_raw_gen(RC_CH_3);

    roll     = &rc_dev_arr[RC_CH_1].sig;
    pitch    = &rc_dev_arr[RC_CH_2].sig;
    throttle = &rc_dev_arr[RC_CH_3].sig;
    
    if (phase->stat == VTOL_STAT_ON)
    {
        switch (phase->step.land)
        {
            case VTOL_LAND_STEP_0:
                if ((pitch->raw > 900) && (pitch->raw < 1200) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.land = VTOL_LAND_STEP_1;
                }
                break;

            case VTOL_LAND_STEP_1:
                if ((roll->raw > 900) && (roll->raw < 1200) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.land = VTOL_LAND_STEP_2;
                }
                break;

            case VTOL_LAND_STEP_2:
                if ((roll->raw > 1450) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.land = VTOL_LAND_STEP_3;
                }
                break;

            case VTOL_LAND_STEP_3:
                if ((pitch->raw > 1450) && (throttle->raw > 900) && (throttle->raw < 1200))
                {
                    phase->step.land = VTOL_LAND_STEP_0;
                    phase->stat = VTOL_STAT_OFF;
                }
                break;

            default:
                break;
        }
    }
}

vtol_stat_t vtol_stat_get(void)
{
    struct vtol_phase *phase = &ghf_vtol_phase;
    return phase->stat;
}
