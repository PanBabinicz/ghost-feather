#ifndef _TIM_CTRL_H
#define _TIM_CTRL_H

#include <stdint.h>
#include "tim_ctrl_common.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief Enumeration of available TIM controller instances.
///
/// This enum lists all supported TIM peripherals that can be accessed through
/// the TIM control layer. The values start at zero and increase sequentially.
/// `TIM_CTRL_INST_TOTAL` represents the count of valid instances.
///
typedef enum tim_ctrl_inst
{
    TIM_CTRL_INST_BEGIN = 0,
    TIM_CTRL_INST_TIM4  = 0,
    TIM_CTRL_INST_TIM12,
    TIM_CTRL_INST_TIM8,
    TIM_CTRL_INST_TOTAL,
} tim_ctrl_inst_t;

///
/// \brief The TIM device interface.
///
/// This structure provides a generic interface to a TIM peripheral.
/// The `tim` pointer references the underlying hardware instance, and the
/// function pointers implement lifecycle and state-control operations.
/// Each function returns a `tim_ctrl_res_t` indicating success or error.
///
struct tim_ctrl_dev
{
    void *tim;
    tim_ctrl_res_t (*init)(void *tim);
    tim_ctrl_res_t (*deinit)(void *tim);
    tim_ctrl_res_t (*enable)(void *tim);
    tim_ctrl_res_t (*disable)(void *tim);
    tim_ctrl_res_t (*ccr_data_get)(void *tim, const tim_ctrl_inst_ccr_t ccr_inst, struct tim_ctrl_ccr_data *ccr_data);
    tim_ctrl_res_t (*ccr_set)(void *tim, const tim_ctrl_inst_ccr_t ccr_inst, const uint32_t ccr);
};

///
/// \brief Gets the TIM device.
///
/// \param[in] inst The selected TIM instance.
///
/// \return struct tim_ctrl_dev* The TIM device pointer.
///
struct tim_ctrl_dev* tim_ctrl_dev_get(tim_ctrl_inst_t inst);

///
/// \brief Gets the TIM device array.
///
/// \return struct tim_ctrl_dev* The begin of the TIM control device array.
///
struct tim_ctrl_dev* tim_ctrl_dev_arr_get(void);

///
/// \brief Initializes the TIM devices.
///
/// This function should be called during system initialization.
///
void tim_ctrl_init(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _TIM_CTRL_H */
