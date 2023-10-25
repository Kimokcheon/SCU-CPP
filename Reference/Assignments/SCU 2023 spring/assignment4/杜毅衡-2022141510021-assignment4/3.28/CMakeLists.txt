cmake_minimum_required(VERSION 3.16)

project(project)

aux_source_directory(./src DIR_SRCS)

include_directories(include)

add_executable(project ${DIR_SRCS})

#cmake -G"MinGW Makefiles" ..