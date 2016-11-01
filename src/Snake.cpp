#include <iostream>
#include "Snake.h"

namespace SnakeServer {
namespace GameObject {

Snake::Snake(Vector2D &t_pos, Vector2D &t_dir)
        : m_pos(t_pos), m_dir(t_dir) {
    m_vel = Vector2D::ONES();
    m_vel *= VELOCITY_MULTIPLIER;
}


void Snake::addEvent(std::unique_ptr<Event::BaseEvent>&& event) {
    m_eventQueue.push_back(std::move(event));
}

std::unique_ptr<Event::BaseEvent> Snake::applyEvent() {
    if (m_eventQueue.empty()) {
        return nullptr;
    }

    auto event = std::move(m_eventQueue.front());
    m_eventQueue.pop_front();
    event->applyChanged(*this);
    return std::move(event);
}

std::string Snake::getDescription() {
    return "SnakeObject";
}

}
}

