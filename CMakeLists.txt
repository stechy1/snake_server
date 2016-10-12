cmake_minimum_required(VERSION 3.6)
project(snake_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp src/commons.h src/Server.cpp src/Server.h src/World.cpp src/World.h src/network/TCPAcceptor.cpp src/network/TCPAcceptor.h src/network/TCPStream.cpp src/network/TCPStream.h)
add_executable(snake_server ${SOURCE_FILES})