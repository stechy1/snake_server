#include "Server.h"

#include <iostream>

namespace SnakeServer {

    Server::Server() {
        std::cout << "Konstruktor serveru" << std::endl;
        std::srand(time(NULL));
    }

    Server::~Server() {}

    void Server::init(const ServerSettings t_serverSettings) {
        m_port = t_serverSettings.port;
        m_maxPlayers = t_serverSettings.maxPlayers;
    }

    void Server::start() {
        Network::TCPAcceptor acceptor(m_port);

        std::cout << "Server started" << std::endl;

        if (!acceptor.openPort()) {
            perror("Failed to open port");
            exit(1);
        }

        std::cout << "Port opened" << std::endl;

        acceptor.start();

        perror("Could not start the server");
        exit(1);
    }

} // end namespace
