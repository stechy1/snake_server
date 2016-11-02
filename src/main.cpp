#include <iostream>
#include "Snake.h"
#include "World.h"
#include "TCPConnection.h"
#include "Protocol.h"

SnakeServer::World *g_world = nullptr;

class IOImpl : public SnakeServer::Network::IOHandler {
public:
    IOImpl() {}

    virtual ~IOImpl() {}

    virtual void onDataReceived(int socketID, std::vector<std::string> data) override {
        for(auto &tmp : data) {
            g_world->addEvent(SnakeServer::parseEvent(socketID, tmp));
        }
    }

    virtual void onDisconnect(int socketID) override {
        std::cout << "Oops, disconnected" << std::endl;
        g_world->removeSnake(socketID);
    }
};

int main(int argc, char *argv[]) {
    IOImpl handler;
    SnakeServer::Network::TCPConnection connection(10000, handler);
    SnakeServer::World world(20, 20, connection);
    g_world = &world;

    connection.start();
    world.start();

    int i;
    std::cin >> i;

    world.stop();
    connection.stop();
}