file(GLOB_RECURSE DUST_SOURCES ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust/*.c)

add_executable(
    test0
    test0.cc
    ${DUST_SOURCES}
    )

message(STATUS "PROJECT ROOT DIR is ${PROJECT_ROOT_DIR}")
target_include_directories(
    test0
    PRIVATE
    ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    test0
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    test0
    PRIVATE
    --coverage
    )

target_link_libraries(
    test0
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(test0)
