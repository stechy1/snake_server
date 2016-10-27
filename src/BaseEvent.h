#ifndef SNAKE_SERVER_BASEEVENT_H
#define SNAKE_SERVER_BASEEVENT_H

#include <string>
#include "IUpdatable.h"

namespace SnakeServer {
namespace Event {

enum EventType {
    WORLD, GAME_OBJECT
};

class BaseEvent {
public:
    BaseEvent() {}

    virtual ~BaseEvent() {}

    virtual std::string getDescription() = 0;

    virtual std::string getData() = 0;

    virtual void applyChanged(IUpdatable &updatable) = 0;

    virtual EventType getEventType() = 0;

    virtual int getUserID() = 0;


};

}
}

#endif //SNAKE_SERVER_BASEEVENT_H
