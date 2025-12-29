# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Updater
#   - Dust protocol
#
# Description:
#   Collects all source files related to the firmware
#   updater and the Dust protocol implementation for
#   the STM32F722 MCU.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE UPDATER_SOURCES stm32f722xx/updater/*.c)
file(GLOB_RECURSE DUST_SOURCES stm32f722xx/dust/*.c)

# --------------------------------------------------
# Target: Updater
# --------------------------------------------------
message(STATUS "Add updater library")
add_library(updater
    ${UPDATER_SOURCES}
)

target_include_directories(updater PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/controller/usart
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/shared/ghost_feather_common
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_libraries(updater PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: Dust protocol
# --------------------------------------------------
message(STATUS "Add dust library")
add_library(dust
    ${DUST_SOURCES}
)

target_include_directories(dust PRIVATE
    ${PROJECT_SOURCE_DIR}/controller/usart
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_libraries(dust PRIVATE
    gfc_common_options
)

target_compile_definitions(dust PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:DEBUG_DUST_PROTOCOL=1>"
)

