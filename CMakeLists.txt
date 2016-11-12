cmake_minimum_required(VERSION 3.0)
project(snake_server)

if (CYGWIN)
    set(BOOSTROOT "C:/boost_1_61_0")
endif()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

if (CYGWIN)
    add_definitions(-DBOOST_THREAD_POSIX -D_XOPEN_SOURCE=700)
endif()

find_package(Boost 1.61.0 COMPONENTS log)

set(CMAKE_CXX_FLAGS "-std=c++14 -pthread")
set(SOURCE_FILES src/main.cpp src/Snake.cpp src/Snake.h src/World.cpp src/World.h src/Server.cpp src/Server.h src/TCPStream.cpp src/TCPStream.h src/SingleStreamListenerImpl.cpp src/SingleStreamListenerImpl.h src/Protocol.h src/Food.cpp src/Food.h src/Event.cpp src/Event.h src/Vector2D.h src/SimpleLogger.cpp src/SimpleLogger.h)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(snake_server ${SOURCE_FILES})
    target_link_libraries(snake_server ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find boost")
endif()