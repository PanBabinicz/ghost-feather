file(GLOB_RECURSE STARTUP_SOURCES stm32f722xx/*.c)

set_property(
    GLOBAL
    PROPERTY STARTUP_SOURCES
    ${STARTUP_SOURCES}
    )

add_library(
    stm32f722xx_startup
    ${STARTUP_SOURCES}
    )

target_include_directories(
    stm32f722xx_startup
    PUBLIC
    ${PROJECT_SOURCE_DIR}/memory
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx
    )
