file(GLOB_RECURSE BMI270 ${PROJECT_ROOT_DIR}/controller/bmi270/*.c)
file(GLOB_RECURSE SPI_CTRL ${PROJECT_ROOT_DIR}/controller/spi/*.c)

add_executable(
    bmi270_init
    init.cc
    ${BMI270}
    ${SPI_CTRL}
    )

target_include_directories(
    bmi270_init
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/bmi270
    ${PROJECT_ROOT_DIR}/controller/spi
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_definitions(
    bmi270_init
    PRIVATE
    STM32F7
    BMI270_VLD_CONF_FILE
    )

target_compile_options(
    bmi270_init
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    bmi270_init
    PRIVATE
    --coverage
    )

target_link_libraries(
    bmi270_init
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(bmi270_init)
