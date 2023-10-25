cmake_minimum_required(VERSION 3.10)

# the name of project
project(stuinfo)

# 定义. srcs变量，其值为当前目录下所有的源代码文件
aux_source_directory(. srcs)

# 编译 SRC 变量所代表的源代码文件，生成 main 可执行文件
add_executable(stuinfo.exe ${srcs})