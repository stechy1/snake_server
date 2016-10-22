#ifndef SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H
#define SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H

#include <memory>
#include "BaseEvent.h"
#include "../Vector2D.h"

namespace SnakeServer {
namespace Event {

class SnakeChangeDirectionEvent : public BaseEvent {
public:
    SnakeChangeDirectionEvent(int t_userID, std::shared_ptr<Vector2D> t_direction);

    virtual std::string getDescription() override;

    virtual std::string getData() override;

    virtual void applyChanged(IUpdatable &updatable) override;

private:
    int m_userID;
    std::shared_ptr<Vector2D> m_direction;
};

}
}


#endif //SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H
