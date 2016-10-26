#ifndef SNAKE_SERVER_LOGOUTEVENT_H
#define SNAKE_SERVER_LOGOUTEVENT_H

#include "BaseEvent.h"

namespace SnakeServer {
namespace Event {

class LogoutEvent : public BaseEvent {
public:
    LogoutEvent(int t_userID);

    virtual ~LogoutEvent();

    virtual std::string getDescription() override;

    virtual std::string getData() override;

    virtual void applyChanged(IUpdatable &updatable) override;

    virtual EventType getEventType() override;

private:
};

}
}

#endif //SNAKE_SERVER_LOGOUTEVENT_H
