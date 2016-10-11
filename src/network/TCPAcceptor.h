#ifndef SNAKE_NETWORK_TCPACCEPTOR
#define SNAKE_NETWORK_TCPACCEPTOR

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "TCPStream.h"
 
using namespace std;

namespace SnakeServer {
	
	namespace Network {

		class TCPAcceptor {

			enum class ConnectionStatus	{
				NOT_CONNECTED = -1, CONNECTED = 0, LOST_CONNECTION = 1
			};

			static const unsigned int BACKLOG = 10; // Počet uživatelů maximálně čekajících na obsloužení
			int    _lsd;        // Listenning socket descriptor
			int    _port;       // Port peeru
			bool   _listening;  // True, pokud poslouchám, jinak false
			unsigned int    _maxClients; // Maximální počet připojitelných klientů

			fd_set _master_fsd; // Master file descriptor list
			fd_set _read_fsd;   // File descriptor list for read events
			fd_set _write_fsd;  // File descriptor list for write events

			int _fdMax = 0;     // Nejmenší index socket file descriptoru
			int _fdMin = 0;     // Největší index socket file descriptoru

			TCPStream *_clients;      // Klienti

			public:
				TCPAcceptor(int, unsigned int);
				~TCPAcceptor();

				bool openPort();     // Pokusí se otevřít naslouchací port
				void start();        // Spustí komunikační proces s příchozími klienty

			protected:
				TCPStream* accept(); // Vytvoří nový TCP stream s klientem

			private:
				TCPAcceptor();
				TCPAcceptor(const TCPAcceptor& acceptor);
		}; // end class

	} // end namespace Network

}// end namespace SnakeServer

#endif