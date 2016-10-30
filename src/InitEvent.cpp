#include <cstdarg>
#include "InitEvent.h"

namespace SnakeServer {
namespace Event {

InitEvent::InitEvent(int t_uid, GameObject::Snake &t_snake, int t_width, int t_height, std::map<int, GameObject::Snake*> &t_snakes, std::map<int, GameObject::Food*> &t_food)
        : m_uid(t_uid), m_width(t_width), m_height(t_height) {
    m_data =  "init:{" + joinValues("|", 6, (double)m_uid, t_snake.m_pos.X(), t_snake.m_pos.Y(), t_snake.m_dir.X(), t_snake.m_dir.Y(), (double)t_snake.size) + "}"
            + "size:{" + joinValues("|", 2, (double)t_width, (double)t_height) + "}"
            + "players:{" + playerValues(t_snakes) + "}"
            + "food:{" + foodValues(t_food) + "};";

}

std::string InitEvent::getDescription() {
    return "InitEvent";
}

std::string InitEvent::getData() {
    return m_data;
}

void InitEvent::applyChanged(IUpdatable &updatable) {

}

EventType InitEvent::getEventType() {
    return EventType::WORLD;
}

int InitEvent::getUserID() {
    return m_uid;
}

std::string InitEvent::joinValues(std::string delimiter, int count, ...) {
    va_list ap;
    va_start(ap, count);

    std::string res = "[";

    for(int i = 0; i < count; ++i) {
        res += std::to_string(va_arg(ap, double)) + delimiter;
    }

    res.erase(res.size() - 1);
    res += "]";

    va_end(ap);
    return res;
}

std::string InitEvent::playerValues(std::map<int, GameObject::Snake*> &t_snakes) {
    std::string res = "";

    if (t_snakes.size() == 0) {
        return res;
    }

    for(auto info : t_snakes) {
        GameObject::Snake &snake = *info.second;
        std::string infoString = joinValues("|", 6, (double)info.first, snake.m_pos.X(), snake.m_pos.Y(), snake.m_dir.X(), snake.m_dir.Y(), (double)snake.size);
        res += infoString + ",";
    }

    res = res.erase(res.size() - 1);

    return res;
}

std::string InitEvent::foodValues(std::map<int, GameObject::Food*> &t_food) {
    std::string res = "";

    if (t_food.size() == 0) {
        return res;
    }

    for(auto info : t_food) {
        GameObject::Food &food = *info.second;
        std::string infoString = joinValues("|", 3, (double)info.first, food.m_pos.X(), food.m_pos.Y());
        res += infoString + ",";
    }

    res = res.erase(res.size() - 1);

    return res;
}

}
}