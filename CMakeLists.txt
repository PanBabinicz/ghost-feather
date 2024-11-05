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
    ghost_feather_first_bootloader
    ${first_bootloader_sources}
    ${startup_sources}
    ${vectortable_sources}
    )

target_link_directories(
    ghost_feather_first_bootloader
    PUBLIC
    ${PROJECT_SOURCE_DIR}/libopencm3/lib
    ${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx
    )

target_link_libraries(
    ghost_feather_first_bootloader
    PUBLIC
    stm32f722xx_startup
    first_bootloader
    vectortable
    libopencm3_stm32f7.a
    )

target_compile_definitions(
    ghost_feather_first_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )

target_compile_options(
    ghost_feather_first_bootloader
    PUBLIC
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -mcpu=cortex-m7
    -mthumb
    )

target_link_options(
    ghost_feather_first_bootloader
    PUBLIC
    -T${PROJECT_SOURCE_DIR}/linkerscript/stm32f722xx/stm32f722xx_bootloader.ld
    -nostartfiles
    -nostdlib
    )
