#ifndef SNAKE_SERVER
#define SNAKE_SERVER

#include "network/TCPStream.h"

#include <sys/select.h>
#include <vector>

namespace SnakeServer {

	// Struktura obsahující informaci o portu serveru a maximálním počtu hráčů
	struct ServerSettings
	{
		unsigned int port;
		unsigned int maxPlayers;
	}; // end struct

	class Server {

		unsigned int _port;
		unsigned int _maxPlayers;
		//World world;

		public:
			// Variables
			// Inicializační metoda, nastaví potřebné proměnné serveru
			virtual void init( ServerSettings serverSettings );
			// Spuštění serveru
			virtual void start( void );
			// Methods

			Server();
			virtual ~Server();


		protected:
			// Variables

			// Methods


		private:
			// Methods
			fd_set master_fds; /* master file descriptor list */
			fd_set read_fds; /* temp file descriptor list for read events */
			fd_set write_fds; /* temp file descriptor list for write events */

			int fdMax = 0; // Nejmenší index socket file descriptoru
			int fdMin = 0; // Největší index socket file descriptoru
			// Klienti
			std::vector<Network::TCPStream*> clients;


	}; // end class

} // end namespace
#endif