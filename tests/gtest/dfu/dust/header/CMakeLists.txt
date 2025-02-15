file(GLOB_RECURSE DUST_SOURCES ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust/*.c)

add_executable(
    header
    header.cc
    ${DUST_SOURCES}
    )

target_include_directories(
    header
    PRIVATE
    ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    header
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    header
    PRIVATE
    --coverage
    )

target_link_libraries(
    header
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(header)
