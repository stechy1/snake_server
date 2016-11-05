#include <iostream>
#include "World.h"
#include "Protocol.h"
#include "boost/log/trivial.hpp"

SnakeServer::World *g_world = nullptr;
SnakeServer::Network::TCPConnection *g_conn;

class IOImpl : public SnakeServer::Network::IOHandler {
public:
    IOImpl() {}

    virtual ~IOImpl() {}

    virtual void onDataReceived(int socketID, std::vector<std::string> data) override {
        for (auto &tmp : data) {
            g_world->addEvent(SnakeServer::parseEvent(socketID, tmp));
        }
    }

    virtual void onDisconnect(int socketID) override {
        std::cout << "Oops, disconnected" << std::endl;
        g_world->removeSnake(socketID);
        g_conn->disconnectClient(socketID);
    }
};

int main(int argc, char *argv[]) {
    IOImpl handler;
    SnakeServer::Network::TCPConnection connection(10000, handler);
    g_conn = &connection;
    SnakeServer::World world(300, 300, connection);
    g_world = &world;

    connection.start();
    world.start();

    int i;
    std::cin >> i;

    world.stop();
    connection.stop();
}