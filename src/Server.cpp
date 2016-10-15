#include "Server.h"

#include <iostream>

namespace SnakeServer {

    Server::Server() {
        std::cout << "Konstruktor serveru" << std::endl;
        std::srand(time(NULL));
    }

    Server::~Server() {}

    void Server::init(std::unique_ptr<ServerSettings> &t_serverSettings) {
        m_settings = std::move(t_serverSettings);
    }

    void Server::start() {
        Network::TCPAcceptor acceptor(m_settings->port);

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
