file(GLOB_RECURSE BOOT_UPDATER_SOURCES stm32f722xx/*.c)

set_property(
    GLOBAL
    PROPERTY BOOT_UPDATER_SOURCES
    ${BOOT_UPDATER_SOURCES}
    )

message(STATUS "Add boot_updater library")
add_library(
    boot_updater
    ${BOOT_UPDATER_SOURCES}
    )

message(STATUS "Add boot_updater target include directories")
target_include_directories(
    boot_updater
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/libopencm3/include
    ${PROJECT_SOURCE_DIR}/shared/printf
    )

message(STATUS "Add boot_updater target compile definitions")
target_compile_definitions(
    boot_updater
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add boot_updater target compile options")
target_compile_options(
    boot_updater
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )
