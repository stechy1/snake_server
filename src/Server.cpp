#include "Server.h"
#include <iostream>

namespace SnakeServer {

    Server::Server() : m_dataParser(/*std::unique_ptr<DataParser>(new DataParser(m_clients))*/std::make_unique<DataParser>(m_clients)) {
        std::cout << "Konstruktor serveru" << std::endl;
        std::srand(time(NULL));
    }

    Server::~Server() {
        m_connection->shutDown();
        m_dataParser->shutDown();
    }

    void Server::init(std::unique_ptr<ServerSettings> &t_serverSettings) {
        m_settings = std::move(t_serverSettings);
        m_world = std::make_unique<World>(m_clients, m_settings->width, m_settings->height);
    }

    void Server::start() {
        std::cout << "Server started" << std::endl;

        m_connection = std::make_unique<Network::TCPConnection>(m_clients, m_settings->port, nullptr);

        if (!m_connection->openPort()) {
            perror("Failed to open port");
            exit(1);
        }

        std::cout << "Port opened" << std::endl;

        std::thread parserThread = m_dataParser->start();
        m_connection->start();

        m_world->generate();
        std::thread worldThread = m_world->start();

        worldThread.join();
        parserThread.join();

        perror("Server finished");
        exit(0);
    }

} // end namespace
