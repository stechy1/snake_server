#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include "TCPConnection.h"
#include <iostream>

namespace SnakeServer {

    namespace Network {

        TCPConnection::TCPConnection(clientsMap_t *t_clients, const unsigned int t_port, std::shared_ptr<IOHandler> t_ioHandler)
                : m_clients(t_clients), m_lsd(0), m_port(t_port), m_listening(false), m_ioHandler(t_ioHandler) {
            FD_ZERO(&m_master_read_fds);
            FD_ZERO(&m_master_write_fds);
            FD_ZERO(&m_read_fds);
            FD_ZERO(&m_write_fds);

            std::cout << "TCPConnection initialized: " << m_port << std::endl;
        }

        TCPConnection::~TCPConnection() {
            if (m_lsd > 0) {
                close(m_lsd);
            }
        }

        bool TCPConnection::openPort() {
            // Pokud už poslouchám, tak nic provádět nebudu
            if (m_listening) {
                return false;
            }

            // Vytvoření nového socketu
            m_lsd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (m_lsd < 0) {
                perror("Socket()");
                return false;
            }

            int optval = 1; // Nastavení socketu na neblokující
            if (ioctl(m_lsd, FIONBIO, (char *) &optval) < 0) {
                close(m_lsd);
                perror("ioctl nonblock");
                return false;
            }

            optval = 1;
            // Možnost permanentního znovupoužití stejného serveru
            setsockopt(m_lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

            struct ::sockaddr_in address;
            memset(&address, 0, sizeof(address));
            address.sin_family = PF_INET;
            address.sin_port = htons(m_port);
            address.sin_addr.s_addr = htonl(INADDR_ANY); // Poslouchám na jekémkoliv interfacu

            // Propojení adresy a socket descriptoru
            int result = bind(m_lsd, (struct sockaddr *) &address, sizeof(address));
            if (result < 0) {
                perror("bind() failed");
                return false;
            }

            result = listen(m_lsd, BACKLOG);
            if (result < 0) {
                perror("listen() failed");
                return false;
            }

            FD_SET(m_lsd, &m_master_read_fds);
            m_fdMax = m_lsd; // Nastavení maximální ho offsetu socketů
            m_fdMin = m_lsd; // Nastavení minimálního offsetu socketů

            m_listening = true;
            return true;
        }

        std::thread TCPConnection::start() {
            std::cout << "TCPService running..." << std::endl;
            return std::thread(&TCPConnection::run, this);
        }

        void TCPConnection::shutDown() {
            interupt = true;
        }

        void TCPConnection::run() {
            while(!interupt) {
                // Zkopírování seznamů
                memcpy(&m_read_fds, &m_master_read_fds, sizeof(m_master_read_fds));
                memcpy(&m_write_fds, &m_master_write_fds, sizeof(m_master_write_fds));

                if (select(m_fdMax + 1, &m_read_fds, &m_write_fds, NULL, NULL) == -1) {
                    close(m_lsd);
                    perror("Chyba v selectu");
                    exit(1);
                }

                // Proiteruj všechny sockety
                for (int i = m_fdMin; i <= m_fdMax; i++) {
                    if (FD_ISSET(i, &m_read_fds)) { // Pokud je socket[i] čtecího typu
                        if (i == m_lsd) { // Pokud je ten čtecí socket můj hlavní socket
                            // Jsem připraven přijmout do své náruče nového klienta
                            //std::cout << "Jsem připraven přijmout do své náruče nového klienta." << std::endl;
                            try {
                                this->accept();
                                std::cout << "Vytvorilo se nove spojeni s klientem: " << i << std::endl;
                                //m_dataParser->onClientConnected(i);
                            } catch (std::exception e) {
                                std::cout << "Vyskytla se chyba s připojením uživatele" << std::endl;
                            }
                        } else {
                            // Jsem připraven číst data od klienta
                            //std::cout << "Jsem připraven číst data od klienta" << std::endl;
                            try {
                                //auto data = m_clients[i]->receive();
                                auto data = (*m_clients)[i]->stream->receive();
                                if (data != "") {
                                    //std::cout << "Received: " << data  << std::endl;
                                    m_ioHandler->onReceived(i, data);
                                }

                            } catch (std::runtime_error ex) {
                                std::cout << "Chyba při přijímání dat od klienta" << std::endl;
                            }
                        }
                    }
                    if (FD_ISSET(i, &m_write_fds)) {
                        // Jsem připraven poslat data tomuto klientovi
                        //std::cout << "Jsem připraven poslat data klientovi" << std::endl;
                        (*m_clients)[i]->stream->send();
                    }
                }
            }
        }

        void TCPConnection::accept() {
            if (!m_listening) {
                return;
            }

            struct sockaddr_in address;
            socklen_t len = sizeof(address);

            memset(&address, 0, sizeof(address));
            int sd = ::accept(m_lsd, (struct sockaddr *) &address, &len);
            if (sd < 0) {
                perror("accept() failed");
                throw std::runtime_error("sdfsdf");
            }

            (*m_clients)[sd] = std::make_shared<Client>();
            (*m_clients)[sd]->stream = std::make_unique<TCPStream>(sd, &address);

            FD_SET(sd, &m_master_read_fds);

            if (sd > m_fdMax) m_fdMax = sd;
            if (sd < m_fdMin) m_fdMin = sd;
        }

    } // end namespace Network

} // end namespace SnakeServer