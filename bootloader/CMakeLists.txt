file(GLOB_RECURSE FIRST_BOOTLOADER_SOURCES stm32f722xx/first_bootloader/*.c)
file(GLOB_RECURSE SECOND_BOOTLOADER_SOURCES stm32f722xx/second_bootloader/*.c)

set_property(
    GLOBAL
    PROPERTY FIRST_BOOTLOADER_SOURCES
    ${FIRST_BOOTLOADER_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY SECOND_BOOTLOADER_SOURCES
    ${SECOND_BOOTLOADER_SOURCES}
    )

message(STATUS "Add first_bootloader library")
add_library(
    first_bootloader
    ${FIRST_BOOTLOADER_SOURCES}
    )

message(STATUS "Add second_bootloader library")
add_library(
    second_bootloader
    ${SECOND_BOOTLOADER_SOURCES}
    )

message(STATUS "Add first_bootloader target include directories")
target_include_directories(
    first_bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add second_bootloader target include directories")
target_include_directories(
    second_bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add first_bootloader target compile definitions")
target_compile_definitions(
    first_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add second_bootloader target compile definitions")
target_compile_definitions(
    second_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add first_bootloader target compile options")
target_compile_options(
    first_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )

message(STATUS "Add second_bootloader target compile options")
target_compile_options(
    second_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )
