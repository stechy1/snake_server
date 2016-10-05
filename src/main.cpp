#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
	char *host, *port;

	if (argc < 3) {
		cout << "Použití: ./server host port" << endl;
		exit(1);
	}

	host = argv[1];
	port = argv[2];

	if (!Commons::isInteger(port)) {
		error("Port musí být číslo!");
	}

	cout << "Host: " << host << ":" << port << endl;

	ServerSettings serverSettings;
	serverSettings.port = atoi(port);

	Server server;
	server.init(serverSettings);
	server.start();

	return 0;
}