#include <string>
#include <netinet/in.h>
#include "tcpstream.h"
 
using namespace std;

namespace SnakeServer::Network {

	class TCPAcceptor {
		static const unsigned int BACKLOG = 10; // Počet uživatelů maximálně čekajících na obsloužení
		int    m_lsd;       // Listenning socket descriptor
		string m_address;   // Adresa peeru
		int    m_port;      // Port peeru
		bool   m_listening; // True, pokud poslouchám, jinak false

		public:
			TCPAcceptor(int port, const char* address="");
			~TCPAcceptor();

			int        start();
			TCPStream* accept();

		private:
			TCPAcceptor() {}
	}; // end class

}// end namespace