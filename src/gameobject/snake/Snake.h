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
    Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir);

    Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir, std::unique_ptr<Vector2D> t_vel);

    void addEvent(std::shared_ptr<Event::BaseEvent> event);

    virtual void update(double t, double dt) override;

    virtual std::string getDescription() override;

private:
    std::list<std::shared_ptr<Event::BaseEvent>> m_eventQueue;
};

}
}
}

#endif //SNAKE_SERVER_SNAKE_H
