file(GLOB_RECURSE DUST_SOURCES ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust/*.c)

add_executable(
    payload
    payload.cc
    ${DUST_SOURCES}
    )

target_include_directories(
    payload
    PRIVATE
    ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    payload
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    payload
    PRIVATE
    --coverage
    )

target_link_libraries(
    payload
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(payload)
