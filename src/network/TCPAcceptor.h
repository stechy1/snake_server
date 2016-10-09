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
			static const unsigned int BACKLOG = 10; // Počet uživatelů maximálně čekajících na obsloužení
			int    m_lsd;       // Listenning socket descriptor
			int    m_port;      // Port peeru
			bool   m_listening; // True, pokud poslouchám, jinak false

			public:
				TCPAcceptor(int port);
				~TCPAcceptor();

				int start();
				TCPStream* accept();

				int getMySocketDescriptor();

			private:
				TCPAcceptor();
				TCPAcceptor(const TCPAcceptor& acceptor);
		}; // end class

	} // end namespace Network

}// end namespace SnakeServer

#endif