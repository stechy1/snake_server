#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "TCPAcceptor.h"
#include <iostream>

namespace SnakeServer {

    namespace Network {

        TCPAcceptor::TCPAcceptor(int port, unsigned int maxPlayers)
                : _lsd(0), _port(port), _listening(false), _maxClients(maxPlayers) {
            FD_ZERO(&_master_fsd);
            FD_ZERO(&_read_fsd);
            FD_ZERO(&_write_fsd);

            std::cout << "Konstruktor TCPAcceptor. " << _maxClients << std::endl;
            _clients = new TCPStream[_maxClients];
            //memset(_clients, 0, sizeof(TCPStream));
            // for (unsigned int i = 0; i < _maxClients; ++i) {
            // 	*(_clients + i) = (int)ConnectionStatus::NOT_CONNECTED;
            // }
        }

        TCPAcceptor::~TCPAcceptor() {
            if (_lsd > 0) {
                close(_lsd);
            }
            for (unsigned int i = 0; i < _maxClients; ++i) {
                //if (*(_clients + i) != NULL) {
                delete (_clients + i);
                //}
            }

            delete _clients;
        }

        bool TCPAcceptor::openPort() {
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
            // if (ioctl(_lsd, FIONBIO, (char *)&optval) < 0) {
            // 	close(_lsd);
            // 	perror("ioctl nonblock");
            // 	return false;
            // }

            optval = 1;
            // Možnost permanentního znovupoužití stejného serveru
            setsockopt(_lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

            struct ::sockaddr_in address;
            memset(&address, 0, sizeof(address));
            address.sin_family = PF_INET;
            address.sin_port = htons(_port);
            address.sin_addr.s_addr = htonl(INADDR_ANY); // Poslouchám na jekémkoliv interfacu

            // Propojení adresy a socket descriptoru
            int result = bind(_lsd, (struct sockaddr *) &address, sizeof(address));
            if (result < 0) {
                perror("bind() failed");
                return false;
            }

            result = listen(_lsd, BACKLOG);
            if (result < 0) {
                perror("listen() failed");
                return false;
            }

            FD_SET(_lsd, &_master_fsd);
            _fdMax = _lsd; // Nastavení maximální ho offsetu socketů
            _fdMin = _lsd; // Nastavení minimálního offsetu socketů

            _listening = true;
            return true;
        }

        void TCPAcceptor::start() {
            char buffer[1];
            for (;;) {
                // Zkopírování hlavního seznamu do čtecího a zapisovacího
                memcpy(&_read_fsd, &_master_fsd, sizeof(_master_fsd));
                memcpy(&_write_fsd, &_master_fsd, sizeof(_master_fsd));

                std::cout << "Smyčka" << std::endl;

                if (select(_fdMax + 1, &_read_fsd, &_write_fsd, NULL, NULL) == -1) {
                    close(_lsd);
                    perror("Chyba v selectu");
                    exit(1);
                }

                std::cout << "Select is OK" << std::endl;

                // Proiteruj všechny sockety
                for (int i = _fdMin; i <= _fdMax; i++) {
                    if (FD_ISSET(i, &_read_fsd)) { // Pokud je socket[i] čtecího typu
                        if (i == _lsd) { // Pokud je ten čtecí socket můj hlavní socket
                            // Jsem připraven přijmout do své náruče nového klienta
                            std::cout << "Jsem připraven přijmout do své náruče nového klienta." << std::endl;
                            TCPStream *client = this->accept();
                            if (client != NULL) {
                                std::cout << "Přijal jsem nového klienta" << std::endl;
                                //delete client;
                            }
                            break;
                        } else {
                            // Jsem připraven číst data od klienta
                            std::cout << "Jsem připraven číst data od klienta" << std::endl;
                            TCPStream *client = (_clients + i);

                            client->receive(buffer, 4096);
                            // if (received == -1) {
                            // 	perror("error receive()");
                            // 	exit(1);
                            // }

                            // std::cout << "Received: " << buffer << "; bytes received: " << received << std::endl;

                            break;
                        }
                    }
                    if (FD_ISSET(i, &_write_fsd)) {
                        // Jsem připraven poslat data tomuto klientovi
                        //std::cout << "Jsem připraven poslat data klientovi" << std::endl;
                        break;
                    }
                }
                //std::cout << "Cycle" << std::endl;
                //exit(1);
            }
        }

        TCPStream *TCPAcceptor::accept() {
            if (!_listening) {
                return NULL;
            }

            struct sockaddr_in address;
            socklen_t len = sizeof(address);

            memset(&address, 0, sizeof(address));
            int sd = ::accept(_lsd, (struct sockaddr *) &address, &len);
            if (sd < 0) {
                perror("accept() failed");
                return NULL;
            }

            TCPStream *client = new TCPStream(sd, &address);
            _clients[sd] = *client;
            FD_SET(sd, &_master_fsd);

            if (sd > _fdMax) _fdMax = sd;
            if (sd < _fdMin) _fdMin = sd;

            return client;
        }

    } // end namespace Network

} // end namespace SnakeServer