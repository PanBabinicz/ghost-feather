file(GLOB_RECURSE USART_CONTROLLER_SOURCES usart/*.c)

set_property(
    GLOBAL
    PROPERTY USART_CONTROLLER_SOURCES
    ${USART_CONTROLLER_SOURCES}
    )

message(STATUS "Add usart_controller library")
add_library(
    usart_controller
    ${USART_CONTROLLER_SOURCES}
    )

message(STATUS "Add usart_controller target include directories")
target_include_directories(
    usart_controller
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
    )

message(STATUS "Add usart_controller target compile definitions")
target_compile_definitions(
    usart_controller
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add usart_controller target compile options")
target_compile_options(
    usart_controller
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )
