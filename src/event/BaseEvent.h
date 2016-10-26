#ifndef SNAKE_SERVER_BASEEVENT_H
#define SNAKE_SERVER_BASEEVENT_H

#include <string>
#include <stdexcept>
#include "IUpdatable.h"

namespace SnakeServer {
namespace Event {

enum EventType {
    WORLD, GAME_OBJECT
};

class BaseEvent {
public:
    BaseEvent(int t_userID) : m_userID(t_userID) {}

    virtual ~BaseEvent() {}

    int getUserID() { return m_userID; }

    virtual std::string getDescription() {return "";}

    virtual std::string getData() { return "";}

    virtual void applyChanged(IUpdatable &updatable) {}

    virtual EventType getEventType() {throw std::runtime_error("unimplemented");};

protected:
    int m_userID = -1;
};

}
}

#endif //SNAKE_SERVER_BASEEVENT_H
