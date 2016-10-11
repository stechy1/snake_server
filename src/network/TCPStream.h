#ifndef SNAKE_TCPSTREAM
#define SNAKE_TCPSTREAM

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
 
using namespace std;

namespace SnakeServer {
	
	namespace Network {

		class TCPStream {
			int     _sd;        // Socket file discriptor
			string  _peerIP;    // IP adresa peeru
			int     _peerPort;  // Port peeru

			public:
				friend class TCPAcceptor;  // Přiřazení "přátelské" třídy pro přístup k privátnímu konstruktoru
				friend class TCPConnector; // Přiřazení "přátelské" třídy pro přístup k privátnímu konstruktoru

				virtual ~TCPStream();

				// Odešle zadaný buffer do internetu
				ssize_t send(char* buffer, size_t len);
				// Přijme data z internetu
				ssize_t receive(char* buffer, size_t len);

				// Getter pro IP adresu peeru
				string getPeerIP();
				// Getter pro Port peeru
				int getPeerPort();

				enum {
			        connectionClosed = 0,
			        connectionReset = -1,
			        connectionTimedOut = -2
				};

			private:
				// sd - Socket descriptor; address - reference na strukturu sockaddr_in
				TCPStream(int sd, struct sockaddr_in* address); // Jediný používaný konstruktor
				TCPStream(); // Prázdný konstruktor
				TCPStream(const TCPStream& stream); // Copy konstructor

				bool waitForReadEvent(int timeout);
		}; // end class

	} // end namespace Network

} // end namespace SnakeServer

#endif