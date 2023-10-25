#cmake_mininum_required(VERSION 3.18)

project(stuinfo)

aux_source_directory(./src DIR_SRCS)

include_directories(include)

add_executable(stuinfo ${DIR_SRCS})