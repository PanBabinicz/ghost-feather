# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Bootloader
#   - Apploader
#
# Description:
#   Collects all source files related to the bootloader
#   and apploader for the STM32F722 MCU.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE BOOTLOADER_SRCS bootloader/*.c)
file(GLOB_RECURSE APPLOADER_SRCS apploader/*.c)

# --------------------------------------------------
# Target: Bootloader
# --------------------------------------------------
message(STATUS "Add bootloader library")
add_library(bootloader
    ${BOOTLOADER_SRCS}
)

target_include_directories(bootloader PRIVATE
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(bootloader PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: Apploader
# --------------------------------------------------
message(STATUS "Add apploader library")
add_library(apploader
    ${APPLOADER_SRCS}
)

target_include_directories(apploader PRIVATE
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/shared/ghost_feather_common
)

target_link_libraries(apploader PRIVATE
    gfc_common_options
)
