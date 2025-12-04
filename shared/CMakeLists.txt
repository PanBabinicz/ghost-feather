# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Timing
#
# Description:
#   Collects all source files related to the timing
#   mechanism for the STM32F722 MCU.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE TIMING_SOURCES timing/*.c)

# --------------------------------------------------
# Target: Timing
# --------------------------------------------------
message(STATUS "Add timing library")
add_library(timing
    ${TIMING_SOURCES}
)

target_include_directories(timing PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(timing PRIVATE
    gfc_common_options
)
