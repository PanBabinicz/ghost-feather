# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Dust protocol
#   - Updater
#
# Description:
#   Collects all source files related to the firmware
#   updater and the Dust protocol implementation for
#   the STM32F722 MCU.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE DUST_SRCS dust/*.c)
file(GLOB_RECURSE UPDATER_SRCS updater/*.c)

# --------------------------------------------------
# Target: Dust protocol
# --------------------------------------------------
message(STATUS "Add dust library")
add_library(dust
    ${DUST_SRCS}
)

target_include_directories(dust PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers/usart
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_libraries(dust PRIVATE
    gfc_common_options
)

target_compile_definitions(dust PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:DEBUG_DUST_PROTOCOL=1>"
)

# --------------------------------------------------
# Target: Updater
# --------------------------------------------------
message(STATUS "Add updater library")
add_library(updater
    ${UPDATER_SRCS}
)

target_include_directories(updater PRIVATE
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/dfu/dust
    ${PROJECT_SOURCE_DIR}/drivers/usart
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/shared/ghost_feather_common
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_libraries(updater PRIVATE
    gfc_common_options
)
