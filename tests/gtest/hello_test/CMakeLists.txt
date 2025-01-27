add_executable(
    hello_test
    hello_test.cc
    )

target_compile_options(
    hello_test
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    hello_test
    PRIVATE
    --coverage
    )

target_link_libraries(
    hello_test
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(hello_test)
