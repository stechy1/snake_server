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

    virtual void onDataReceived(const uuid &clientID, const std::vector<std::string> data) const override {
        for (auto &tmp : data) {
            g_world->addEvent(SnakeServer::parseEvent(clientID, tmp));
        }
    }

    virtual void onDisconnect(const uuid &clientID) const override {
        LOG_INFO << "Client is disconnected";
        g_server->disconnectClient(clientID);
    }
};

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "Nesprávný počet parametrů" << std::endl;
        std::cout << "./snake_server port [ip]" << std::endl;
        exit(1);
    }

    int port = atoi(argv[1]);


    LOG_INFO << "╔════════════════════════════════════════════════════════════════════╗";
    LOG_INFO << "║	   _____             _                                        	║";
    LOG_INFO << "║	  / ____|           | |                                      	║";
    LOG_INFO << "║	 | (___  _ __   __ _| | _____   ___  ___ _ ____   _____ _ __ 	║";
    LOG_INFO << "║	  \\___ \\| '_ \\ / _` | |/ / _ \\ / __|/ _ | '__\\ \\ / / _ | '__|	║";
    LOG_INFO << "║	  ____) | | | | (_| |   |  __/ \\__ |  __| |   \\ V |  __| |   	║";
    LOG_INFO << "║	 |_____/|_| |_|\\__,_|_|\\_\\___| |___/\\___|_|    \\_/ \\___|_|   	║";
    LOG_INFO << "║	                                                             	║";
    LOG_INFO << "╚════════════════════════════════════════════════════════════════════╝";
    LOG_INFO << "Starting up...";
    IOImpl handler;
    uuid seed;
    SnakeServer::Network::Server server(port, handler, seed);
    g_server = &server;
    SnakeServer::World world(600, 600, server);
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