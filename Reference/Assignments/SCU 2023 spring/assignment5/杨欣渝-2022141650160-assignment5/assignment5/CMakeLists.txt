cmake_minimum_required(VERSION 3.18)
project(assignment5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O2 -mavx -ffast-math")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()
find_package(GTest CONFIG REQUIRED)
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(
        assignment5_lib
        SHARED
        src/publication.cpp
        src/book.cpp
        src/author.cpp
        src/assignment5.cpp
)
target_include_directories(
        assignment5_lib
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(
        main
        src/main.cpp
        src/unittest.cpp
)

target_link_libraries(main PRIVATE assignment5_lib GTest::gtest GTest::gmock)
include(GoogleTest)
add_test(GoogleTest main)
gtest_discover_tests(main)