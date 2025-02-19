file(GLOB_RECURSE USART_CONTROLLER ${PROJECT_ROOT_DIR}/controller/usart/*.c)

add_executable(
    deinit
    deinit.cc
    ${USART_CONTROLLER}
    )

target_include_directories(
    deinit
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/usart
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    deinit
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    deinit
    PRIVATE
    --coverage
    )

target_link_libraries(
    deinit
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(deinit)
