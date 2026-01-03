# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - BMI270 sensor module
#   - PID module
#   - RC module
#   - TIM module
#
# Description:
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE BMI270_SRCS sensor/bmi270/*.c)
#file(GLOB_RECURSE PID_SRCS pid/*.c)
file(GLOB_RECURSE RC_SRCS rc/*.c)
file(GLOB_RECURSE TIM_SRCS tim/*.c)

# --------------------------------------------------
# Target: BMI270 sensor module
# --------------------------------------------------
message(STATUS "Add bmi270 sensor module library")
add_library(bmi270
    ${BMI270_SRCS}
)

target_include_directories(bmi270 PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers/sensor/bmi270
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
# Target: PID module
# --------------------------------------------------
#message(STATUS "Add pid module library")
#add_library(pid
#    ${PID_SRCS}
#)
#
#target_include_directories(pid PRIVATE
#    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
#)
#
#target_link_libraries(pid PRIVATE
#    gfc_common_options
#)

# --------------------------------------------------
# Target: RC module
# --------------------------------------------------
message(STATUS "Add rc module library")
add_library(rc
    ${RC_SRCS}
)

target_include_directories(rc PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers/tim
    ${PROJECT_SOURCE_DIR}/modules/tim
)

target_link_directories(rc PRIVATE
    ${PROJECT_SOURCE_DIR}/modules
)

target_link_libraries(rc PRIVATE
    gfc_common_options
    tim
)

# --------------------------------------------------
# Target: TIM module
# --------------------------------------------------
message(STATUS "Add tim module library")
add_library(tim
    ${TIM_SRCS}
)

target_include_directories(tim PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers/tim
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
)

target_link_libraries(tim PRIVATE
    gfc_common_options
    ll_tim
)
