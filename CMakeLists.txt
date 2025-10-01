cmake_minimum_required(VERSION 3.30.2)

project(
    ghost-feather
    VERSION 1.0.0
    LANGUAGES C ASM
    )

add_subdirectory(loader)
add_subdirectory(dfu)
add_subdirectory(app)
add_subdirectory(startup)
add_subdirectory(vectortable)
add_subdirectory(controller)
add_subdirectory(submodules)

get_cmake_property(bootloader_sources BOOTLOADER_SOURCES)
get_cmake_property(apploader_sources APPLOADER_SOURCES)
get_cmake_property(updater_sources UPDATER_SOURCES)
get_cmake_property(dust_sources DUST_SOURCES)
get_cmake_property(app_sources APP_SOURCES)
get_cmake_property(bootloader_startup_sources BOOTLOADER_STARTUP_SOURCES)
get_cmake_property(apploader_startup_sources APPLOADER_STARTUP_SOURCES)
get_cmake_property(updater_startup_sources UPDATER_STARTUP_SOURCES)
get_cmake_property(app_startup_sources APP_STARTUP_SOURCES)
get_cmake_property(vectortable_sources VECTORTABLE_SOURCES)
get_cmake_property(usart_controller_sources USART_CONTROLLER_SOURCES)
get_cmake_property(bmi270_sources BMI270_SOURCES)
get_cmake_property(spi_ctrl_sources SPI_CTRL_SOURCES)
get_cmake_property(printf_sources PRINTF_SOURCES)

message(STATUS "Add ghost-feather-bootloader executable")
add_executable(
    ghost-feather-bootloader.elf
    ${bootloader_sources}
    ${bootloader_startup_sources}
    ${vectortable_sources}
    )

message(STATUS "Add ghost-feather-apploader executable")
add_executable(
    ghost-feather-apploader.elf
    ${apploader_sources}
    ${apploader_startup_sources}
    ${vectortable_sources}
    )

message(STATUS "Add ghost-feather-updater executable")
add_executable(
    ghost-feather-updater.elf
    ${updater_sources}
    ${dust_sources}
    ${updater_startup_sources}
    ${vectortable_sources}
    ${usart_controller_sources}
    ${printf_sources}
    )

message(STATUS "Add ghost-feather-app executable")
add_executable(
    ghost-feather-app.elf
    ${app_sources}
    ${app_startup_sources}
    ${bmi270_sources}
    ${spi_ctrl_sources}
    ${vectortable_sources}
    )

message(STATUS "Add ghost-feather-bootloader target link directories")
target_link_directories(
    ghost-feather-bootloader.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-apploader target link directories")
target_link_directories(
    ghost-feather-apploader.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-updater target link directories")
target_link_directories(
    ghost-feather-updater.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/controller
    ${PROJECT_SOURCE_DIR}/submodules
    ${PROJECT_SOURCE_DIR}/dfu
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-app target link directories")
target_link_directories(
    ghost-feather-app.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    /usr/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-bootloader target link libraries")
target_link_libraries(
    ghost-feather-bootloader.elf
    PRIVATE
    bootloader_startup
    bootloader
    vectortable
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-apploader target link libraries")
target_link_libraries(
    ghost-feather-apploader.elf
    PRIVATE
    apploader_startup
    apploader
    vectortable
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-updater target link libraries")
target_link_libraries(
    ghost-feather-updater.elf
    PRIVATE
    updater_startup
    updater
    dust
    vectortable
    usart_controller
    printf
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-app target link libraries")
target_link_libraries(
    ghost-feather-app.elf
    PRIVATE
    app_startup
    app
    vectortable
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-bootloader target include directories")
target_include_directories(
    ghost-feather-bootloader.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/bootloader
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add ghost-feather-apploader target include directories")
target_include_directories(
    ghost-feather-apploader.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/loader/stm32f722xx/apploader
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/shared
    )

message(STATUS "Add ghost-feather-updater target include directories")
target_include_directories(
    ghost-feather-updater.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/updater
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_SOURCE_DIR}/controller/usart
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
    )

message(STATUS "Add ghost-feather-app target include directories")
target_include_directories(
    ghost-feather-app.elf
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/app/stm32f722xx
    ${PROJECT_SOURCE_DIR}/controller/bmi270
    ${PROJECT_SOURCE_DIR}/controller/spi
    ${PROJECT_SOURCE_DIR}/shared
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )


message(STATUS "Add ghost-feather-bootloader target compile definitions")
target_compile_definitions(
    ghost-feather-bootloader.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add ghost-feather-apploader target compile definitions")
target_compile_definitions(
    ghost-feather-apploader.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add ghost-feather-updater target compile definitions")
target_compile_definitions(
    ghost-feather-updater.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    "$<$<COMPILE_LANGUAGE:C>:PRINTF_DISABLE_SUPPORT_LONG_LONG>"
    "$<$<COMPILE_LANGUAGE:C>:DEBUG_DUST_PROTOCOL=1>"
    "$<$<COMPILE_LANGUAGE:C>:DEBUG=1>"
    )

message(STATUS "Add ghost-feather-app target compile definitions")
target_compile_definitions(
    ghost-feather-app.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add ghost-feather-bootloader target compile options")
target_compile_options(
    ghost-feather-bootloader.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add ghost-feather-apploader target compile options")
target_compile_options(
    ghost-feather-apploader.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add ghost-feather-updater target compile options")
target_compile_options(
    ghost-feather-updater.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-Wcast-align>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add ghost-feather-app target compile options")
target_compile_options(
    ghost-feather-app.elf
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O3>"
    )

message(STATUS "Add ghost-feather-bootloader target compile options")
target_link_options(
    ghost-feather-bootloader.elf
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/bootloader.ld
    -nostartfiles
    -specs=nano.specs
    )

message(STATUS "Add ghost-feather-apploader target compile options")
target_link_options(
    ghost-feather-apploader.elf
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/apploader.ld
    -nostartfiles
    -specs=nano.specs
    )

message(STATUS "Add ghost-feather-updater target compile options")
target_link_options(
    ghost-feather-updater.elf
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/updater.ld
    -nostartfiles
    -specs=nano.specs
    )

message(STATUS "Add ghost-feather-app target compile options")
target_link_options(
    ghost-feather-app.elf
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/app.ld
    -nostartfiles
    -specs=nano.specs
    )
