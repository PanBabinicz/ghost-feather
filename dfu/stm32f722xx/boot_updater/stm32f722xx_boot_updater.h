#ifndef _BOOT_UPDATER_H
#define _BOOT_UPDATER_H

#include <stdint.h>

///
/// \brief
///
typedef enum
{
    BOOT_UPDATER_RESULT_SUCCESS = 0,
    BOOT_UPDATER_RESULT_ERROR,
} boot_updater_result_t;

///
/// \brief
///
boot_updater_result_t boot_updater_init(void);

/*
///
/// \brief
///
boot_updater_result_t boot_updater_deinit(void);
*/

///
/// \brief
///
void boot_updater_start(void);

#endif /* _BOOT_UPDATER_H */