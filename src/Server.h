#ifndef SNAKE_SERVER_SERVER_H
#define SNAKE_SERVER_SERVER_H

#include "World.h"

namespace SnakeServer {

class ServerSettings {
public:
    ServerSettings() {}
    ~ServerSettings() {}

    unsigned int world_count;
    unsigned int port;
    unsigned int width;
    unsigned int height;
    unsigned int players_per_server;

};

class Server {
public:
    Server(ServerSettings &settings);
    ~Server();

private:
    ServerSettings &m_settings;

    std::vector<World*> m_worlds;
};

}

#endif //SNAKE_SERVER_SERVER_H
