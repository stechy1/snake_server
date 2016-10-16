cmake_minimum_required(VERSION 3.6)
project(snake_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp src/commons.h src/Server.cpp src/Server.h src/World.cpp src/World.h src/network/TCPConnection.cpp src/network/TCPConnection.h src/network/TCPStream.cpp src/network/TCPStream.h src/gameobject/BaseObject.cpp src/gameobject/BaseObject.h src/IComponent.h src/InputComponent.h src/PhysicsComponent.h src/gameobject/snake/tile/Tail.cpp src/gameobject/snake/tile/Tail.h src/gameobject/food/Food.cpp src/gameobject/food/Food.h src/gameobject/snake/SnakeSimplePhysicsComponent.cpp src/gameobject/snake/SnakeSimplePhysicsComponent.h src/gameobject/snake/SnakeSimpleInputComponent.cpp src/gameobject/snake/SnakeSimpleInputComponent.h src/Client.h src/event/GameEvent.h src/event/LoginEvent.cpp src/event/LoginEvent.h src/DataParser.cpp src/DataParser.h src/event/GameEvent.cpp src/utils/SafeList.h src/utils/SafeMap.h src/utils/SafeQueue.h src/utils/SafeQueue.cpp src/utils/SafeList.cpp src/utils/SafeMap.cpp)
add_executable(snake_server ${SOURCE_FILES})