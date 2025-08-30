file(GLOB_RECURSE BMI270 ${PROJECT_ROOT_DIR}/controller/bmi270/*.c)
file(GLOB_RECURSE SPI_CTRL ${PROJECT_ROOT_DIR}/controller/spi/*.c)

add_executable(
    dev_get
    dev_get.cc
    ${BMI270}
    ${SPI_CTRL}
    )

target_include_directories(
    dev_get
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/bmi270
    ${PROJECT_ROOT_DIR}/controller/spi
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_definitions(
    dev_get
    PRIVATE
    STM32F7
    )

target_compile_options(
    dev_get
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    dev_get
    PRIVATE
    --coverage
    )

target_link_libraries(
    dev_get
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(dev_get)
