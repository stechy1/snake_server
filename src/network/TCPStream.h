#ifndef SNAKE_TCPSTREAM
#define SNAKE_TCPSTREAM

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
 
using namespace std

namespace SnakeServer::Network {

	class TCPStream {
		int     m_sd;        // Identifikátor, zda-li se jedná o clienta, nebo o server
		string  m_peerIP;    // IP adresa peeru
		int     m_peerPort;  // Port peeru

		public:
			friend class TCPAcceptor;  // Přiřazení "přátelské" třídy pro přístup k privátnímu konstruktoru
			friend class TCPConnector; // Přiřazení "přátelské" třídy pro přístup k privátnímu konstruktoru

			~TCPStream();

			// Odešle zadaný buffer do internetu
			ssize_t send(char* buffer, size_t len);
			// Přijme data z internetu
			ssize_t receive(char* buffer, size_t len);

			// Getter pro IP adresu peeru
			string getPeerIP( void );
			// Getter pro Port peeru
			int getPeerPort( void );

		private:
			// sd - Socket descriptor; address - reference na strukturu sockaddr_in
			TCPStream(int sd, struct sockaddr_in* address); // Jediný používaný konstruktor
			TCPStream(); // Prázdný konstruktor
			TCPStream(const TCPStream& stream); // Copy konstructor
	}; // end class

} // end namespace

#endif