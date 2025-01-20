file(GLOB_RECURSE PRINTF_SOURCES printf/*.c)

set_property(
    GLOBAL
    PROPERTY PRINTF_SOURCES
    ${PRINTF_SOURCES}
    )

message(STATUS "Add printf library")
add_library(
    printf
    ${PRINTF_SOURCES}
    )

message(STATUS "Add printf target include directories")
target_include_directories(
    printf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
    )

message(STATUS "Add printf target compile definitions")
target_compile_definitions(
    printf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add printf target compile options")
target_compile_options(
    printf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )
