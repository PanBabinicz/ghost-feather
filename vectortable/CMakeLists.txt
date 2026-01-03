# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Vectortable
#
# Description:
#   Collects printf related source files for
#   the Ghost Feather firmware targets running on
#   the STM32F722 MCU.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE VECTORTABLE_SRCS *.S)

# --------------------------------------------------
# Target: Vectortable
# --------------------------------------------------
message(STATUS "Add vectortable library")
add_library(vectortable
    ${VECTORTABLE_SRCS}
)
