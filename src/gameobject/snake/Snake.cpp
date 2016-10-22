#include <iostream>
#include "Snake.h"

namespace SnakeServer {
namespace GameObject {
namespace Snake {

Snake::Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir)
        : BaseObject(std::move(t_pos), std::move(t_dir)) {
    *m_vel*=VELOCITY_MULTIPLIER;
}

Snake::Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir, std::unique_ptr<Vector2D> t_vel)
        : BaseObject(std::move(t_pos), std::move(t_dir), std::move(t_vel)) {
    *m_vel*=VELOCITY_MULTIPLIER;
}

void SnakeServer::GameObject::Snake::Snake::update(double t, double dt) {
    std::cout << "Aktualizace stavu hada" << std::endl;

    if (!m_eventQueue.empty()) {
        const std::shared_ptr<Event::BaseEvent> event = m_eventQueue.front();
        m_eventQueue.pop_front();
        event->applyChanged(*this);
    }

    const Vector2D newPos(Vector2D::mul(*m_dir, *m_vel)*=SIZE);
    *m_pos+=newPos;

    std::cout << "Position: " << m_pos->to_string() << std::endl;
}

void Snake::addEvent(std::shared_ptr<Event::BaseEvent> event) {
    m_eventQueue.push_back(event);
}

std::string Snake::getDescription() {
    return "SnakeObject";
}

}
}
}

