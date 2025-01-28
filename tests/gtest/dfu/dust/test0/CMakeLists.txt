add_executable(
    test0
    test0.cc
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
