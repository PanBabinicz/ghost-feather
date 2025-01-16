file(GLOB_RECURSE BOOT_UPDATER_SOURCES stm32f722xx/boot_updater/*.c)
file(GLOB_RECURSE DUST_SOURCES stm32f722xx/dust/*.c)

set_property(
    GLOBAL
    PROPERTY BOOT_UPDATER_SOURCES
    ${BOOT_UPDATER_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY DUST_SOURCES
    ${DUST_SOURCES}
    )

message(STATUS "Add boot_updater library")
add_library(
    boot_updater
    ${BOOT_UPDATER_SOURCES}
    )

message(STATUS "Add dust library")
add_library(
    dust
    ${DUST_SOURCES}
    )

message(STATUS "Add boot_updater target include directories")
target_include_directories(
    boot_updater
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/controller/usart
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
    )

message(STATUS "Add dust target include directories")
target_include_directories(
    dust
    PRIVATE
    ${PROJECT_SOURCE_DIR}/controller/usart
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
    )

message(STATUS "Add boot_updater target compile definitions")
target_compile_definitions(
    boot_updater
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add dust target compile definitions")
target_compile_definitions(
    dust
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    "$<$<COMPILE_LANGUAGE:C>:DEBUG_DUST_PROTOCOL=1>"
    )

message(STATUS "Add boot_updater target compile options")
target_compile_options(
    boot_updater
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-Wcast-align>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add dust target compile options")
target_compile_options(
    dust
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-Wcast-align>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )
