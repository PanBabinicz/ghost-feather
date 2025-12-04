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
file(GLOB_RECURSE APP_SOURCES stm32f722xx/*.c)

# --------------------------------------------------
# Target: Application
# --------------------------------------------------
message(STATUS "Add app library")
add_library(app
    ${APP_SOURCES}
)

target_include_directories(app PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/controller/bmi270
    ${PROJECT_SOURCE_DIR}/controller/spi
    ${PROJECT_SOURCE_DIR}/controller/tim
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(app PRIVATE
    gfc_common_options
)
