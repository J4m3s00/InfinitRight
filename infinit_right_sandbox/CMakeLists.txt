cmake_minimum_required(VERSION 3.15)

add_executable(InfinitRightSandbox src/main.cpp)

#Test The linkage and usage of gravity
target_link_libraries(InfinitRightSandbox ${CMAKE_SOURCE_DIR}/../gravity/build/libgravityapi_s.a)


target_link_libraries(InfinitRightSandbox InfinitRight)