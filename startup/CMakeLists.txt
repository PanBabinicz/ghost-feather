# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Bootloader startup
#   - Apploader startup
#   - Updater startup
#   - Application startup
#
# Description:
#   Collects all startup-related source files for
#   the Ghost Feather firmware targets running on
#   the STM32F722 MCU. These startup modules define
#   the low-level initialization code for each
#   firmware stage: bootloader, apploader, updater,
#   and main application.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE BOOTLOADER_STARTUP_SOURCES stm32f722xx/bootloader/*.c)
file(GLOB_RECURSE APPLOADER_STARTUP_SOURCES stm32f722xx/apploader/*.c)
file(GLOB_RECURSE UPDATER_STARTUP_SOURCES stm32f722xx/updater/*.c)
file(GLOB_RECURSE APP_STARTUP_SOURCES stm32f722xx/app/*.c)

# --------------------------------------------------
# Target: Bootloader startup
# --------------------------------------------------
set_property(
    GLOBAL
    PROPERTY BOOTLOADER_STARTUP_SOURCES
    ${BOOTLOADER_STARTUP_SOURCES}
    )

message(STATUS "Add bootloader_startup library")
add_library(
    bootloader_startup
    ${BOOTLOADER_STARTUP_SOURCES}
    )

target_include_directories(
    bootloader_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/bootloader
    )

target_link_libraries(
    bootloader_startup
    PRIVATE
    gfc_common_options
    )

# --------------------------------------------------
# Target: Apploader startup
# --------------------------------------------------
set_property(
    GLOBAL
    PROPERTY APPLOADER_STARTUP_SOURCES
    ${APPLOADER_STARTUP_SOURCES}
    )

message(STATUS "Add apploader_startup library")
add_library(
    apploader_startup
    ${APPLOADER_STARTUP_SOURCES}
    )

target_include_directories(
    apploader_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/apploader
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

target_link_libraries(
    apploader_startup
    PRIVATE
    gfc_common_options
    )

# --------------------------------------------------
# Target: Updater startup
# --------------------------------------------------
set_property(
    GLOBAL
    PROPERTY UPDATER_STARTUP_SOURCES
    ${UPDATER_STARTUP_SOURCES}
    )

message(STATUS "Add updater_startup library")
add_library(
    updater_startup
    ${UPDATER_STARTUP_SOURCES}
    )

target_include_directories(
    updater_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/updater
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

target_link_libraries(
    updater_startup
    PRIVATE
    gfc_common_options
    )

# --------------------------------------------------
# Target: Application startup
# --------------------------------------------------
set_property(
    GLOBAL
    PROPERTY APP_STARTUP_SOURCES
    ${APP_STARTUP_SOURCES}
    )

message(STATUS "Add app_startup library")
add_library(
    app_startup
    ${APP_STARTUP_SOURCES}
    )

target_include_directories(
    app_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/app/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

target_link_libraries(
    app_startup
    PRIVATE
    gfc_common_options
    )
