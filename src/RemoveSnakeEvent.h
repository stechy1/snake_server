#ifndef SNAKE_SERVER_REMOVESNAKEEVENT_H
#define SNAKE_SERVER_REMOVESNAKEEVENT_H

#include "BaseEvent.h"

namespace SnakeServer {
namespace Event {
class RemoveSnakeEvent : public BaseEvent {
public:
    RemoveSnakeEvent(int t_uid);

    virtual ~RemoveSnakeEvent();

    virtual std::string getDescription() override;

    virtual std::string getData() override;

    virtual void applyChanged(IUpdatable &updatable) override;

    virtual EventType getEventType() override;

    virtual int getUserID() override;

private:
    int m_uid;
};

}
}

#endif //SNAKE_SERVER_REMOVESNAKEEVENT_H
