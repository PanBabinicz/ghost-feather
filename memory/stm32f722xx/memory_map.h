#ifndef _MEMORY_MAP_H
#define _MEMORY_MAP_H

#include <stdint.h>

extern uint32_t __bootloader_start__;
extern uint32_t __bootloader_size__;
extern uint32_t __apploader_start__;
extern uint32_t __apploader_size__;
extern uint32_t __updater_start__;
extern uint32_t __updater_size__;
extern uint32_t __app_start__;
extern uint32_t __app_size__;

#endif /* _MEMORY_MAP_H */
