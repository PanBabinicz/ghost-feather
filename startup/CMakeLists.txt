file(GLOB_RECURSE BOOTLOADER_STARTUP_SOURCES stm32f722xx/bootloader/*.c)
file(GLOB_RECURSE APPLOADER_STARTUP_SOURCES stm32f722xx/apploader/*.c)
file(GLOB_RECURSE UPDATER_STARTUP_SOURCES stm32f722xx/updater/*.c)
file(GLOB_RECURSE APP_STARTUP_SOURCES stm32f722xx/app/*.c)

set_property(
    GLOBAL
    PROPERTY BOOTLOADER_STARTUP_SOURCES
    ${BOOTLOADER_STARTUP_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY APPLOADER_STARTUP_SOURCES
    ${APPLOADER_STARTUP_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY UPDATER_STARTUP_SOURCES
    ${UPDATER_STARTUP_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY APP_STARTUP_SOURCES
    ${APP_STARTUP_SOURCES}
    )

message(STATUS "Add bootloader_startup library")
add_library(
    bootloader_startup
    ${BOOTLOADER_STARTUP_SOURCES}
    )

message(STATUS "Add apploader_startup library")
add_library(
    apploader_startup
    ${APPLOADER_STARTUP_SOURCES}
    )

message(STATUS "Add updater_startup library")
add_library(
    updater_startup
    ${UPDATER_STARTUP_SOURCES}
    )

message(STATUS "Add app_startup library")
add_library(
    app_startup
    ${APP_STARTUP_SOURCES}
    )

message(STATUS "Add bootloader_startup target include directories")
target_include_directories(
    bootloader_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/bootloader
    )

message(STATUS "Add apploader_startup target include directories")
target_include_directories(
    apploader_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/apploader
    )

message(STATUS "Add updater_startup target include directories")
target_include_directories(
    updater_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/updater
    )

message(STATUS "Add app_startup target include directories")
target_include_directories(
    app_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/app/stm32f722xx
    )
