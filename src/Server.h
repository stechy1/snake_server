#ifndef SNAKE_SERVER
#define SNAKE_SERVER

#include "network/TCPStream.h"
#include "network/TCPConnection.h"
#include "World.h"
#include "DataParser.h"

#include <sys/select.h>
#include <vector>

namespace SnakeServer {

    // Struktura obsahující informaci o portu serveru a maximálním počtu hráčů
    struct ServerSettings {
        unsigned int port = 0;
        uint16_t maxPlayers = 10;
        unsigned int width = 600;
        unsigned int height = 600;
    }; // end struct

    class Server {
    public:
        Server();

        virtual ~Server();

        // Inicializační metoda, nastaví potřebné proměnné serveru
        void init(std::unique_ptr<ServerSettings> t_serverSettings);
        // Spuštění serveru
        void start();

    private:
        // Methods
        clientsMap_t *m_clients;

        std::unique_ptr<World> m_world;
        std::unique_ptr<ServerSettings> m_settings;
        std::unique_ptr<Network::TCPConnection> m_connection;
        std::shared_ptr<DataParser> m_dataParser;


    }; // end class

} // end namespace
#endif