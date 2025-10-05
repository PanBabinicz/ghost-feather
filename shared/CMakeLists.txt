file(GLOB GHOST_FEATHER_COMMON_SOURCES ghost_feather_common.c)
file(GLOB_RECURSE TIMING_SOURCES timing/*.c)

set_property(
    GLOBAL
    PROPERTY GHOST_FEATHER_COMMON_SOURCES
    ${GHOST_FEATHER_COMMON_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY TIMING_SOURCES
    ${TIMING_SOURCES}
    )

message(STATUS "Add ghost_feather_common library")
add_library(
    ghost_feather_common
    ${GHOST_FEATHER_COMMON_SOURCES}
    )

message(STATUS "Add timing library")
add_library(
    timing
    ${TIMING_SOURCES}
    )

message(STATUS "Add ghost_feather_common target include directories")
target_include_directories(
    ghost_feather_common
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add timing target include directories")
target_include_directories(
    timing
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add ghost_feather_common target compile definitions")
target_compile_definitions(
    ghost_feather_common
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add timing target compile definitions")
target_compile_definitions(
    timing
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add ghost_feather_common target compile options")
target_compile_options(
    ghost_feather_common
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add timing target compile options")
target_compile_options(
    timing
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )
