#include <stdio.h>
#include <iostream>

#include "Server.h"
#include "commons.h"

std::unique_ptr<SnakeServer::ServerSettings> parseArguments(int argc, char *argv[]) {
    std::unique_ptr<SnakeServer::ServerSettings> settings = std::make_unique<SnakeServer::ServerSettings>();
    int i = 0;

    while (i < argc) {
        std::string param(argv[++i]);

        if (param == "-port") {
            std::string port = argv[++i];

            if (!Commons::isInteger(port)) {
                perror("Port musí být číslo");
                exit(1);
            }

            settings->port = std::stoi(port);
            continue;
        }

        if (param == "-players") {
            std::string playersCount = argv[++i];

            if (!Commons::isInteger(playersCount)) {
                perror("Počet hráčů musí býr číslo");
            }

            settings->maxPlayers = std::stoi(playersCount);
            continue;
        }

        if (param == "-w" || param == "-width") {
            std::string width = argv[++i];

            if (!Commons::isInteger(width)) {
                perror("Šířka mapy musí býr číslo");
            }

            settings->width = std::stoi(width);
            continue;
        }

        if (param == "-h" || param == "-height") {
            std::string height = argv[++i];

            if (!Commons::isInteger(height)) {
                perror("Výška mapy musí býr číslo");
            }

            settings->height = std::stoi(height);
            continue;
        }
    }

    return settings;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Použití: ./server -port <port> -players <maxPlayers> -width <width> -height <height>" << std::endl;
        exit(1);
    }

    std::unique_ptr<SnakeServer::ServerSettings> settings;

    try {
        settings = parseArguments(argc, argv);
    } catch (std::runtime_error ex) {

        exit(1);
    }


    SnakeServer::Server server;
    server.init(settings);
    server.start();

    return 0;
}