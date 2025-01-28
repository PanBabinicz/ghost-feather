add_executable(
    test2
    test2.cc
    )

target_compile_options(
    test2
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    test2
    PRIVATE
    --coverage
    )

target_link_libraries(
    test2
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(test2)
