# Set the system name to avoid macOS-specific settings
set(CMAKE_SYSTEM_NAME Generic)

# Specify the C and ASM compilers for ARM
set(CMAKE_C_COMPILER /opt/homebrew/bin/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER /opt/homebrew/bin/arm-none-eabi-as)
set(CMAKE_LINKER /opt/homebrew/bin/arm-none-eabi-ld)

# Prevent CMake from adding macOS-specific flags
set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_ASM_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS "")

# Suppress certain platform-specific checks and flags
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
