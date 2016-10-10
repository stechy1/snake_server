#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "TCPAcceptor.h"
#include <iostream>

namespace SnakeServer {

	namespace Network {

		TCPAcceptor::TCPAcceptor(int port, unsigned int maxPlayers) 
	    : _lsd(0), _port(port), _listening(false), _maxClients(maxPlayers) {
	    	FD_ZERO(&_master_fds);
			FD_ZERO(&_read_fds);
			FD_ZERO(&_write_fds);

			_clients = new int[_maxClients];
			for (unsigned int i = 0; i < _maxClients; ++i) {
				*(_clients + i) = (int)ConnectionStatus::NOT_CONNECTED;
			}
	    }

		TCPAcceptor::~TCPAcceptor( void ) {
		    if (_lsd > 0) {
		        close(_lsd);
		    }

		    delete _clients;
		}

		bool TCPAcceptor::openPort( void ) {
			// Pokud už poslouchám, tak nic provádět nebudu
			if (_listening) {
				return false;
			}

			// Vytvoření nového socketu
			_lsd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (_lsd < 0) {
				perror("Socket()");
			}

			int optval = 1; // Nastavení socketu na neblokující
			if (ioctl(_lsd, FIONBIO, (char *)&optval) < 0) {
				close(_lsd);
				perror("ioctl nonblock");
				return false;
			}

			optval = 1;
			// Možnost permanentního znovupoužití stejného serveru
	    	setsockopt(_lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

			struct ::sockaddr_in address;
			memset(&address, 0, sizeof(address));
			address.sin_family = PF_INET;
			address.sin_port = htons(_port);
			address.sin_addr.s_addr = htonl(INADDR_ANY); // Poslouchám na jekémkoliv interfacu

	    	// Propojení adresy a socket descriptoru
	    	int result = bind(_lsd, (struct sockaddr*) &address, sizeof(address));
	    	if (result < 0) {
	    		perror("bind() failed");
	    		return false;
	    	}

	    	result = listen(_lsd, BACKLOG);
	    	if (result < 0) {
	    		perror("listen() failed");
	    		return false;
	    	}

	    	FD_SET(_lsd, &_master_fds);
			_fdMax = _lsd; // Nastavení maximální ho offsetu socketů
			_fdMin = _lsd; // Nastavení minimálního offsetu socketů

	    	_listening = true;
	    	return true;
		}

		void TCPAcceptor::start( void ) {
			for(;;) {
				// Zkopírování hlavního seznamu do čtecího a zapisovacího
			    memcpy(&_read_fds, &_master_fds, sizeof(_master_fds));
			    memcpy(&_write_fds, &_master_fds, sizeof(_master_fds));

			    std::cout << "Smyčka" << std::endl;

			    if (select(_fdMax + 1, &_read_fds, &_write_fds, NULL, NULL) == -1) {
			    	close(_lsd);
			    	perror("Chyba v selectu");
			    	exit(1);
			    }

			    std::cout << "Select is OK" << std::endl;

			    // Proiteruj všechny sockety
			    for(int i = _fdMin; i <= _fdMax; i++) {
			    	if (FD_ISSET(i, &_read_fds)) { // Pokud je socket[i] čtecího typu
			    		if (i == _lsd) { // Pokud je ten čtecí socket můj hlavní socket
			    			// Jsem připraven přijmout do své náruče nového klienta
			    			std::cout << "Jsem připraven přijmout do své náruče nového klienta." << std::endl;
			    			TCPStream *client = this->accept();
			    			if (client != NULL) {
			    				std::cout << "Přijal jsem nového klienta" << std::endl;
			    				delete client;
			    			}
			    			break;
			    		} else {
	    					// Jsem připraven číst data od klienta
	    					std::cout << "Jsem připraven číst data od klienta" << std::endl;
	    					break;
			    		}
			    	} else if (FD_ISSET(i, &_write_fds)) {
			    		// Jsem připraven poslat data tomuto klientovi
			    		std::cout << "Jsem připraven poslat data klientovi" << std::endl;
			    		break;
			    	}
			    }
			    std::cout << "Cycle" << std::endl;
			    exit(1);
			}
		}

		TCPStream* TCPAcceptor::accept( void ) {
		    if (!_listening) {
		        return NULL;
		    }

		    struct sockaddr_in address;
		    socklen_t len = sizeof(address);

		    memset(&address, 0, sizeof(address));
		    int sd = ::accept(_lsd, (struct sockaddr*)&address, &len);
		    if (sd < 0) {
		        perror("accept() failed");
		        return NULL;
		    }


		    
		    return new TCPStream(sd, &address);
		}

	} // end namespace Network

} // end namespace SnakeServer