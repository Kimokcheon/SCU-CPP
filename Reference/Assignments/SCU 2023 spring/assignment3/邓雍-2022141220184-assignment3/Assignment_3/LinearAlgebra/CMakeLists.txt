cmake_minimum_required(VERSION 3.13)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/linearalgebra.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
)

