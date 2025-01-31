file(GLOB_RECURSE DUST_SOURCES ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust/*.c)

add_executable(
    crc16-lut-generation
    crc16-lut-generation.cc
    ${DUST_SOURCES}
    )

target_include_directories(
    crc16-lut-generation
    PRIVATE
    ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    crc16-lut-generation
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    crc16-lut-generation
    PRIVATE
    --coverage
    )

target_link_libraries(
    crc16-lut-generation
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(crc16-lut-generation)
