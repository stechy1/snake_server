cmake_minimum_required(VERSION 3.6)
project(snake_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp)
add_executable(snake_server ${SOURCE_FILES})