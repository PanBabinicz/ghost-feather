file(GLOB_RECURSE USART_CONTROLLER ${PROJECT_ROOT_DIR}/controller/usart/*.c)

add_executable(
    init
    init.cc
    ${USART_CONTROLLER}
    )

target_include_directories(
    init
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/usart
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    init
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    init
    PRIVATE
    --coverage
    )

target_link_libraries(
    init
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(init)
