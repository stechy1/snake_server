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

	Server::Server(void) {
		std::cout << "Konstruktor serveru" << std::endl;

		FD_ZERO(&_master_fds);
		FD_ZERO(&_read_fds);
		FD_ZERO(&_write_fds);
	}

	Server::~Server(void) {
		delete _clients;
	}

	void Server::init(ServerSettings serverSettings) {
		_port = serverSettings.port;
		_maxPlayers = serverSettings.maxPlayers;

		_clients = new int[_maxPlayers];
		for (unsigned int i = 0; i < _maxPlayers; ++i) {

			*(_clients + i) = static_cast<std::underlying_type<ConnectionStatus>::type>(ConnectionStatus::NOT_CONNECTED);
		}
	}

	void Server::acceptClient(TCPAcceptor *acceptor) {
		int incoming_sock;                 // Socket descriptor pro příchozí socket
		//struct sockaddr_in incoming_addr;  // Adresa příchozího socketu
		//unsigned int incoming_addr_len;    // Délka adresy

		for(;;) {
			TCPStream* stream = acceptor->accept();
			if (stream == NULL)
				break;

			incoming_sock = stream->getSocketDescriptor();

			_clients[incoming_sock] = static_cast<std::underlying_type<ConnectionStatus>::type>(ConnectionStatus::CONNECTED);

			FD_SET(incoming_sock, &_master_fds);

			if (incoming_sock > _fdMax) _fdMax = incoming_sock;
			if (incoming_sock < _fdMin) _fdMin = incoming_sock;
		}
		// for(;;) {
		// 	incoming_addr_len = sizeof(incoming_addr);
		// 	incoming_sock = ::accept(_listen_socket, (struct sockaddr*)&incoming_addr, &incoming_addr_len);

		// 	if (incoming_sock < 0) {
		// 		if (errno != EWOULDBLOCK) {
		// 			close(_listen_socket);
		// 			perror("Chyba při přijení nového klienta");
		// 			exit(1);
		// 		}
		// 		break;
		// 	}
		// }
	}

	void Server::start( void ) {
		int i = 0;
		//TCPStream*   stream = NULL;
		TCPAcceptor* acceptor = NULL;

		std::cout << "Server started" << std::endl;

		acceptor = new TCPAcceptor(_port);

		int _listen_socket = acceptor->start();
		if (_listen_socket < 0) {
			perror("Failed to create listen sock");
			exit(1);
		}

		// Přidání server listeneru do seznamu "master_fsd"
		FD_SET(_listen_socket, &_master_fds);
		_fdMax = _listen_socket; // Nastavení maximální ho offsetu socketů
		_fdMin = _listen_socket; // Nastavení minimálního offsetu socketů

		for(;;) {
			// Zkopírování hlavního seznamu do čtecího a zapisovacího
		    memcpy(&_read_fds, &_master_fds, sizeof(_master_fds));
		    memcpy(&_write_fds, &_master_fds, sizeof(_master_fds));

		    // Čekám na jakoukoliv akci
		    if (select(_fdMax + 1, &_read_fds, &_write_fds, NULL, NULL) == -1) {
		    	close(_listen_socket);
		    	perror("Chyba v selectu");
		    	exit(1);
		    }

		    // Proiteruj všechny sockety
		    for(i = _fdMin; i <= _fdMax; i++) {
		    	if (FD_ISSET(i, &_read_fds)) { // Pokud je socket[i] čtecího typu
		    		if (i == _listen_socket) { // Pokud je ten čtecí socket můj hlavní socket
		    			// Jsem připraven přijmout do své náruče nového klienta
		    			this->acceptClient(acceptor);
		    		} else {
    					// Jsem připraven číst data od klienta
    					std::cout << "Jsem připraven číst data od klienta" << std::endl;
		    		}
		    	} else if (FD_ISSET(i, &_write_fds)) {
		    		// Jsem připraven poslat data tomuto klientovi
		    		std::cout << "Jsem připraven poslat data klientovi" << std::endl;
		    	}
		    }
		}

//		if (acceptor->start() == 0) {
//			for(;;) {
//				TCPStream* stream = acceptor->accept();
//				if (stream != NULL) {
//					_clients.push_back(stream);
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
