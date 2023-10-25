cmake_minimum_required(VERSION 3.24)
project(assignment6)

include(FetchContent)

include(GoogleTest)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(assignment6 cpp/main.cpp cpp/linkedlist.cpp h/linkedlist.h cpp/unittest.cpp)

target_link_libraries(assignment6 GTest::GTest GTest::Main)
