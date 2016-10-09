#include "Server.h"
#include "network/TCPAcceptor.h"
#include "network/TCPStream.h"

#include <stdio.h>
#include <string.h>
#include <sys/select.h>

#include <iostream>

using namespace SnakeServer::Network;

namespace SnakeServer {

	Server::Server(void) {
		std::cout << "Konstruktor serveru" << std::endl;

		FD_ZERO(&master_fds);
		FD_ZERO(&read_fds);
		FD_ZERO(&write_fds);
	}

	Server::~Server(void) {
		std::vector<TCPStream*>::iterator iter;
		for(iter = clients.begin(); iter != clients.end(); iter++) {
			delete *iter;
		}
	}

	void Server::init(ServerSettings serverSettings) {
		this->_port = serverSettings.port;
		this->_maxPlayers = serverSettings.maxPlayers;
	}

	void Server::start( void ) {
		int i = 0;
		//TCPStream*   stream = NULL;
		TCPAcceptor* acceptor = NULL;

		std::cout << "Server started" << std::endl;

		acceptor = new TCPAcceptor(_port);

		int listen_sock = acceptor->start();
		if (listen_sock < 0) {
			perror("Failed to create listen sock");
			exit(1);
		}

		// Přidání server listeneru do seznamu "master_fsd"
		FD_SET(listen_sock, &master_fds);
		fdMax = listen_sock;
		fdMin = listen_sock;

		for(;;) {
			// Zkopírování hlavního seznamu do čtecího a zapisovacího
		    memcpy(&read_fds, &master_fds, sizeof(master_fds));
		    memcpy(&write_fds, &master_fds, sizeof(master_fds));

		    // Čekám na jakoukoliv akci
		    if (select(fdMax + 1, &read_fds, &write_fds, NULL, NULL) == -1) {
		    	close(listen_sock);
		    	perror("Chyba v selectu");
		    	exit(1);
		    }

		    // Proiteruj všechny sockety
		    for(i = fdMin; i <= fdMax; i++) {
		    	if (FD_ISSET(i, &read_fds)) { // Pokud je socket[i] čtecího typu
		    		if (i == listen_sock) { // Pokud je ten čtecí socket můj hlavní socket
		    			// Jsem připraven přijmout do své náruče dalšího klienta
		    		} else {
    					// Jsem připraven číst data od klienta
		    		}
		    	} else if (FD_ISSET(i, &write_fds)) {
		    		// Jsem připraven poslat data tomuto klientovi
		    	}
		    }
		}

//		if (acceptor->start() == 0) {
//			for(;;) {
//				TCPStream* stream = acceptor->accept();
//				if (stream != NULL) {
//					clients.push_back(stream);
//					size_t len;
//					char line[256];
//					while ((len = stream->receive(line, sizeof(line), 0)) > 0) {
//						line[len] = '\0';
//						std::cout << "Recieved: " << line << std::endl;
//					}
//					delete stream;
//				}
//			}
//		}

		perror("Could not start the server");
		exit(1);
	}

} // end namespace
