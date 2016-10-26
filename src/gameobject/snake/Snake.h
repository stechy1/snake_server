#ifndef SNAKE_SERVER_SNAKE_H
#define SNAKE_SERVER_SNAKE_H

#include <list>
#include "../BaseObject.h"
#include "../../event/BaseEvent.h"
#include "../../event/IUpdatable.h"

namespace SnakeServer {
namespace GameObject {
namespace Snake {

    static const unsigned int SIZE = 15;
    static const float VELOCITY_MULTIPLIER = 0.7f;

class Snake : public BaseObject, public Event::IUpdatable {
public:
    Snake();

    Snake(Vector2D &t_pos);
    Snake(Vector2D &t_pos, Vector2D &t_dir);
    Snake(Vector2D &t_pos, Vector2D &t_dir, Vector2D &t_vel);

    virtual ~Snake();

    void addEvent(Event::BaseEvent &event);

    virtual void update(double t, double dt) override;

    virtual std::string getDescription() override;

private:
    std::list<Event::BaseEvent> m_eventQueue;
};

}
}
}

#endif //SNAKE_SERVER_SNAKE_H
