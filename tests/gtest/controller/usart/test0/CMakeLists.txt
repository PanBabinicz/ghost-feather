add_executable(
    usart-test0
    test0.cc
    )

target_compile_options(
    usart-test0
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    usart-test0
    PRIVATE
    --coverage
    )

target_link_libraries(
    usart-test0
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(usart-test0)
