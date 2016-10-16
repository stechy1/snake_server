#include <stdio.h>
#include <iostream>

#include "Server.h"
#include "commons.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Použití: ./server -port <port> -players <maxPlayers> -width <width> -height <height>" << std::endl;
        exit(1);
    }

    std::unique_ptr<SnakeServer::ServerSettings> settings = std::make_unique<SnakeServer::ServerSettings>();
    int i = 0;

    while (i < argc) {
        std::string param(argv[++i]);
        std::cout << "Testuji argument: " << param << std::endl;

        if (param.compare("-port") == 0) {
            std::string port = argv[++i];

            if (!Commons::isInteger(port)) {
                perror("Port musí být číslo");
                exit(1);
            }

            settings->port = std::stoi(port);
            std::cout << "Nastavuji port na: " << port << std::endl;
            continue;
        }

        if (param == "-players") {
            std::string playersCount = argv[++i];

            if (!Commons::isInteger(playersCount)) {
                perror("Počet hráčů musí být číslo");
                exit(1);
            }

            settings->maxPlayers = std::stoi(playersCount);
            std::cout << "Nastavuji maximalni pocet hracu na: " << playersCount << std::endl;
            continue;
        }

        if (param == "-w" || param == "-width") {
            std::string width = argv[++i];

            if (!Commons::isInteger(width)) {
                perror("Šířka mapy musí být číslo");
                exit(1);
            }

            settings->width = std::stoi(width);
            continue;
        }

        if (param == "-h" || param == "-height") {
            std::string height = argv[++i];

            if (!Commons::isInteger(height)) {
                perror("Výška mapy musí být číslo");
                exit(1);
            }

            settings->height = std::stoi(height);
            continue;
        }
    }

    std::cout << "Program arguments parsed..." << std::endl;

//    try {
//        SnakeServer::Server server;
//        server.init(settings);
//        server.start();
//    } catch (std::exception ex) {
//        std::cout << ex.what() << std::endl;
//    }

    std::cout << "Unexpected exit" << std::endl;
    return 0;
}