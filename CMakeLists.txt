cmake_minimum_required(VERSION 3.5)
project(snake_server)

if (CYGWIN)
    set(BOOSTROOT "C:/boost_1_62_0")
endif ()

find_package(Boost)

if (Boost_FOUND)
    set(CMAKE_CXX_FLAGS "-std=c++14 -pthread -lboost_log -DBOOST_LOG_DYN_LINK")
    include_directories(${Boost_INCLUDE_DIRS})

    set(SOURCE_FILES src/main.cpp src/Snake.cpp src/Snake.h src/World.cpp src/World.h src/TCPConnection.cpp src/TCPConnection.h src/TCPStream.cpp src/TCPStream.h src/SingleStreamListenerImpl.cpp src/SingleStreamListenerImpl.h src/Protocol.h src/Food.cpp src/Food.h src/Event.cpp src/Event.h src/Vector2D.h)
    add_executable(snake_server ${SOURCE_FILES})
else ()
    message(FATAL_ERROR "Could not find boost!")
endif ()


