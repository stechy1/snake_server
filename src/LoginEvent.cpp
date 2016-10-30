#include <iostream>
#include "LoginEvent.h"
#include "Snake.h"
#include "World.h"
#include "InitEvent.h"

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
    try {
        GameObject::Snake *snake = world.addSnake(m_userID);

        Event::InitEvent event(m_userID, *snake, world.m_width, world.m_height, world.m_snakesOnMap, world.m_foodOnMap);
        world.sendMessage(m_userID, event.getData());
        world.wakeUp();
    } catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
}

EventType LoginEvent::getEventType() {
    return EventType::WORLD;
}

int LoginEvent::getUserID() {
    return m_userID;
}

}
}
