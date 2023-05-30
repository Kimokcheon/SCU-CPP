cmake_minimum_required(VERSION 3.16)

project(RayTrace)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

aux_source_directory(./src DIR_SRCS)

include_directories(include)

add_executable(main ${DIR_SRCS})

target_link_libraries(main PRIVATE "-Wl,--stack,1000000000")


# find_package(Threads)

# target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})


find_package(OpenMP REQUIRED)
# 添加OpenMP编译选项
target_compile_options(main PUBLIC ${OpenMP_CXX_FLAGS})

# 添加OpenMP链接选项
target_link_libraries(main PUBLIC ${OpenMP_CXX_FLAGS})


# cmake -G"MinGW Makefiles" ..