cmake_minimum_required(VERSION 3.30.2)

project(
    ghost-feather
    VERSION 1.0.0
    LANGUAGES C ASM
    )

add_subdirectory(startup)
add_subdirectory(vectortable)
add_subdirectory(bootloader)

get_cmake_property(first_bootloader_sources FIRST_BOOTLOADER_SOURCES)
get_cmake_property(second_bootloader_sources SECOND_BOOTLOADER_SOURCES)
get_cmake_property(stm32f722xx_first_bootloader_startup_sources STM32F722XX_FIRST_BOOTLOADER_STARTUP_SOURCES)
get_cmake_property(stm32f722xx_second_bootloader_startup_sources STM32F722XX_SECOND_BOOTLOADER_STARTUP_SOURCES)
get_cmake_property(vectortable_sources VECTORTABLE_SOURCES)

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

message(STATUS "Add ghost-feather-first-bootloader target link directories")
target_link_directories(
    ghost-feather-first-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    )

message(STATUS "Add ghost-feather-second-bootloader target link directories")
target_link_directories(
    ghost-feather-second-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
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

message(STATUS "Add ghost-feather-first-bootloader target include directories")
target_include_directories(
    ghost-feather-first-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/libopencm3/include
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx/first_bootloader
    )

message(STATUS "Add ghost-feather-second-bootloader target include directories")
target_include_directories(
    ghost-feather-second-bootloader
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/libopencm3/include
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx/second_bootloader
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

message(STATUS "Add ghost-feather-first-bootloader target compile options")
target_compile_options(
    ghost-feather-first-bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )

message(STATUS "Add ghost-feather-second-bootloader target compile options")
target_compile_options(
    ghost-feather-second-bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
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
    -nostdlib
    )

message(STATUS "Add ghost-feather-second-bootloader target compile options")
target_link_options(
    ghost-feather-second-bootloader
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/stm32f722xx_second_bootloader.ld
    -nostartfiles
    -nostdlib
    )
