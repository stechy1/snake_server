cmake_minimum_required(VERSION 3.6)
project(snake_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if (CYGWIN)
    set(BOOSTROOT "C:/boost_1_62_0")
else ()
    set(BOOSTROOT "/usr/include/boost")
endif ()
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost)

if(Boost_FOUND)
    set(SOURCE_FILES src/main.cpp src/gameobject/BaseObject.cpp src/gameobject/BaseObject.h src/gameobject/snake/Snake.cpp src/gameobject/snake/Snake.h src/event/BaseEvent.cpp src/event/BaseEvent.h src/event/IUpdatable.h src/event/LoginEvent.cpp src/event/LoginEvent.h src/event/SnakeChangeDirectionEvent.cpp src/event/SnakeChangeDirectionEvent.h src/World.cpp src/World.h src/network/TCPConnection.cpp src/network/TCPConnection.h src/network/TCPStream.cpp src/network/TCPStream.h src/Server.cpp src/Server.h)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(snake_server ${SOURCE_FILES})
    target_link_libraries(snake_server ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find boost!")
endif()
