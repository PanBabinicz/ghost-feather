file(GLOB_RECURSE BOOTLOADER_SOURCES stm32f722xx/bootloader/*.c)
file(GLOB_RECURSE APPLOADER_SOURCES stm32f722xx/apploader/*.c)

set_property(
    GLOBAL
    PROPERTY BOOTLOADER_SOURCES
    ${BOOTLOADER_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY APPLOADER_SOURCES
    ${APPLOADER_SOURCES}
    )

message(STATUS "Add bootloader library")
add_library(
    bootloader
    ${BOOTLOADER_SOURCES}
    )

message(STATUS "Add apploader library")
add_library(
    apploader
    ${APPLOADER_SOURCES}
    )

message(STATUS "Add bootloader target include directories")
target_include_directories(
    bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add apploader target include directories")
target_include_directories(
    apploader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/shared
    )

message(STATUS "Add bootloader target compile definitions")
target_compile_definitions(
    bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add apploader target compile definitions")
target_compile_definitions(
    apploader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add bootloader target compile options")
target_compile_options(
    bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add apploader target compile options")
target_compile_options(
    apploader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )
