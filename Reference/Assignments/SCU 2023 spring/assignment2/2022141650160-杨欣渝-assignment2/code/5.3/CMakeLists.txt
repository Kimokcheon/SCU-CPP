# CMakeLists.txt
cmake_minimum_required(VERSION 3.11)
project(random_generator_project)
add_library(${PROJECT_NAME} SHARED src/RandomGenerator.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(main src/main.cpp)
target_link_libraries(main ${PROJECT_NAME})