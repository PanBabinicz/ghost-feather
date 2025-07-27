file(GLOB_RECURSE BMI270 ${PROJECT_ROOT_DIR}/controller/bmi270/*.c)
file(GLOB_RECURSE SPI_CTRL ${PROJECT_ROOT_DIR}/controller/spi/*.c)

add_executable(
    get_dev
    get_dev.cc
    ${BMI270}
    ${SPI_CTRL}
    )

target_include_directories(
    get_dev
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/bmi270
    ${PROJECT_ROOT_DIR}/controller/spi
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_definitions(
    get_dev
    PRIVATE
    STM32F7
    )

target_compile_options(
    get_dev
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    get_dev
    PRIVATE
    --coverage
    )

target_link_libraries(
    get_dev
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(get_dev)
