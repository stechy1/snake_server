#include "Server.h"
#include "network/TCPAcceptor.h"
#include "network/TCPStream.h"

#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <errno.h>

#include <iostream>

using namespace SnakeServer::Network;

namespace SnakeServer {

	Server::Server() {
		std::cout << "Konstruktor serveru" << std::endl;
	}

	Server::~Server() {}

	void Server::init(ServerSettings serverSettings) {
		_port = serverSettings.port;
		_maxPlayers = serverSettings.maxPlayers;
	}

	void Server::start() {
		TCPAcceptor acceptor(_port, _maxPlayers);

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
