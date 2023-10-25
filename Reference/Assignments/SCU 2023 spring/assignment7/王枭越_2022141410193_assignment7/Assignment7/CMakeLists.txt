cmake_minimum_required(VERSION 3.13)
project(Assignment7)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_test.cpp
        src/espresso_based.cpp
        src/cappuccino.cpp
        src/mocha.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
)

target_compile_options(main PRIVATE -g)