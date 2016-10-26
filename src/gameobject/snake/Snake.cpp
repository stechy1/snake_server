#include <iostream>
#include "Snake.h"

namespace SnakeServer {
namespace GameObject {
namespace Snake {

Snake::Snake() {}

Snake::Snake(Vector2D &t_pos) : BaseObject(t_pos) {}

Snake::Snake(Vector2D &t_pos, Vector2D &t_dir) : BaseObject(t_pos, t_dir) {}

Snake::Snake(Vector2D &t_pos, Vector2D &t_dir, Vector2D &t_vel) : BaseObject(t_pos, t_dir, t_vel) {}

Snake::~Snake() {}

void SnakeServer::GameObject::Snake::Snake::update(double t, double dt) {
    std::cout << "Aktualizace stavu hada" << std::endl;

    if (!m_eventQueue.empty()) {
        Event::BaseEvent *event = m_eventQueue.front();
        m_eventQueue.pop_front();
        event->applyChanged(*this);
        delete event;
    }

    const Vector2D newPos(Vector2D::mul(m_dir, m_vel)*=SIZE);
    m_pos+=newPos;

    std::cout << "Position: " << m_pos.to_string() << std::endl;
}

void Snake::addEvent(Event::BaseEvent &event) {
    m_eventQueue.push_back(&event);
}

std::string Snake::getDescription() {
    return "SnakeObject";
}

}
}
}

