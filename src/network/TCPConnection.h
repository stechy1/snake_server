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
#include <thread>
#include "TCPStream.h"
#include "../Client.h"

namespace SnakeServer {

    namespace Network {

        class IOHandler;
        class TCPConnection {

            enum class ConnectionStatus {
                NOT_CONNECTED = -1, CONNECTED = 0, LOST_CONNECTION = 1
            };

            clientsMap_t m_clients;

            static const unsigned int BACKLOG = 10; // Počet uživatelů maximálně čekajících na obsloužení
            int m_lsd = -1;                // Listenning socket descriptor
            unsigned int m_port = 0;                // Port peeru
            bool m_listening = false;      // True, pokud poslouchám, jinak false
            unsigned int m_maxClients = 0; // Maximální počet připojitelných klientů

            fd_set m_master_read_fds;  // Master file descriptor list for read events
            fd_set m_master_write_fds; // Master file descriptor list for write events
            fd_set m_read_fds;         // File descriptor list for read events
            fd_set m_write_fds;        // File descriptor list for write events

            int m_fdMax = 0;     // Nejmenší index socket file descriptoru
            int m_fdMin = 0;     // Největší index socket file descriptoru


            //std::map<int, std::unique_ptr<TCPStream>> m_clients; // Mapa klientů, kde klíč = fds; value = TCPStream

            std::unique_ptr<IOHandler> m_ioHandler;

            bool interupt = false;

        public:
            TCPConnection(clientsMap_t &t_clients, const unsigned int t_port,
                        std::unique_ptr<IOHandler> t_ioHandler); // Konstruktor s portem jako parametr

            ~TCPConnection();

            bool openPort();     // Pokusí se otevřít naslouchací port
            void start();        // Spustí nové vlákno
            void shutDown();     // Ukončí vlákno

        protected:
            void accept(); // Vytvoří nový TCP stream s klientem
            void run();        // Spustí komunikační proces s příchozími klienty

        private:
            //TCPConnection();

            TCPConnection(const TCPConnection &acceptor);
        };

        class IOHandler {
        public:
            virtual void onReceived(int clientID, std::string data) = 0;

            virtual ~IOHandler() {}
        };
        // end class

    } // end namespace Network

}// end namespace SnakeServer

#endif