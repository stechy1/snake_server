#include <iostream>
#include <boost/uuid/uuid.hpp>
#include "World.h"
#include "Protocol.h"

typedef boost::uuids::uuid uuid;

SnakeServer::World *g_world = nullptr;
SnakeServer::Network::Server *g_conn;

class IOImpl : public SnakeServer::Network::IOHandler {
public:
    IOImpl() {}

    virtual ~IOImpl() {}

    virtual void onDataReceived(uuid clientID, std::vector<std::string> data) override {
        for (auto &tmp : data) {
            g_world->addEvent(SnakeServer::parseEvent(clientID, tmp));
        }
    }

    virtual void onDisconnect(uuid clientID) override {
        std::cout << "Oops, disconnected" << std::endl;
        g_world->removeSnake(clientID);
        g_conn->disconnectClient(clientID);
    }
};

int main(int argc, char *argv[]) {
    IOImpl handler;
    uuid seed;
    SnakeServer::Network::Server connection(10000, handler, seed);
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