file(GLOB_RECURSE USART_PRINTF_SOURCES printf/*.c)

set_property(
    GLOBAL
    PROPERTY USART_PRINTF_SOURCES
    ${USART_PRINTF_SOURCES}
    )

message(STATUS "Add usart_printf library")
add_library(
    usart_printf
    ${USART_PRINTF_SOURCES}
    )

message(STATUS "Add usart_printf target include directories")
target_include_directories(
    usart_printf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/libopencm3/include
    )

message(STATUS "Add usart_printf target compile definitions")
target_compile_definitions(
    usart_printf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add usart_printf target compile options")
target_compile_options(
    usart_printf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )
