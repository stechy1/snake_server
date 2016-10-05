#include "Server.h"
#include "network/TCPAcceptor.h"
#include "network/TCPStream.h"

#include <stdio.h>
#include <string.h>

#include <iostream>

using namespace SnakeServer::Network;

namespace SnakeServer {

	Server::Server(void) {
		std::cout << "Konstruktor serveru" << std::endl;
	}

	Server::~Server(void) {}

	void Server::init(ServerSettings serverSettings) {
		this->_port = serverSettings.port;
		this->_maxPlayers = serverSettings.maxPlayers;
	}

	void Server::start( void ) {

		TCPStream*   stream = NULL;
		TCPAcceptor* acceptor = NULL;

		std::cout << "Server started" << std::endl;

		acceptor = new TCPAcceptor(_port);
		if (acceptor->start() == 0) {
			for(;;) {
				stream = acceptor->accept();
				if (stream != NULL) {
					size_t len;
					char line[256];
					while ((len = stream->receive(line, sizeof(line), 0)) > 0) {
						line[len] = '\0';
						std::cout << "Recieved: " << line << std::endl;
					}
					delete stream;
				}
			}
		}

		perror("Could not start the server");
		exit(1);
	}

} // end namespace
