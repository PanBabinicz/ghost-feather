# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Printf
#
# Description:
#   Collects printf related source files for
#   the Ghost Feather firmware targets running on
#   the STM32F722 MCU.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE PRINTF_SRCS printf/*.c)

# --------------------------------------------------
# Target: Printf
# --------------------------------------------------
message(STATUS "Add printf library")
add_library(printf
    ${PRINTF_SRCS}
)

target_compile_definitions(printf PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:PRINTF_DISABLE_SUPPORT_LONG_LONG>"
)

target_include_directories(printf PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_libraries(printf PRIVATE
    gfc_common_options
)
