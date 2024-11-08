file(GLOB_RECURSE STARTUP_SOURCES stm32f722xx/*.c)

set_property(
    GLOBAL
    PROPERTY STARTUP_SOURCES
    ${STARTUP_SOURCES}
    )

message(
    STATUS
    "Add stm32f722xx_startup library"
    )

add_library(
    stm32f722xx_startup
    ${STARTUP_SOURCES}
    )

target_include_directories(
    stm32f722xx_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx
    )
