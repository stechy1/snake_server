#include <iostream>
#include "LoginEvent.h"
#include "../gameobject/snake/Snake.h"

namespace SnakeServer {
namespace Event {

LoginEvent::LoginEvent(int t_userID, std::string t_username) : m_userID(t_userID), m_username(t_username) {}

std::string LoginEvent::getDescription() {
    return "Login event";
}

std::string LoginEvent::getData() {
    return "";
}

void LoginEvent::applyChanged(IUpdatable &updatable) {
    SnakeServer::GameObject::Snake::Snake &snake = static_cast<SnakeServer::GameObject::Snake::Snake&>(updatable);

    std::cout << "Aplikuji změny v LoginEventu" << std::endl;
}

}
}
