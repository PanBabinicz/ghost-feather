file(GLOB_RECURSE STM32F722XX_FIRST_BOOTLOADER_STARTUP_SOURCES stm32f722xx/first_bootloader/*.c)
file(GLOB_RECURSE STM32F722XX_SECOND_BOOTLOADER_STARTUP_SOURCES stm32f722xx/second_bootloader/*.c)
file(GLOB_RECURSE STM32F722XX_APP_STARTUP_SOURCES stm32f722xx/app/*.c)

set_property(
    GLOBAL
    PROPERTY STM32F722XX_FIRST_BOOTLOADER_STARTUP_SOURCES
    ${STM32F722XX_FIRST_BOOTLOADER_STARTUP_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY STM32F722XX_SECOND_BOOTLOADER_STARTUP_SOURCES
    ${STM32F722XX_SECOND_BOOTLOADER_STARTUP_SOURCES}
    )

set_property(
    GLOBAL
    PROPERTY STM32F722XX_APP_STARTUP_SOURCES
    ${STM32F722XX_APP_STARTUP_SOURCES}
    )

message(STATUS "Add stm32f722xx_first_bootloader_startup library")
add_library(
    stm32f722xx_first_bootloader_startup
    ${STM32F722XX_FIRST_BOOTLOADER_STARTUP_SOURCES}
    )

message(STATUS "Add stm32f722xx_second_bootloader_startup library")
add_library(
    stm32f722xx_second_bootloader_startup
    ${STM32F722XX_SECOND_BOOTLOADER_STARTUP_SOURCES}
    )

message(STATUS "Add stm32f722xx_app_startup library")
add_library(
    stm32f722xx_app_startup
    ${STM32F722XX_APP_STARTUP_SOURCES}
    )

message(STATUS "Add stm32f722xx_first_bootloader_startup target include directories")
target_include_directories(
    stm32f722xx_first_bootloader_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx/first_bootloader
    )

message(STATUS "Add stm32f722xx_second_bootloader_startup target include directories")
target_include_directories(
    stm32f722xx_second_bootloader_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx/second_bootloader
    )

message(STATUS "Add stm32f722xx_app_startup target include directories")
target_include_directories(
    stm32f722xx_app_startup
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/app/stm32f722xx
    )
