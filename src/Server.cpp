#include "Server.h"

#include <iostream>

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
	std::cout << "Server started" << std::endl;
}

} // end namespace