cmake_minimum_required(VERSION 3.0)
project(snake_server)

set(BOOSTROOT "/usr/include/boost")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system thread log)

set(CMAKE_CXX_FLAGS "-std=c++14 -pthread")
set(SOURCE_FILES src/main.cpp src/Snake.cpp src/Snake.h src/World.cpp src/World.h src/Server.cpp src/Server.h src/TCPStream.cpp src/TCPStream.h src/SingleStreamListenerImpl.cpp src/SingleStreamListenerImpl.h src/Protocol.h src/Food.cpp src/Food.h src/Event.cpp src/Event.h src/Vector2D.h src/SimpleLogger.cpp src/SimpleLogger.h)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(snake_server ${SOURCE_FILES})
target_link_libraries(snake_server ${Boost_LIBRARIES})