cmake_minimum_required(VERSION 3.5)
project(snake_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES src/main.cpp src/gameobject/BaseObject.cpp src/gameobject/BaseObject.h src/gameobject/snake/Snake.cpp src/gameobject/snake/Snake.h src/event/BaseEvent.h src/event/IUpdatable.h src/event/LoginEvent.cpp src/event/LoginEvent.h src/event/SnakeChangeDirectionEvent.cpp src/event/SnakeChangeDirectionEvent.h src/World.cpp src/World.h src/network/TCPConnection.cpp src/network/TCPConnection.h src/network/TCPStream.cpp src/network/TCPStream.h src/network/SingleStreamListenerImpl.cpp src/network/SingleStreamListenerImpl.h src/Protocol.h src/event/LogoutEvent.cpp src/event/LogoutEvent.h src/Utils.h)
add_executable(snake_server ${SOURCE_FILES})
