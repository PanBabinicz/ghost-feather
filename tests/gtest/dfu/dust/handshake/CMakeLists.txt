file(GLOB_RECURSE DUST_SOURCES ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust/*.c)

add_executable(
    handshake
    handshake.cc
    ${DUST_SOURCES}
    )

target_include_directories(
    handshake
    PRIVATE
    ${PROJECT_ROOT_DIR}/dfu/stm32f722xx/dust
    ${PROJECT_ROOT_DIR}/tests/gmock
    )

target_compile_options(
    handshake
    PRIVATE
    --coverage
    -g
    -O0
    )

target_link_options(
    handshake
    PRIVATE
    --coverage
    )

target_link_libraries(
    handshake
    PRIVATE
    GTest::gtest_main
    )

include(GoogleTest)
gtest_discover_tests(handshake)
