file(GLOB_RECURSE DUST_SOURCES ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust/*.c)

add_executable(
    deserialization
    deserialization.cc
    ${DUST_SOURCES}
    )

target_include_directories(
    deserialization
    PRIVATE
    ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    deserialization
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    deserialization
    PRIVATE
    --coverage
    )

target_link_libraries(
    deserialization
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(deserialization)
