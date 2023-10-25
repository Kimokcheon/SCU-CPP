cmake_minimum_required(VERSION 3.13)
project(Assignment5)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/assignment5.cpp
        src/author.cpp
        src/publication.cpp
        src/book.cpp
        src/unittest.cpp
)

target_compile_options(main PRIVATE -g)

target_link_libraries(main
        GTest::GTest
        GTest::Main
)