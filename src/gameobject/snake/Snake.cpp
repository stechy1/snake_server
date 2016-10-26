#include <iostream>
#include "Snake.h"

namespace SnakeServer {
namespace GameObject {
namespace Snake {

Snake::Snake(int t_id, Vector2D &t_pos, Vector2D &t_dir)
        : BaseObject(t_pos, t_dir), m_id(t_id) {
    m_vel = Vector2D::ONES();
    m_vel *= VELOCITY_MULTIPLIER;
}

Snake::~Snake() {
    for(auto event : m_eventQueue) {
        delete event;
    }
}

void SnakeServer::GameObject::Snake::Snake::update(double t, double dt) {
    if (!m_eventQueue.empty()) {
        Event::BaseEvent *event = m_eventQueue.front();
        m_eventQueue.pop_front();
        event->applyChanged(*this);
        //m_worldBroadcaster.broadcastMessage(m_id, event->getData());
        delete event;
    }

    const Vector2D newPos(Vector2D::mul(m_dir, m_vel)*=SIZE);
    m_pos+=newPos;
}

void Snake::addEvent(Event::BaseEvent *event) {
    m_eventQueue.push_back(event);
}

std::string Snake::getDescription() {
    return "SnakeObject";
}

}
}
}

