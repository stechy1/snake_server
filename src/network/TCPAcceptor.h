#ifndef SNAKE_NETWORK_TCPACCEPTOR
#define SNAKE_NETWORK_TCPACCEPTOR

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/select.h>
#include <memory>
#include <map>
#include "TCPStream.h"

namespace SnakeServer {

    namespace Network {

        class TCPAcceptor {

            enum class ConnectionStatus {
                NOT_CONNECTED = -1, CONNECTED = 0, LOST_CONNECTION = 1
            };

            static const unsigned int BACKLOG = 10; // Počet uživatelů maximálně čekajících na obsloužení
            int m_lsd = -1;                // Listenning socket descriptor
            int m_port = 0;                // Port peeru
            bool m_listening = false;      // True, pokud poslouchám, jinak false
            unsigned int m_maxClients = 0; // Maximální počet připojitelných klientů

            fd_set m_master_read_fds;  // Master file descriptor list for read events
            fd_set m_master_write_fds; // Master file descriptor list for write events
            fd_set m_read_fds;         // File descriptor list for read events
            fd_set m_write_fds;        // File descriptor list for write events

            int m_fdMax = 0;     // Nejmenší index socket file descriptoru
            int m_fdMin = 0;     // Největší index socket file descriptoru

            std::map<int, std::unique_ptr<TCPStream>> m_clients; // Mapa klientů, kde klíč = fds; value = TCPStream

        public:
            TCPAcceptor(int t_port); // Konstruktor s portem jako parametr

            ~TCPAcceptor();

            bool openPort();     // Pokusí se otevřít naslouchací port
            void start();        // Spustí komunikační proces s příchozími klienty

        protected:
            void accept(); // Vytvoří nový TCP stream s klientem

        private:
            //TCPAcceptor();

            TCPAcceptor(const TCPAcceptor &acceptor);
        };
        // end class

    } // end namespace Network

}// end namespace SnakeServer

#endif