file(GLOB_RECURSE CIRCULAR_BUFFER ${PROJECT_ROOT_DIR}/shared/data_structure/*.c)

add_executable(
    pop
    pop.cc
    ${CIRCULAR_BUFFER}
    )

target_include_directories(
    pop
    PRIVATE
    ${PROJECT_ROOT_DIR}/shared
    )

target_compile_options(
    pop
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    pop
    PRIVATE
    --coverage
    )

target_link_libraries(
    pop
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(pop)
