file(GLOB_RECURSE DUST_SOURCES ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust/*.c)

add_executable(
    transmission
    transmission.cc
    ${DUST_SOURCES}
    )

target_include_directories(
    transmission
    PRIVATE
    ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    transmission
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    transmission
    PRIVATE
    --coverage
    )

target_link_libraries(
    transmission
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(transmission)
