#ifndef SNAKE_SERVER_SNAKE_H
#define SNAKE_SERVER_SNAKE_H

#include <list>
#include "BaseEvent.h"
#include "IUpdatable.h"
#include "Vector2D.h"

namespace SnakeServer {
namespace GameObject {

static const float VELOCITY_MULTIPLIER = 0.7f;

class Snake : public Event::IUpdatable {
public:
    Snake(Vector2D &t_pos, Vector2D &t_dir);

    virtual ~Snake();

    void addEvent(Event::BaseEvent *event);

    Event::BaseEvent *applyEvent() {
        if (m_eventQueue.empty()) {
            return nullptr;
        }

        Event::BaseEvent *event = m_eventQueue.front();
        m_eventQueue.pop_front();
        event->applyChanged(*this);
        return event;
    }

    std::string getDescription();

    Vector2D m_pos = Vector2D::ZERO();
    Vector2D m_dir = Vector2D::RIGHT();
    Vector2D m_vel = Vector2D::ONES();
    int size = 25;

private:
    std::list<Event::BaseEvent*> m_eventQueue; // TODO unique pointer
};

}
}

#endif //SNAKE_SERVER_SNAKE_H
