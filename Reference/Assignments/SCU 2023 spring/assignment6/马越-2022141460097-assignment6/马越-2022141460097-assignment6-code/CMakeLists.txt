cmake_minimum_required(VERSION 3.18)
project(assignment6)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest CONFIG REQUIRED)

include_directories(h)

enable_testing()

add_executable(assignment6
        cpp/main.cpp
        cpp/linkedlist.cpp
        cpp/unittest.cpp
        h/linkedlist.h
        )

target_link_libraries(assignment6 PRIVATE GTest::gtest GTest::gmock)

include(GoogleTest)

gtest_discover_tests(assignment6)