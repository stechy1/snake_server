#ifndef SNAKE_SERVER
#define SNAKE_SERVER

#include "network/TCPStream.h"
#include "network/TCPAcceptor.h"
#include "World.h"

#include <sys/select.h>
#include <vector>

namespace SnakeServer {

    // Struktura obsahující informaci o portu serveru a maximálním počtu hráčů
    struct ServerSettings {
        unsigned int port;
        unsigned int maxPlayers;
    }; // end struct

    class Server {

        unsigned int _port;
        unsigned int _maxPlayers;

        World world;

    public:
        // Variables
        // Inicializační metoda, nastaví potřebné proměnné serveru
        virtual void init(const ServerSettings serverSettings);

        // Spuštění serveru
        virtual void start();
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