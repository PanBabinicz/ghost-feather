file(GLOB_RECURSE BMI270 ${PROJECT_ROOT_DIR}/controller/bmi270/*.c)
file(GLOB_RECURSE SPI_CTRL ${PROJECT_ROOT_DIR}/controller/spi/*.c)

add_executable(
    bmi270_gyr_set_z
    gyr_set_z.cc
    ${BMI270}
    ${SPI_CTRL}
    )

target_include_directories(
    bmi270_gyr_set_z
    PRIVATE
    ${PROJECT_ROOT_DIR}/controller/bmi270
    ${PROJECT_ROOT_DIR}/controller/spi
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_definitions(
    bmi270_gyr_set_z
    PRIVATE
    STM32F7
    )

target_compile_options(
    bmi270_gyr_set_z
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    bmi270_gyr_set_z
    PRIVATE
    --coverage
    )

target_link_libraries(
    bmi270_gyr_set_z
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(bmi270_gyr_set_z)
