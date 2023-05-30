cmake_minimum_required( VERSION 3.11 )
project( _Sb_tree )

add_library( ${PROJECT_NAME} SHARED tree.cpp unit_test.cpp map.h )

find_package(GTest REQUIRED)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set( CMAKE_CXX_STANDARD 17 )
# add_compile_options(  )

add_executable( main test.cpp unit_test.cpp main.cpp )
target_link_libraries( main ${PROJECT_NAME} GTest::GTest GTest::Main )