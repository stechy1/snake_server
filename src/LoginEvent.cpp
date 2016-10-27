#include <iostream>
#include "LoginEvent.h"
#include "Snake.h"
#include "World.h"

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
    SnakeServer::World &world = static_cast<SnakeServer::World&>(updatable);
    world.addSnake(m_userID);
}

EventType LoginEvent::getEventType() {
    return EventType::WORLD;
}

int LoginEvent::getUserID() {
    return m_userID;
}

}
}
