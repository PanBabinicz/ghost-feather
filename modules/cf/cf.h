#ifndef _CF_H
#define _CF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

///
/// \brief The complementary filter result type.
///
typedef enum cf_res
{
    CF_STAT_OK = 0,
    CF_STAT_ERR,
} cf_res_t;

///
/// \brief The complementary filter status type.
///
typedef enum cf_inst
{
    CF_INST_BEGIN = 0,
    CF_INST_ROLL  = 0,
    CF_INST_PITCH,
    CF_INST_TOTAL,
} cf_inst_t;

///
/// \brief
///
cf_res_t cf_init(const cf_inst_t inst);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _CF_H */
