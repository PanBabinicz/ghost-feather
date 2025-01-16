file(GLOB_RECURSE APP_SOURCES stm32f722xx/*.c)

set_property(
    GLOBAL
    PROPERTY APP_SOURCES
    ${APP_SOURCES}
    )

message(STATUS "Add app library")
add_library(
    app
    ${APP_SOURCES}
    )

message(STATUS "Add app target include directories")
target_include_directories(
    app
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add app target compile definitions")
target_compile_definitions(
    app
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add app target compile options")
target_compile_options(
    app
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )
