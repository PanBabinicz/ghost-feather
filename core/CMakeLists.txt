# --------------------------------------------------
# SPDX-License-Identifier: MIT
# --------------------------------------------------
# Project: Ghost Feather Firmware (STM32F7)
# Modules:
#   - Ghost Feather Main Firmawre
#   - Ghost Feather Common
#
# Description:
#   Collects all source files related to the ghost
#   feather firmware and files related to it.
# --------------------------------------------------
# Files list genereation
# --------------------------------------------------
file(GLOB_RECURSE GHF_SOURCES ghf/*.c)
file(GLOB_RECURSE GHFC_SOURCES ghfc/*.c)

# --------------------------------------------------
# Target: Ghost Feather Main Firmware
# --------------------------------------------------
message(STATUS "Add ghost feather main firmware library")
add_library(ghf
    ${GHF_SOURCES}
)

target_include_directories(ghf PRIVATE
    ${PROJECT_SOURCE_DIR}/controller/rf
    ${PROJECT_SOURCE_DIR}/controller/tim
)

target_link_libraries(ghf PRIVATE
    gfc_common_options
)

# --------------------------------------------------
# Target: Ghost Feather Common
# --------------------------------------------------
#message(STATUS "Add ghost feather common library")
#add_library(ghfc
#    ${GHFC_SOURCES}
#)

#target_include_directories(ghfc PRIVATE
#    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
#)

#target_link_libraries(ghfc PRIVATE
#    gfc_common_options
#)
