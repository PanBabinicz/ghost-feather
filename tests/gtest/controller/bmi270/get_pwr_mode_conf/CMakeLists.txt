file(GLOB_RECURSE BMI270 ${PROJECT_ROOT_DIR}/controller/bmi270/*.c)
file(GLOB_RECURSE SPI_CTRL ${PROJECT_ROOT_DIR}/controller/spi/*.c)

add_executable(
    get_pwr_mode_conf
    get_pwr_mode_conf.cc
    ${BMI270}
    ${SPI_CTRL}
    )

target_include_directories(
    get_pwr_mode_conf
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/bmi270
    ${PROJECT_ROOT_DIR}/controller/spi
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_definitions(
    get_pwr_mode_conf
    PRIVATE
    STM32F7
    )

target_compile_options(
    get_pwr_mode_conf
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    get_pwr_mode_conf
    PRIVATE
    --coverage
    )

target_link_libraries(
    get_pwr_mode_conf
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(get_pwr_mode_conf)
