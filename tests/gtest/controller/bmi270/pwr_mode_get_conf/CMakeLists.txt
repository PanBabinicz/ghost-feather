file(GLOB_RECURSE BMI270 ${PROJECT_ROOT_DIR}/controller/bmi270/*.c)
file(GLOB_RECURSE SPI_CTRL ${PROJECT_ROOT_DIR}/controller/spi/*.c)

add_executable(
    pwr_mode_get_conf
    pwr_mode_get_conf.cc
    ${BMI270}
    ${SPI_CTRL}
    )

target_include_directories(
    pwr_mode_get_conf
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/bmi270
    ${PROJECT_ROOT_DIR}/controller/spi
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_definitions(
    pwr_mode_get_conf
    PRIVATE
    STM32F7
    )

target_compile_options(
    pwr_mode_get_conf
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    pwr_mode_get_conf
    PRIVATE
    --coverage
    )

target_link_libraries(
    pwr_mode_get_conf
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(pwr_mode_get_conf)
