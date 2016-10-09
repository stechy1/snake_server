#ifndef SNAKE_SERVER
#define SNAKE_SERVER

#include "network/TCPStream.h"
#include "network/TCPAcceptor.h"

#include <sys/select.h>
#include <vector>

namespace SnakeServer {

	// Struktura obsahující informaci o portu serveru a maximálním počtu hráčů
	struct ServerSettings
	{
		unsigned int port;
		unsigned int maxPlayers;
	}; // end struct

	enum class ConnectionStatus	{
		NOT_CONNECTED = -1, CONNECTED = 0, LOST_CONNECTION = 1
	};

	class Server {

		unsigned int _port;
		unsigned int _maxPlayers;

		fd_set _master_fds; // Master file descriptor list
		fd_set _read_fds;   // File descriptor list for read events
		fd_set _write_fds;  // File descriptor list for write events

		int _fdMax = 0; // Nejmenší index socket file descriptoru
		int _fdMin = 0; // Největší index socket file descriptoru
		// Klienti
		int *_clients;
		//std::vector<Network::TCPStream*> _clients;

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
			void acceptClient(Network::TCPAcceptor*);


	}; // end class

} // end namespace
#endif