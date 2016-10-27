#ifndef SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H
#define SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H

#include <memory>
#include "BaseEvent.h"
#include "Vector2D.h"

namespace SnakeServer {
namespace Event {

class SnakeChangeDirectionEvent : public BaseEvent {
public:
    SnakeChangeDirectionEvent(int t_userID, Vector2D &t_direction);

    SnakeChangeDirectionEvent(const SnakeChangeDirectionEvent &other) {
        m_userID = other.m_userID;
        m_direction = other.m_direction;
    }

    virtual std::string getDescription() override;

    virtual std::string getData() override;

    virtual void applyChanged(IUpdatable &updatable) override;

    virtual EventType getEventType() override;

    virtual int getUserID() override;

private:
    int m_userID;
    Vector2D m_direction;
};

}
}


#endif //SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H
