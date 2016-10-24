#include "Server.h"

namespace SnakeServer {

Server::Server(ServerSettings &t_settings) : m_settings(t_settings) {
    const unsigned long worldCount = m_settings.world_count;
    const unsigned int width = m_settings.width;
    const unsigned int height = m_settings.height;

    m_worlds.resize(worldCount);
    for (int i = 0; i < worldCount; ++i) {
        m_worlds.push_back(new World(width, height));
    }
}

Server::~Server() {
    for (int i = 0; i < m_settings.world_count; ++i) {
        delete(m_worlds[i]);
    }
}


}