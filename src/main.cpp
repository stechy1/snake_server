#include <iostream>
#include <boost/uuid/uuid.hpp>
#include "World.h"
#include "Protocol.h"
#include "SimpleLogger.h"

typedef boost::uuids::uuid uuid;

SnakeServer::World *g_world = nullptr;
SnakeServer::Network::Server *g_server;

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
        LOG_INFO << "Client is disconnected";
        g_server->disconnectClient(clientID);
    }
};

int main(int argc, char *argv[]) {
    LOG_INFO << "╔════════════════╗";
    LOG_INFO << "║                ║";
    LOG_INFO << "║  Snake server  ║";
    LOG_INFO << "║                ║";
    LOG_INFO << "╚════════════════╝";
    LOG_INFO << "Starting up...";
    IOImpl handler;
    uuid seed;
    SnakeServer::Network::Server server(10000, handler, seed);
    g_server = &server;
    SnakeServer::World world(300, 300, server);
    g_world = &world;

    server.start();
    world.start();
    LOG_INFO << "Server running";

    int i;
    std::cin >> i;

    LOG_INFO << "Shutting down the server.";
    world.stop();
    server.stop();
    LOG_INFO << "Server is down.";
    LOG_INFO << "Bye.";
}