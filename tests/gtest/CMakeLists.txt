cmake_minimum_required(VERSION 3.30.2)

project(
    ghost-feather-tests
    VERSION 1.0.0
    )

find_package(
    GTest
    REQUIRED
    )

enable_testing()

add_subdirectory(controller/bmi270)
add_subdirectory(controller/usart)
add_subdirectory(data_structure/circular_buffer)
add_subdirectory(dfu/dust)
