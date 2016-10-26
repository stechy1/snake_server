#include <iostream>
#include "gameobject/snake/Snake.h"
#include "World.h"
#include "network/TCPConnection.h"
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
            std::cout << "Data received from: " << socketID << ", content: " << tmp << std::endl;
            std::unique_ptr<SnakeServer::Event::BaseEvent> event = SnakeServer::parseEvent(socketID, tmp);
            world->addEvent(*event);
        }
    }

    virtual void onDisconnect(int socketID) override {
        std::cout << "Oops, disconnected" << std::endl;
        world->removeSnake(socketID);
        connection->disconnectClient(socketID);
    }
};

int main(int argc, char *argv[]) {

    world = new SnakeServer::World(400, 300);
    handler = new IOImpl();
    connection = new SnakeServer::Network::TCPConnection(10000, *handler);

    connection->init();
    connection->start();

    world->init();
    world->start();

    int i;
    std::cin >> i;

    world->stop();
    connection->stop();

    delete handler;
    delete world;
    delete connection;
}