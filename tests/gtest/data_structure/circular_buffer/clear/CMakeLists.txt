file(GLOB_RECURSE CIRCULAR_BUFFER ${PROJECT_ROOT_DIR}/shared/data_structure/*.c)

add_executable(
    clear
    clear.cc
    ${CIRCULAR_BUFFER}
    )

target_include_directories(
    clear
    PRIVATE
    ${PROJECT_ROOT_DIR}/shared
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    clear
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    clear
    PRIVATE
    --coverage
    )

target_link_libraries(
    clear
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(clear)
