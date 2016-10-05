#ifndef SNAKE_SERVER
#define SNAKE_SERVER

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


	}; // end class

} // end namespace
#endif