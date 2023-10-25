cmake_minimum_required(VERSION 3.25)
project(bookshelf)

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

add_executable(bookshelf src/main.cpp src/assignment5.cpp src/author.cpp src/book.cpp src/publication.cpp  include/assignment5.h include/author.h include/book.h include/publication.h src/unittest.cpp)

target_link_libraries(bookshelf GTest::GTest GTest::Main)
