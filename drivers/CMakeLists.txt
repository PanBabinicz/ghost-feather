# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - BMI270 sensor low level driver
#   - SPI low level driver
#   - TIM low level driver
#   - USART low level driver
#
# Description:
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE LL_BMI270_SRCS sensor/bmi270/*.c)
file(GLOB_RECURSE LL_SPI_SRCS spi/*.c)
file(GLOB_RECURSE LL_TIM_SRCS tim/*.c)
file(GLOB_RECURSE LL_USART_SRCS usart/*.c)

# --------------------------------------------------
# Target: BMI270 low-lever driver
# --------------------------------------------------
message(STATUS "Add bmi270 sensor low-level driver library")
add_library(ll_bmi270
    ${LL_BMI270_SRCS}
)

target_include_directories(ll_bmi270 PRIVATE
    ${PROJECT_SOURCE_DIR}/shared/timing
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_directories(ll_bmi270 PRIVATE
    ${PROJECT_SOURCE_DIR}/shared
)

target_link_libraries(ll_bmi270 PRIVATE
    gfc_common_options
    timing
)

# --------------------------------------------------
# Target: SPI low-lever driver
# --------------------------------------------------
message(STATUS "Add spi low-level driver library")
add_library(ll_spi
    ${LL_SPI_SRCS}
)

target_include_directories(ll_spi PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(ll_spi PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: TIM low-lever driver
# --------------------------------------------------
message(STATUS "Add tim low-level driver library")
add_library(ll_tim
    ${LL_TIM_SRCS}
)

target_include_directories(ll_tim PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(ll_tim PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: USART controller
# --------------------------------------------------
message(STATUS "Add usart low-level driver library")
add_library(ll_usart
    ${LL_USART_SRCS}
)

target_include_directories(ll_usart PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
)

target_link_libraries(ll_usart PRIVATE
    gfc_common_options
)
