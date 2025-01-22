#ifndef _BOOT_UPDATER_H
#define _BOOT_UPDATER_H

#include <stdint.h>

///
/// \brief The boot updater results type.
///
typedef enum
{
    BOOT_UPDATER_RESULT_SUCCESS = 0,
    BOOT_UPDATER_RESULT_ERROR,
} boot_updater_result_t;

///
/// \brief Starts the boot updater.
///
void boot_updater_start(void);

#endif /* _BOOT_UPDATER_H */
