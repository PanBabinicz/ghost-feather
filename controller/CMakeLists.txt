file(GLOB_RECURSE USART_CONTROLLER_SOURCES usart/*.c)
file(GLOB_RECURSE BMI270_SOURCES bmi270/*.c)
file(GLOB_RECURSE SPI_CTRL_SOURCES spi/*.c)

set_property(
    GLOBAL
    PROPERTY USART_CONTROLLER_SOURCES
    ${USART_CONTROLLER_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY BMI270_SOURCES
    ${BMI270_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY SPI_CTRL_SOURCES
    ${SPI_CTRL_SOURCES}
    )

message(STATUS "Add usart_controller library")
add_library(
    usart_controller
    ${USART_CONTROLLER_SOURCES}
    )

message(STATUS "Add bmi270 library")
add_library(
    bmi270
    ${BMI270_SOURCES}
    )

message(STATUS "Add spi_ctrl library")
add_library(
    spi_ctrl
    ${SPI_CTRL_SOURCES}
    )

message(STATUS "Add usart_controller target include directories")
target_include_directories(
    usart_controller
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
    )

message(STATUS "Add bmi270 target include directories")
target_include_directories(
    bmi270
    PRIVATE
    ${PROJECT_SOURCE_DIR}/controller/spi
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add spi_ctrl target include directories")
target_include_directories(
    spi_ctrl
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add usart_controller target compile definitions")
target_compile_definitions(
    usart_controller
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add bmi270 target compile definitions")
target_compile_definitions(
    bmi270
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add spi_ctrl target compile definitions")
target_compile_definitions(
    spi_ctrl
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
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add bmi270 target compile options")
target_compile_options(
    bmi270
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add spi_ctrl target compile options")
target_compile_options(
    spi_ctrl
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )
