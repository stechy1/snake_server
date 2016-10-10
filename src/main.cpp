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

using namespace std;
using namespace SnakeServer;

/**
 * Funkce, která vypíše chybovu hlášku a ukončí program
 */
void error(const char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	char *port;

	if (argc < 2) {
		cout << "Použití: ./server port" << endl;
		exit(1);
	}

	port = argv[1];

	if (!Commons::isInteger(port)) {
		error("Port musí být číslo!");
	}

	cout << "Host: localhost:" << port << endl;

	ServerSettings serverSettings;
	serverSettings.port = atoi(port);

	Server server;
	server.init(serverSettings);
	server.start();

	return 0;
}