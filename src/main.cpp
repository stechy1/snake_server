#include <iostream>
#include "gameobject/snake/Snake.h"
#include "event/LoginEvent.h"
#include "event/SnakeChangeDirectionEvent.h"
#include "World.h"
#include "network/TCPConnection.h"


class IOImpl : public SnakeServer::Network::IOHandler {
public:
    IOImpl() {}

    virtual ~IOImpl() {}

    virtual void onDataReceived(int socketID, std::list<std::string> data) override {
        for(auto &tmp : data) {
            std::cout << "Data received from: " << socketID << ", content: " << tmp << std::endl;
        }
    }

    virtual void onDisconnect(int socketID) override {
        std::cout << "Oops, disconnected" << std::endl;
    }
};

int main(int argc, char *argv[]) {

    SnakeServer::Network::IOHandler *handler = new IOImpl();
    SnakeServer::Network::TCPConnection connection(10000, *handler);

    connection.init();
    connection.start();

    int i;
    std::cin >> i;

    connection.stop();

    delete handler;
}