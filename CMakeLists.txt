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
# CPU / FPU configuration flags
# --------------------------------------------------
set(CPU_FLAGS
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
        ${CPU_FLAGS}
        ${OPT_FLAGS}
    >
    $<$<COMPILE_LANGUAGE:ASM>:
        ${CPU_FLAGS}
    >
)

# --------------------------------------------------
# Subdirectories
# --------------------------------------------------
# Each subdirectory defines and registers sources
# via set_property(GLOBAL PROPERTY <NAME>_SOURCES ...)
# --------------------------------------------------
add_subdirectory(app)
add_subdirectory(controller)
add_subdirectory(dfu)
add_subdirectory(loader)
add_subdirectory(shared)
add_subdirectory(submodules)
add_subdirectory(startup)
add_subdirectory(vectortable)

# --------------------------------------------------
# Target: Bootloader
# --------------------------------------------------
message(STATUS "Configuring ghost-feather-bootloader.elf")
add_executable(ghost-feather-bootloader.elf
    misc/empty.c
)

target_include_directories(ghost-feather-bootloader.elf PUBLIC
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/bootloader
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(ghost-feather-bootloader.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/bootloader
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
)

target_link_libraries(ghost-feather-bootloader.elf PRIVATE
    bootloader_startup
    bootloader
    gfc_common_options
    libopencm3_stm32f7.a
    timing
    vectortable
)

target_link_options(ghost-feather-bootloader.elf PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/bootloader.ld
    -nostartfiles
    -specs=nano.specs
)

# --------------------------------------------------
# Target: Apploader
# --------------------------------------------------
message(STATUS "Configuring ghost-feather-apploader.elf")
add_executable(ghost-feather-apploader.elf
    misc/empty.c
)

target_include_directories(ghost-feather-apploader.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/apploader
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(ghost-feather-apploader.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
)

target_link_libraries(ghost-feather-apploader.elf PRIVATE
    apploader_startup
    apploader
    gfc_common_options
    libopencm3_stm32f7.a
    vectortable
)

target_link_options(ghost-feather-apploader.elf PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/apploader.ld
    -nostartfiles
    -specs=nano.specs
)

# --------------------------------------------------
# Target: Updater
# --------------------------------------------------
message(STATUS "Configuring ghost-feather-updater.elf")
add_executable(ghost-feather-updater.elf
    misc/empty.c
)

target_include_directories(ghost-feather-updater.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/controller/usart
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/updater
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_directories(ghost-feather-updater.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/controller
    ${PROJECT_SOURCE_DIR}/dfu
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
)

target_link_libraries(ghost-feather-updater.elf PRIVATE
    updater_startup
    updater
    usart_controller
    dust
    printf
    gfc_common_options
    libopencm3_stm32f7.a
    vectortable
)

target_link_options(ghost-feather-updater.elf PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/updater.ld
    -nostartfiles
    -specs=nano.specs
)

# --------------------------------------------------
# Target: Main application
# --------------------------------------------------
message(STATUS "Configuring ghost-feather-app.elf")
add_executable(ghost-feather-app.elf
    misc/empty.c
)

target_include_directories(ghost-feather-app.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/app/stm32f722xx
    ${PROJECT_SOURCE_DIR}/controller/bmi270
    ${PROJECT_SOURCE_DIR}/controller/spi
    ${PROJECT_SOURCE_DIR}/controller/tim
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(ghost-feather-app.elf PRIVATE
    ${PROJECT_SOURCE_DIR}/controller
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
)

target_link_libraries(ghost-feather-app.elf PRIVATE
    app_startup
    app
    bmi270
    gfc_common_options
    libopencm3_stm32f7.a
    tim_ctrl
    timing
    vectortable
)

target_link_options(ghost-feather-app.elf PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/app.ld
    -nostartfiles
    -specs=nano.specs
)

# --------------------------------------------------
# Summary
# --------------------------------------------------
message(STATUS "Ghost Feather firmware build configured successfully.")
