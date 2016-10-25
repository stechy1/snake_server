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

// Otestuje aplikaci eventu změny směru na hada
void testing() {
    std::unique_ptr<SnakeServer::Vector2D> pos = std::make_unique<SnakeServer::Vector2D>(SnakeServer::Vector2D::ZERO());
    std::unique_ptr<SnakeServer::Vector2D> dir = std::make_unique<SnakeServer::Vector2D>(SnakeServer::Vector2D::RIGHT());
    std::unique_ptr<SnakeServer::Vector2D> vel = std::make_unique<SnakeServer::Vector2D>(SnakeServer::Vector2D::ONES());
    SnakeServer::GameObject::Snake::Snake snake(std::move(pos), std::move(dir), std::move(vel));
    std::shared_ptr<SnakeServer::Event::BaseEvent> event1 = std::make_shared<SnakeServer::Event::SnakeChangeDirectionEvent>(1, std::make_shared<SnakeServer::Vector2D>(-0.7797703670711318, 0.626065631254226));
    std::shared_ptr<SnakeServer::Event::BaseEvent> event2 = std::make_shared<SnakeServer::Event::SnakeChangeDirectionEvent>(1, std::make_shared<SnakeServer::Vector2D>(-0.69, -0.1));

//    // První update - neaplikuje žádný event
//    snake.update(0,0);
//
    // Přidá do EventQueue dva eventy o změně směru
    snake.addEvent(event1);
    snake.addEvent(event2);
//
//    // Vyvolá dva updaty které změní vektor směru hada
//    snake.update(0,0);
//    snake.update(0,0);

    SnakeServer::World world(400, 300);

    world.start();
    world.addSnake(1);
}

int main(int argc, char *argv[]) {

    SnakeServer::Network::IOHandler *handler = new IOImpl();
    SnakeServer::Network::TCPConnection connection(*handler);

    connection.init();
    connection.start();

    int i;
    std::cin >> i;

    connection.stop();

    delete handler;
}