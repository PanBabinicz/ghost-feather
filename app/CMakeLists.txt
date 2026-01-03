# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Application
#
# Description:
#   Defines the main application build configuration
#   for the STM32F722 MCU. Collects all application
#   sources, sets include paths, and links against
#   shared libraries and the common interface target
#   (`gfc_common_options`).
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE APP_SRCS *.c)

# --------------------------------------------------
# Target: Application
# --------------------------------------------------
message(STATUS "Add app library")
add_library(app
    ${APP_SRCS}
)

target_include_directories(app PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers/tim
    ${PROJECT_SOURCE_DIR}/modules/rc
    ${PROJECT_SOURCE_DIR}/modules/tim
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(app PRIVATE
    gfc_common_options
)
