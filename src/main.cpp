#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "Vector2D.h"

// Socket libraries
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Server.h"
#include "commons.h"

/**
 * Funkce, která vypíše chybovu hlášku a ukončí program
 */
void error(const char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	char *port, *maxPlayers;

	if (argc < 2) {
		std::cout << "Použití: ./server <port> <maxPlayers>" << std::endl;
		exit(1);
	}

	port = argv[1];
	maxPlayers = argv[2];

	if (!Commons::isInteger(port)) {
		error("Port musí být číslo!");
	}

	if (!Commons::isInteger(maxPlayers)) {
		error("Počet hráčů musí být číslo!");
	}

	std::cout << "Host: localhost:" << port << std::endl;

	SnakeServer::ServerSettings serverSettings;
	serverSettings.port = atoi(port);
	serverSettings.maxPlayers = atoi(maxPlayers);

	SnakeServer::Server server;
	server.init(serverSettings);
	server.start();

	return 0;
}