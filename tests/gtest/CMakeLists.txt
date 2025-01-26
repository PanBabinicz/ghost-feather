cmake_minimum_required(VERSION 3.30.2)

project(
    hello_test
    VERSION 1.0.0
    )

find_package(
    GTest
    REQUIRED
    )

enable_testing()

add_subdirectory(hello_test)
