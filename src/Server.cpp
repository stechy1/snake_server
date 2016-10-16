#include "Server.h"
#include <iostream>

namespace SnakeServer {

    Server::Server() /*: m_dataParser(std::make_unique<DataParser>(m_clients))*/ {
        std::srand(time(NULL));

        m_clients = new clientsMap_t;

        std::cout << "Server initialized" << std::endl;
    }

    Server::~Server() {
        std::cout << "Shutting down server..." << std::endl;
        m_connection->shutDown();
        m_dataParser->shutDown();

        delete m_dataParser;
        delete m_clients;
    }

    void Server::init(std::unique_ptr<ServerSettings> &t_serverSettings) {
        std::cout << "Server initialization..." << std::endl;
        m_settings = std::move(t_serverSettings);
        //m_world = std::make_unique<World>(m_clients, m_settings->width, m_settings->height);
        //m_dataParser = std::make_unique<DataParser>(m_clients);
        m_dataParser = new DataParser(m_clients);
        std::cout << "Server initialization done..." << std::endl;
    }

    void Server::start() {
        std::cout << "Server started" << std::endl;

        m_connection = std::make_unique<Network::TCPConnection>(m_clients, m_settings->port, m_dataParser);

        if (!m_connection->openPort()) {
            perror("Failed to open port");
            exit(1);
        }

        std::cout << "Port opened" << std::endl;

        //std::thread parserThread = m_dataParser->start();
        //m_connection->start();

        //m_world->generate();
        //std::thread worldThread = m_world->start();

        //worldThread.join();
        //parserThread.join();

        m_connection->start().join();

        perror("Server finished");
        //exit(0);
    }

} // end namespace
