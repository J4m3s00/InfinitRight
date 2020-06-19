cmake_minimum_required(VERSION 3.15)
project(InfinitRight)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
add_compile_definitions(IR_WIN)
elseif(APPLE)
add_compile_definitions(IR_MAC)
endif()

include_directories(infinit_right/src/)

add_subdirectory(infinit_right)
add_subdirectory(infinit_right_sandbox)



