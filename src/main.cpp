#include <iostream>
#include "Snake.h"
#include "World.h"
#include "TCPConnection.h"
#include "Protocol.h"

SnakeServer::World *world;
SnakeServer::Network::IOHandler *handler;
SnakeServer::Network::TCPConnection *connection;

class IOImpl : public SnakeServer::Network::IOHandler {
public:
    IOImpl() {}

    virtual ~IOImpl() {}

    virtual void onDataReceived(int socketID, std::list<std::string> data) override {
        for(auto &tmp : data) {
            SnakeServer::Event::BaseEvent *event = SnakeServer::parseEvent(socketID, tmp);
            world->addEvent(event);
        }
    }

    virtual void onDisconnect(int socketID) override {
        std::cout << "Oops, disconnected" << std::endl;
        world->removeSnake(socketID);
        connection->disconnectClient(socketID);
    }
};

int main(int argc, char *argv[]) {
    srand (time(NULL));
    handler = new IOImpl();
    connection = new SnakeServer::Network::TCPConnection(10000, *handler);
    world = new SnakeServer::World(20, 20, *connection);

    connection->init();
    connection->start();

    world->init();
    world->start();

    int i;
    std::cin >> i;

    world->stop();
    connection->stop();

    delete world;
    delete handler;
    delete connection;
}