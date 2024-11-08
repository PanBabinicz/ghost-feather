file(GLOB_RECURSE FIRST_BOOTLOADER_SOURCES stm32f722xx/*.c)

set_property(
    GLOBAL
    PROPERTY FIRST_BOOTLOADER_SOURCES
    ${FIRST_BOOTLOADER_SOURCES}
    )

message(
    STATUS
    "Add first_bootloader library"
    )

add_library(
    first_bootloader
    ${FIRST_BOOTLOADER_SOURCES}
    )

target_include_directories(
    first_bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/libopencm3/include
    )

target_compile_definitions(
    first_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )
