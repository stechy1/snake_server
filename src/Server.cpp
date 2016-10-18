#include "Server.h"
#include <iostream>

namespace SnakeServer {

    Server::Server() {
        std::srand(time(NULL));
        m_clients = new clientsMap_t;
        std::cout << "Server initialized" << std::endl;
    }

    Server::~Server() {
        std::cout << "Shutting down server..." << std::endl;
        m_dataParser->shutDown();
        m_world->shutDown();
        m_connection->shutDown();

        delete m_clients;
    }

    void Server::init(std::unique_ptr<ServerSettings> t_serverSettings) {
        std::cout << "Server initialization..." << std::endl;
        m_settings = std::move(t_serverSettings);
        std::cout << "Server port: " << m_settings->port << std::endl;
        m_world = std::make_unique<World>(m_clients, m_settings->width, m_settings->height);
        m_dataParser = std::make_shared<DataParser>(m_clients);
        std::cout << "Server initialization done..." << std::endl;
    }

    void Server::start() {
        m_world->generate();

        m_connection = std::make_unique<Network::TCPConnection>(m_clients, m_settings->port, m_dataParser);

        if (!m_connection->openPort()) {
            perror("Failed to open port");
            exit(1);
        }

        std::cout << "Port opened" << std::endl;

        std::cout << "Starting service threads..." << std::endl;
        m_dataParser->start();
        m_world->start();
        m_connection->start();
        std::cout << "Service threads started." << std::endl;

        std::cout << "Server started" << std::endl;

//        worldThread.join();
//        parserThread.join();
//        connectionThread.join();

        int n;
        std::cin >> n;

        std::cout << "Server finished" << std::endl;
    }

} // end namespace
