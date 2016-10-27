cmake_minimum_required(VERSION 3.5)
project(snake_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES src/main.cpp src/Snake.cpp src/Snake.h src/BaseEvent.h src/IUpdatable.h src/LoginEvent.cpp src/LoginEvent.h src/SnakeChangeDirectionEvent.cpp src/SnakeChangeDirectionEvent.h src/World.cpp src/World.h src/TCPConnection.cpp src/TCPConnection.h src/TCPStream.cpp src/TCPStream.h src/SingleStreamListenerImpl.cpp src/SingleStreamListenerImpl.h src/Protocol.h src/LogoutEvent.cpp src/LogoutEvent.h src/Utils.h)
add_executable(snake_server ${SOURCE_FILES})
