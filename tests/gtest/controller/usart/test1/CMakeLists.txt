add_executable(
    usart-test1
    test1.cc
    )

target_compile_options(
    usart-test1
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    usart-test1
    PRIVATE
    --coverage
    )

target_link_libraries(
    usart-test1
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(usart-test1)
