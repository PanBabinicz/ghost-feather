add_executable(
    test1
    test1.cc
    )

target_compile_options(
    test1
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    test1
    PRIVATE
    --coverage
    )

target_link_libraries(
    test1
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(test1)
