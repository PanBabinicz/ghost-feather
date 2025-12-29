# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - USART controller
#   - BMI270 sensor driver
#   - PID controller
#   - SPI controller
#   - TIM controller
#
# Description:
#   Collects all controller-related source files for
#   the STM32F722 MCU. This includes USART, BMI270,
#   PID and SPI subsystems.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE USART_CONTROLLER_SOURCES usart/*.c)
file(GLOB_RECURSE BMI270_SOURCES bmi270/*.c)
file(GLOB_RECURSE PID_CTRL_SOURCES pid/*.c)
file(GLOB_RECURSE RF_CTRL_SOURCES rf/*.c)
file(GLOB_RECURSE SPI_CTRL_SOURCES spi/*.c)
file(GLOB_RECURSE TIM_CTRL_SOURCES tim/*.c)

# --------------------------------------------------
# Target: USART controller
# --------------------------------------------------
message(STATUS "Add usart_controller library")
add_library(usart_controller
    ${USART_CONTROLLER_SOURCES}
)

target_include_directories(usart_controller PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_libraries(usart_controller PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: BMI270 sensor driver
# --------------------------------------------------
message(STATUS "Add bmi270 library")
add_library(bmi270
    ${BMI270_SOURCES}
)

target_include_directories(bmi270 PRIVATE
    ${PROJECT_SOURCE_DIR}/controller/spi
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(bmi270 PRIVATE
    ${PROJECT_SOURCE_DIR}/shared
)

target_link_libraries(bmi270 PRIVATE
    gfc_common_options
    timing
)

# --------------------------------------------------
# Target: PID controller
# --------------------------------------------------
message(STATUS "Add pid_ctrl library")
add_library(pid_ctrl
    ${PID_CTRL_SOURCES}
)

target_include_directories(pid_ctrl PRIVATE
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(pid_ctrl PRIVATE
    ${PROJECT_SOURCE_DIR}/shared
)

target_link_libraries(pid_ctrl PRIVATE
    gfc_common_options
    timing
)

# --------------------------------------------------
# Target: RF controller
# --------------------------------------------------
message(STATUS "Add rf_ctrl library")
add_library(rf_ctrl
    ${RF_CTRL_SOURCES}
)

target_include_directories(rf_ctrl PRIVATE
    ${PROJECT_SOURCE_DIR}/controller/tim
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

#target_link_directories(rf_ctrl PRIVATE
#${PROJECT_SOURCE_DIR}/shared
#)

target_link_libraries(rf_ctrl PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: SPI controller
# --------------------------------------------------
message(STATUS "Add spi_ctrl library")
add_library(spi_ctrl
    ${SPI_CTRL_SOURCES}
)

target_include_directories(spi_ctrl PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(spi_ctrl PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: TIM controller
# --------------------------------------------------
message(STATUS "Add tim_ctrl library")
add_library(tim_ctrl
    ${TIM_CTRL_SOURCES}
)

target_include_directories(tim_ctrl PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(tim_ctrl PRIVATE
    gfc_common_options
)
