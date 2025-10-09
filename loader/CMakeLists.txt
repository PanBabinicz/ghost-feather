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
file(GLOB_RECURSE BOOTLOADER_SOURCES stm32f722xx/bootloader/*.c)
file(GLOB_RECURSE APPLOADER_SOURCES stm32f722xx/apploader/*.c)

# --------------------------------------------------
# Target: Bootloader
# --------------------------------------------------
set_property(
    GLOBAL
    PROPERTY BOOTLOADER_SOURCES
    ${BOOTLOADER_SOURCES}
    )

message(STATUS "Add bootloader library")
add_library(
    bootloader
    ${BOOTLOADER_SOURCES}
    )

target_include_directories(
    bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

target_link_libraries(
    bootloader
    PRIVATE
    gfc_common_options
    )

# --------------------------------------------------
# Target: Bootloader
# --------------------------------------------------
set_property(
    GLOBAL
    PROPERTY APPLOADER_SOURCES
    ${APPLOADER_SOURCES}
    )

message(STATUS "Add apploader library")
add_library(
    apploader
    ${APPLOADER_SOURCES}
    )

target_include_directories(
    apploader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/shared
    )

target_link_libraries(
    apploader
    PRIVATE
    gfc_common_options
    )
