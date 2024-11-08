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
get_cmake_property(startup_sources STARTUP_SOURCES)
get_cmake_property(vectortable_sources VECTORTABLE_SOURCES)

add_executable(
    ghost-feather
    ${first_bootloader_sources}
    ${startup_sources}
    ${vectortable_sources}
    )

target_link_directories(
    ghost-feather
    PRIVATE
    ${PROJECT_SOURCE_DIR}/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    )

target_link_libraries(
    ghost-feather
    PRIVATE
    stm32f722xx_startup
    first_bootloader
    vectortable
    libopencm3_stm32f7.a
    )

target_include_directories(
    ghost-feather
    PRIVATE
    ${PROJECT_SOURCE_DIR}/memory/stm32f722xx
    ${PROJECT_SOURCE_DIR}/libopencm3/include
    ${PROJECT_SOURCE_DIR}/bootloader/stm32f722xx
    )

target_compile_definitions(
    ghost-feather
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

target_compile_options(
    ghost-feather
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>"
    "$<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>"
    "$<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m7>"
    "$<$<COMPILE_LANGUAGE:C>:-mthumb>"
    "$<$<COMPILE_LANGUAGE:C>:-O1>"
    )

target_link_options(
    ghost-feather
    PRIVATE
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/stm32f722xx_bootloader.ld
    -nostartfiles
    -nostdlib
    )
