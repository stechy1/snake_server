#ifndef SNAKE_SERVER_CLIENT_H
#define SNAKE_SERVER_CLIENT_H

#include <memory>
#include <list>
#include <map>
#include "network/TCPStream.h"
#include "gameobject/snake/Snake.h"

namespace SnakeServer {

    typedef std::shared_ptr<std::list<std::string>> cache_list;

    struct Client {
        std::shared_ptr<Network::TCPStream> stream;
        std::shared_ptr<GameObject::Snake::Snake> snake;
        cache_list cache = std::make_shared<std::list<std::string>>();
        bool ready = false;
    };

    typedef std::map<int, std::shared_ptr<Client>> clientsMap_t;

}

#endif //SNAKE_SERVER_CLIENT_H
