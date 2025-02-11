file(GLOB_RECURSE CIRCULAR_BUFFER ${PROJECT_ROOT_DIR}/shared/data_structure/*.c)

add_executable(
    push
    push.cc
    ${CIRCULAR_BUFFER}
    )

target_include_directories(
    push
    PRIVATE
    ${PROJECT_ROOT_DIR}/shared
    )

target_compile_options(
    push
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    push
    PRIVATE
    --coverage
    )

target_link_libraries(
    push
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(push)
