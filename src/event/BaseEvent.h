#ifndef SNAKE_SERVER_BASEEVENT_H
#define SNAKE_SERVER_BASEEVENT_H

#include <string>
#include "IUpdatable.h"

namespace SnakeServer {
namespace Event {

class BaseEvent {
public:
    BaseEvent() {}

    virtual ~BaseEvent() {}

    virtual std::string getDescription() = 0;

    virtual std::string getData() = 0;

    virtual void applyChanged(IUpdatable &updatable) = 0;
};

}
}

#endif //SNAKE_SERVER_BASEEVENT_H
