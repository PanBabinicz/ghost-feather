file(GLOB_RECURSE FIRST_BOOTLOADER_SOURCES stm32f722xx/*.c)

set_property(
    GLOBAL
    PROPERTY FIRST_BOOTLOADER_SOURCES
    ${FIRST_BOOTLOADER_SOURCES}
    )

add_library(
    first_bootloader
    ${FIRST_BOOTLOADER_SOURCES}
    )

target_include_directories(
    first_bootloader
    PUBLIC
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/libopencm3/include
    )

target_compile_definitions(
    first_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )
