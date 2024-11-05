cmake_minimum_required(VERSION 3.30.2)

project(
    ghost-feather
    VERSION 1.0.0
    LANGUAGES C ASM
    )

# Set the system name to generic to avoid macOS-specific flags
set(CMAKE_SYSTEM_NAME Generic)

# Clear any macOS or default flags that may introduce `-arch`
set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_ASM_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS "")

set(tools /opt/homebrew)
set(CMAKE_C_COMPILER ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER ${tools}/bin/arm-none-eabi-as)
set(CMAKE_LINKER ${tools}/bin/arm-none-eabi-ld)

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

target_link_libraries(
    ghost_feather_first_bootloader
    PUBLIC
    stm32f722xx_startup
    first_bootloader
    vectortable
    )

target_compile_definitions(
    ghost_feather_first_bootloader
    PRIVATE
    "$<$<COMPILE_LANGUAGE:C>:STM32F7>"
    )
