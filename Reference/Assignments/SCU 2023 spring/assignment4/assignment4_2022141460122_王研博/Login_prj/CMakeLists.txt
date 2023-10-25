cmake_minimum_required(VERSION 3.16)
project(Login_prj)

set(CMAKE_CXX_STANDARD 14)
find_package(GTest REQUIRED)
include_directories(include/)
add_executable(main
        src/login.cpp
        src/main.cpp
        src/unit_test.cpp)
target_link_libraries(main
        GTest::GTest
        GTest::Main
        )
