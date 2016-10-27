#ifndef SNAKE_SERVER_LOGINEVENT_H
#define SNAKE_SERVER_LOGINEVENT_H

#include "BaseEvent.h"

namespace SnakeServer {
namespace Event {

class LoginEvent : public BaseEvent {
public:
    LoginEvent(int t_userID, std::string t_username);

    virtual std::string getDescription() override;

    virtual std::string getData() override;

    virtual void applyChanged(IUpdatable &updatable) override;

    virtual EventType getEventType() override;

    virtual int getUserID() override;

private:
    int m_userID;
    std::string m_username;
};

}
}


#endif //SNAKE_SERVER_LOGINEVENT_H
