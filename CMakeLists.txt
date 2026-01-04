# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Description: Top-level CMake configuration.
# Handles multiple build targets: bootloader,
# apploader, updater, and main application.
# --------------------------------------------------

cmake_minimum_required(VERSION 3.30.2)

# --------------------------------------------------
# Project metadata
# --------------------------------------------------
project(ghost-feather
    VERSION 1.0.0
    LANGUAGES C ASM
)

# --------------------------------------------------
# Project settings
# --------------------------------------------------
set(BOOTLOADER_ELF ${PROJECT_NAME}-bootloader.elf)
set(APPLOADER_ELF  ${PROJECT_NAME}-apploader.elf)
set(UPDATER_ELF    ${PROJECT_NAME}-updater.elf)
set(APP_ELF        ${PROJECT_NAME}-app.elf)

# --------------------------------------------------
# CPU / FPU configuration flags
# --------------------------------------------------
set(COMPILER_OPTIONS
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
    -mcpu=cortex-m7
    -mthumb
)

set(LINKER_OPTIONS
    -nostartfiles
    -specs=nano.specs
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
    -mcpu=cortex-m7
    -mthumb
)

# --------------------------------------------------
# Build-type configuration
# --------------------------------------------------
# Use `-DCMAKE_BUILD_TYPE=Debug` or `Release` on configure.
# CMake will handle optimization automatically.
# --------------------------------------------------
set(OPT_FLAGS_DEBUG          -O0 -g3)
set(OPT_FLAGS_RELEASE        -O3 -DNDEBUG)
set(OPT_FLAGS_RELWITHDEBINFO -O2 -g3 -DNDEBUG)
set(OPT_FLAGS_MINSIZEREL     -Os -DNDEBUG)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPT_FLAGS ${OPT_FLAGS_DEBUG})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OPT_FLAGS ${OPT_FLAGS_RELEASE})
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(OPT_FLAGS ${OPT_FLAGS_RELWITHDEBINFO})
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(OPT_FLAGS ${OPT_FLAGS_MINSIZEREL})
else()
    message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler flags: ${OPT_FLAGS}")


# --------------------------------------------------
# Define a reusable INTERFACE library for shared options
# --------------------------------------------------

add_library(gfc_common_options INTERFACE)

target_compile_definitions(gfc_common_options INTERFACE
    $<$<COMPILE_LANGUAGE:C>:
        STM32F7
    >
)

target_compile_options(gfc_common_options INTERFACE
    $<$<COMPILE_LANGUAGE:C>:
        ${COMPILER_OPTIONS}
        ${OPT_FLAGS}
    >
    $<$<COMPILE_LANGUAGE:ASM>:
        ${COMPILER_OPTIONS}
    >
)

target_link_options(gfc_common_options INTERFACE
    ${LINKER_OPTIONS}
)

# --------------------------------------------------
# Subdirectories
# --------------------------------------------------
# Each subdirectory defines and registers sources
# via set_property(GLOBAL PROPERTY <NAME>_SOURCES ...)
# --------------------------------------------------
add_subdirectory(app)
add_subdirectory(drivers)
add_subdirectory(dfu)
add_subdirectory(loader)
add_subdirectory(modules)
add_subdirectory(shared)
add_subdirectory(submodules)
add_subdirectory(startup)

# --------------------------------------------------
# Target: Bootloader
# --------------------------------------------------
message(STATUS "Configuring ${BOOTLOADER_ELF}")
add_executable(${BOOTLOADER_ELF}
    ${PROJECT_SOURCE_DIR}/misc/empty.c
    ${PROJECT_SOURCE_DIR}/vectortable/vectortable.S
)

target_include_directories(${BOOTLOADER_ELF} PUBLIC
    ${PROJECT_SOURCE_DIR}/loader/bootloader
    ${PROJECT_SOURCE_DIR}/memory/
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(${BOOTLOADER_ELF} PRIVATE
    ${PROJECT_SOURCE_DIR}/loader/bootloader
    ${PROJECT_SOURCE_DIR}/linkerscript
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
)

target_link_libraries(${BOOTLOADER_ELF} PRIVATE
    gfc_common_options
    bootloader_startup
    bootloader
    libopencm3_stm32f7.a
    timing
)

target_link_options(${BOOTLOADER_ELF} PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/bootloader.ld
)

# --------------------------------------------------
# Target: Apploader
# --------------------------------------------------
message(STATUS "Configuring ${APPLOADER_ELF}")
add_executable(${APPLOADER_ELF}
    ${PROJECT_SOURCE_DIR}/misc/empty.c
    ${PROJECT_SOURCE_DIR}/vectortable/vectortable.S
)

target_include_directories(${APPLOADER_ELF} PRIVATE
    ${PROJECT_SOURCE_DIR}/loader/apploader
    ${PROJECT_SOURCE_DIR}/memory/
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(${APPLOADER_ELF} PRIVATE
    ${PROJECT_SOURCE_DIR}/linkerscript
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
)

target_link_libraries(${APPLOADER_ELF} PRIVATE
    gfc_common_options
    apploader_startup
    apploader
    libopencm3_stm32f7.a
)

target_link_options(${APPLOADER_ELF} PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/apploader.ld
)

# --------------------------------------------------
# Target: Updater
# --------------------------------------------------
message(STATUS "Configuring ${UPDATER_ELF}")
add_executable(${UPDATER_ELF}
    ${PROJECT_SOURCE_DIR}/misc/empty.c
    ${PROJECT_SOURCE_DIR}/vectortable/vectortable.S
)

target_include_directories(${UPDATER_ELF} PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers/usart
    ${PROJECT_SOURCE_DIR}/dfu/updater
    ${PROJECT_SOURCE_DIR}/dfu/dust
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_directories(${UPDATER_ELF} PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers
    ${PROJECT_SOURCE_DIR}/dfu
    ${PROJECT_SOURCE_DIR}/linkerscript
    ${PROJECT_SOURCE_DIR}/submodules
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
)

target_link_libraries(${UPDATER_ELF} PRIVATE
    gfc_common_options
    updater_startup
    updater
    dust
    printf
    ll_usart
    libopencm3_stm32f7.a
)

target_link_options(${UPDATER_ELF} PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/updater.ld
)

# --------------------------------------------------
# Target: Main application
# --------------------------------------------------
message(STATUS "Configuring ${APP_ELF}")
add_executable(${APP_ELF}
    ${PROJECT_SOURCE_DIR}/misc/empty.c
    ${PROJECT_SOURCE_DIR}/vectortable/vectortable.S
)

target_include_directories(${APP_ELF} PRIVATE
    ${PROJECT_SOURCE_DIR}/app
    ${PROJECT_SOURCE_DIR}/drivers/spi
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/modules/motor
    ${PROJECT_SOURCE_DIR}/modules/rc
    ${PROJECT_SOURCE_DIR}/modules/tim
    ${PROJECT_SOURCE_DIR}/modules/vtol
    ${PROJECT_SOURCE_DIR}/modules/sensor/bmi270
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(${APP_ELF} PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers
    ${PROJECT_SOURCE_DIR}/modules
    ${PROJECT_SOURCE_DIR}/linkerscript
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
)

target_link_libraries(${APP_ELF} PRIVATE
    gfc_common_options
    app_startup
    app
    bmi270
    libopencm3_stm32f7.a
    vtol
    motor
    rc
    tim
    ll_tim
    timing
)

target_link_options(${APP_ELF} PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/app.ld
)

# --------------------------------------------------
# Summary
# --------------------------------------------------
message(STATUS "Ghost Feather firmware build configured successfully.")
