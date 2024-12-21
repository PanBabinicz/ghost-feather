cmake_minimum_required(VERSION 3.30.2)

project(
    ghost-feather
    VERSION 1.0.0
    LANGUAGES C ASM
    )

add_subdirectory(bootloader)
add_subdirectory(dfu)
add_subdirectory(app)
add_subdirectory(startup)
add_subdirectory(vectortable)
add_subdirectory(controller)
add_subdirectory(submodules)
#add_subdirectory(lib)

get_cmake_property(first_bootloader_sources FIRST_BOOTLOADER_SOURCES)
get_cmake_property(second_bootloader_sources SECOND_BOOTLOADER_SOURCES)
get_cmake_property(boot_updater BOOT_UPDATER_SOURCES)
get_cmake_property(dust DUST_SOURCES)
get_cmake_property(app_sources APP_SOURCES)
get_cmake_property(stm32f722xx_first_bootloader_startup_sources STM32F722XX_FIRST_BOOTLOADER_STARTUP_SOURCES)
get_cmake_property(stm32f722xx_second_bootloader_startup_sources STM32F722XX_SECOND_BOOTLOADER_STARTUP_SOURCES)
get_cmake_property(stm32f722xx_boot_updater_startup_sources STM32F722XX_BOOT_UPDATER_STARTUP_SOURCES)
get_cmake_property(stm32f722xx_app_startup_sources STM32F722XX_APP_STARTUP_SOURCES)
get_cmake_property(vectortable_sources VECTORTABLE_SOURCES)
get_cmake_property(usart_controller_sources USART_CONTROLLER_SOURCES)
get_cmake_property(printf_sources PRINTF_SOURCES)
#get_cmake_property(stm32f722xx_syscall_sources STM32F722XX_SYSCALL_SOURCES)

message(STATUS "Add ghost-feather-first-bootloader executable")
add_executable(
    ghost-feather-first-bootloader
    ${first_bootloader_sources}
    ${stm32f722xx_first_bootloader_startup_sources}
    ${vectortable_sources}
    )

message(STATUS "Add ghost-feather-second-bootloader executable")
add_executable(
    ghost-feather-second-bootloader
    ${second_bootloader_sources}
    ${stm32f722xx_second_bootloader_startup_sources}
    ${vectortable_sources}
    )

message(STATUS "Add ghost-feather-boot-updater executable")
add_executable(
    ghost-feather-boot-updater
    ${boot_updater}
    ${dust}
    ${stm32f722xx_boot_updater_startup_sources}
    ${vectortable_sources}
    ${usart_controller_sources}
    ${printf_sources}
    )

message(STATUS "Add ghost-feather-app executable")
add_executable(
    ghost-feather-app
    ${app_sources}
    ${stm32f722xx_app_startup_sources}
    ${vectortable_sources}
    )

message(STATUS "Add ghost-feather-first-bootloader target link directories")
target_link_directories(
    ghost-feather-first-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    /Applications/ArmGNUToolchain/13.3.rel1/arm-none-eabi/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-second-bootloader target link directories")
target_link_directories(
    ghost-feather-second-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    /Applications/ArmGNUToolchain/13.3.rel1/arm-none-eabi/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-boot-updater target link directories")
target_link_directories(
    ghost-feather-boot-updater
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/controller
    ${PROJECT_SOURCE_DIR}/submodules
    ${PROJECT_SOURCE_DIR}/dfu
    /Applications/ArmGNUToolchain/13.3.rel1/arm-none-eabi/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-app target link directories")
target_link_directories(
    ghost-feather-app
    PRIVATE
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    /Applications/ArmGNUToolchain/13.3.rel1/arm-none-eabi/arm-none-eabi/lib/thumb/v7+fp/hard
    )

message(STATUS "Add ghost-feather-first-bootloader target link libraries")
target_link_libraries(
    ghost-feather-first-bootloader
    PRIVATE
    stm32f722xx_first_bootloader_startup
    first_bootloader
    vectortable
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-second-bootloader target link libraries")
target_link_libraries(
    ghost-feather-second-bootloader
    PRIVATE
    stm32f722xx_second_bootloader_startup
    second_bootloader
    vectortable
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-boot-updater target link libraries")
target_link_libraries(
    ghost-feather-boot-updater
    PRIVATE
    stm32f722xx_boot_updater_startup
    boot_updater
    dust
    vectortable
    usart_controller
    printf
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-app target link libraries")
target_link_libraries(
    ghost-feather-app
    PRIVATE
    stm32f722xx_app_startup
    app
    vectortable
    libopencm3_stm32f7.a
    )

message(STATUS "Add ghost-feather-first-bootloader target include directories")
target_include_directories(
    ghost-feather-first-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx/first_bootloader
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add ghost-feather-second-bootloader target include directories")
target_include_directories(
    ghost-feather-second-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx/second_bootloader
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )

message(STATUS "Add ghost-feather-boot-updater target include directories")
target_include_directories(
    ghost-feather-boot-updater
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/boot_updater
    ${PROJECT_SOURCE_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_SOURCE_DIR}/controller/usart
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    ${PROJECT_SOURCE_DIR}/submodules/printf
    )

message(STATUS "Add ghost-feather-app target include directories")
target_include_directories(
    ghost-feather-app
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/app/stm32f722xx
    ${PROJECT_SOURCE_DIR}/submodules/libopencm3/include
    )


message(STATUS "Add ghost-feather-first-bootloader target compile definitions")
target_compile_definitions(
    ghost-feather-first-bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add ghost-feather-second-bootloader target compile definitions")
target_compile_definitions(
    ghost-feather-second-bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add ghost-feather-boot-updater target compile definitions")
target_compile_definitions(
    ghost-feather-boot-updater
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    "$<$<COMPILE_LANGUAGE:C>:PRINTF_DISABLE_SUPPORT_LONG_LONG>"
    "$<$<COMPILE_LANGUAGE:C>:DEBUG_DUST_PROTOCOL=1>"
    )

message(STATUS "Add ghost-feather-app target compile definitions")
target_compile_definitions(
    ghost-feather-app
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

message(STATUS "Add ghost-feather-first-bootloader target compile options")
target_compile_options(
    ghost-feather-first-bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )

message(STATUS "Add ghost-feather-second-bootloader target compile options")
target_compile_options(
    ghost-feather-second-bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )

message(STATUS "Add ghost-feather-boot-updater target compile options")
target_compile_options(
    ghost-feather-boot-updater
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )

message(STATUS "Add ghost-feather-app target compile options")
target_compile_options(
    ghost-feather-app
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )

message(STATUS "Add ghost-feather-first-bootloader target compile options")
target_link_options(
    ghost-feather-first-bootloader
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/stm32f722xx_first_bootloader.ld
    -nostartfiles
    -specs=nano.specs
    )

message(STATUS "Add ghost-feather-second-bootloader target compile options")
target_link_options(
    ghost-feather-second-bootloader
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/stm32f722xx_second_bootloader.ld
    -nostartfiles
    -specs=nano.specs
    )

message(STATUS "Add ghost-feather-boot-updater target compile options")
target_link_options(
    ghost-feather-boot-updater
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/stm32f722xx_boot_updater.ld
    -nostartfiles
    -specs=nano.specs
    )

message(STATUS "Add ghost-feather-app target compile options")
target_link_options(
    ghost-feather-app
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/stm32f722xx_app.ld
    -nostartfiles
    -specs=nano.specs
    )
