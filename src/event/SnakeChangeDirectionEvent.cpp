#include <iostream>
#include "SnakeChangeDirectionEvent.h"
#include "../gameobject/snake/Snake.h"

namespace SnakeServer {
namespace Event {

SnakeChangeDirectionEvent::SnakeChangeDirectionEvent(int t_userID, Vector2D &t_direction)
        : m_userID(t_userID), m_direction(t_direction) {}

std::string SnakeChangeDirectionEvent::getDescription() {
    return "SnakeChangeDirectionEvent";
}

std::string SnakeChangeDirectionEvent::getData() {
    return "";
}

void SnakeChangeDirectionEvent::applyChanged(IUpdatable &updatable) {
    SnakeServer::GameObject::Snake::Snake &snake = static_cast<SnakeServer::GameObject::Snake::Snake&>(updatable);

    std::cout << "Aplikuji změny v ChangeDirectionEventu" << std::endl;
    snake.m_dir.set(m_direction);
}

EventType SnakeChangeDirectionEvent::getEventType() {
    return EventType::GAME_OBJECT;
}

int SnakeChangeDirectionEvent::getUserID() {
    return m_userID;
}

}
}
