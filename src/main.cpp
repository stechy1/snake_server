#include <stdio.h>
#include <iostream>

#include "Server.h"
#include "event/LoginEvent.h"
#include "gameobject/snake/SnakeSimplePhysicsComponent.h"
#include "gameobject/snake/SnakeSimpleInputComponent.h"
#include "TempObject.h"

void testing() {
//    SnakeServer::Client client;
    std::unique_ptr<SnakeServer::Vector2D> vec1 = std::make_unique<SnakeServer::Vector2D>();
    std::unique_ptr<SnakeServer::Vector2D> vec2 = std::make_unique<SnakeServer::Vector2D>();
    std::unique_ptr<SnakeServer::InputComponent> input = std::unique_ptr<SnakeServer::GameObject::Snake::SnakeSimpleInputComponent>(new SnakeServer::GameObject::Snake::SnakeSimpleInputComponent());
    std::unique_ptr<SnakeServer::PhysicsComponent> physics = std::unique_ptr<SnakeServer::GameObject::Snake::SnakeSimplePhysicsComponent>(new SnakeServer::GameObject::Snake::SnakeSimplePhysicsComponent);
//    std::unique_ptr<SnakeServer::GameObject::Snake::Snake> snake = std::make_unique<SnakeServer::GameObject::Snake::Snake>(
//            std::move(vec1),
//            std::move(vec2),
//            std::move(input),
//            std::move(physics)
//    );
    SnakeServer::TempObject temp(
            std::move(vec1),
            std::move(vec2),
            std::move(input),
            std::move(physics));
//    SnakeServer::GameObject::Snake::Snake *snake = new SnakeServer::GameObject::Snake::Snake(
//            std::move(vec1),
//            std::move(vec2),
//            std::move(input),
//            std::move(physics));
    //std::unique_ptr<SnakeServer::Event::GameEvent> event = std::make_unique<SnakeServer::Event::LoginEvent>(1, "username");
    SnakeServer::Event::LoginEvent event1(1, "event1");

    //client.snake->addEvent(std::move(event));
//    std::shared_ptr<SnakeServer::GameObject::Snake::Snake> snake = client.snake;
//    SnakeServer::GameObject::Snake::Snake *mySnake;
//    mySnake = snake.get();
//    mySnake->addEvent(&event1);
    //snake->addEvent(&event1);
}

int main(int argc, char *argv[]) {
    testing();
    return 0;

    if (argc < 2) {
        std::cout << "Použití: ./server -port <port> -players <maxPlayers> -width <width> -height <height>" << std::endl;
        exit(1);
    }

    std::unique_ptr<SnakeServer::ServerSettings> settings = std::make_unique<SnakeServer::ServerSettings>();
    int i = 0;

    while (i < argc - 1) {
        std::string param(argv[++i]);
        std::cout << "Testuji argument: " << param << std::endl;

        if (param.compare("-port") == 0) {
            std::string port = argv[++i];

            if (!SnakeServer::Utils::isInteger(port)) {
                perror("Port musí být číslo");
                exit(1);
            }

            settings->port = std::stoi(port);
            std::cout << "Nastavuji port na: " << port << std::endl;
            continue;
        }

        if (param == "-players") {
            std::string playersCount = argv[++i];

            if (!SnakeServer::Utils::isInteger(playersCount)) {
                perror("Počet hráčů musí být číslo");
                exit(1);
            }

            settings->maxPlayers = std::stoi(playersCount);
            std::cout << "Nastavuji maximalni pocet hracu na: " << playersCount << std::endl;
            continue;
        }

        if (param == "-w" || param == "-width") {
            std::string width = argv[++i];

            if (!SnakeServer::Utils::isInteger(width)) {
                perror("Šířka mapy musí být číslo");
                exit(1);
            }

            settings->width = std::stoi(width);
            continue;
        }

        if (param == "-h" || param == "-height") {
            std::string height = argv[++i];

            if (!SnakeServer::Utils::isInteger(height)) {
                perror("Výška mapy musí být číslo");
                exit(1);
            }

            settings->height = std::stoi(height);
            continue;
        }
    }

    std::cout << "Program arguments parsed..." << std::endl;

    SnakeServer::Server server;
    server.init(std::move(settings));
    server.start();

    std::cout << "Unexpected exit" << std::endl;
    return 0;
}