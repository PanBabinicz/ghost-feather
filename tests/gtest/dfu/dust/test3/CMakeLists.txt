add_executable(
    test3
    test3.cc
    )

target_compile_options(
    test3
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    test3
    PRIVATE
    --coverage
    )

target_link_libraries(
    test3
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(test3)
