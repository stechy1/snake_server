#ifndef SNAKE_SERVER_INITEVENT_H
#define SNAKE_SERVER_INITEVENT_H

#include <map>
#include "BaseEvent.h"
#include "Snake.h"
#include "Food.h"

namespace SnakeServer {
namespace Event {

class InitEvent : public BaseEvent {
public:
    InitEvent(int t_uid, GameObject::Snake &t_snake, int t_width, int t_height, std::map<int, GameObject::Snake*> &t_snakes, std::map<int, GameObject::Food*> &t_food);

    virtual ~InitEvent() {};

    virtual std::string getDescription() override;

    virtual std::string getData() override;

    virtual void applyChanged(IUpdatable &updatable) override;

    virtual EventType getEventType() override;

    virtual int getUserID() override;

private:
    std::string playerValues(std::map<int, GameObject::Snake*> &t_snakes);
    std::string foodValues(std::map<int, GameObject::Food*> &t_food);
    std::string joinValues(std::string delimiter, int count,  ...);

    std::string m_data;

    int m_uid;
    int m_width;
    int m_height;


};

}
}

#endif //SNAKE_SERVER_INITEVENT_H
