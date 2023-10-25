cmake_minimum_required(VERSION 3.14)
project(Login)

include(FetchContent)

include(GoogleTest)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)

include_directories(include/${GTEST_INCLUDE_DIRS})

add_executable(Login main.cpp login.cpp unit_test.cpp login.h)

target_link_libraries(Login
        GTest::GTest
        GTest::Main
        )