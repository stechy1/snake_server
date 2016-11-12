#include <cstdarg>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Event.h"

namespace SnakeServer {

inline std::string formatUid(uuid clientID) {
    return ID_OPEN_BRACKET + boost::uuids::to_string(clientID) + ID_CLOSE_BRACKET;
}

std::string joinValues(std::string t_delimiter, int t_count, ...) {
    va_list ap;
    va_start(ap, t_count);

    std::string res = "";

    for (int i = 0; i < t_count; ++i) {
        res += std::to_string(va_arg(ap, double)) + t_delimiter;
    }

    res.erase(res.size() - 1);

    va_end(ap);
    return res;
}

std::string playerValues(std::map<uuid, std::shared_ptr<GameObject::Snake>> t_snakes) {
    std::string res = "";

    if (t_snakes.size() == 0) {
        return res;
    }

    for (auto &info : t_snakes) {
        auto snake = *info.second;
        std::string infoString = VALUE_OPEN_BRACKET
                                 + joinValues(VALUE_SEPARATOR, 5, snake.getPosition().X(),
                                              snake.getPosition().Y(),
                                              snake.getDirection().X(), snake.getDirection().Y(),
                                              (double) snake.getSize())
                                 + VALUE_CLOSE_BRACKET;
        res += formatUid(info.first) + infoString + ",";
    }

    res = res.erase(res.size() - 1);

    return res;
}

// Input events

// Login event
LoginInputEvent::LoginInputEvent(uuid t_clientID, const std::string &t_username)
        : m_clientID(t_clientID), m_username(t_username) {}

EventType LoginInputEvent::getEventType() {
    return LOGIN;
}

uuid &LoginInputEvent::getUserID() {
    return m_clientID;
}

std::string LoginInputEvent::getDescription() {
    return "LoginInputEvent";
}

// Logout event
LogoutInputEvent::LogoutInputEvent(uuid t_clientID)
        : m_clientID(t_clientID) {}

EventType LogoutInputEvent::getEventType() {
    return LOGOUT;
}

uuid &LogoutInputEvent::getUserID() {
    return m_clientID;
}

std::string LogoutInputEvent::getDescription() {
    return "LogoutInputEvent";
}

// ChangeDirection event
SnakeChangeDirectionInputEvent::SnakeChangeDirectionInputEvent(uuid t_clientID, const Vector2D &t_direction)
        : m_clientID(t_clientID), m_direction(t_direction) {}

EventType SnakeChangeDirectionInputEvent::getEventType() {
    return CHANGE_DIR;
}

uuid &SnakeChangeDirectionInputEvent::getUserID() {
    return m_clientID;
}

std::string SnakeChangeDirectionInputEvent::getDescription() {
    return "ChangeDirectionEvent";
}

const Vector2D &SnakeChangeDirectionInputEvent::getDirection() const {
    return m_direction;
}

// Output events

// Init event
InitOutputEvent::InitOutputEvent(uuid &t_clientID, std::shared_ptr<GameObject::Snake> &t_snake, int t_width, int t_height,
                                 std::map<uuid, std::shared_ptr<GameObject::Snake>> &t_snakes,
                                 std::map<int, std::shared_ptr<GameObject::Food>> &t_food) {
    m_data = "init:" + EVENT_VALUE_OPEN_BRACKET + formatUid(t_clientID) +
             joinValues(VALUE_SEPARATOR, 5, t_snake->getPosition().X(), t_snake->getPosition().Y(),
                        t_snake->getDirection().X(), t_snake->getDirection().Y(), (double) t_snake->getSize()) +
             EVENT_VALUE_CLOSE_BRACKET
             + "size:" + EVENT_VALUE_OPEN_BRACKET +
             joinValues(VALUE_SEPARATOR, 2, (double) t_width, (double) t_height) + EVENT_VALUE_CLOSE_BRACKET
             + "players:" + EVENT_TYPE_OPEN_BRACKET + playerValues(t_snakes) + EVENT_TYPE_CLOSE_BRACKET
             + "food:" + EVENT_TYPE_OPEN_BRACKET + foodValues(t_food) + EVENT_TYPE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string InitOutputEvent::getData() {
    return m_data;
}

std::string InitOutputEvent::getDescription() {
    return "InitEvent";
}

std::string InitOutputEvent::foodValues(std::map<int, std::shared_ptr<GameObject::Food>> &t_food) {
    std::string res = "";

    if (t_food.size() == 0) {
        return res;
    }

    for (auto &info : t_food) {
        auto food = *info.second;
        std::string infoString =
                VALUE_OPEN_BRACKET +
                joinValues(VALUE_SEPARATOR, 3, (double) info.first, food.m_pos.X(), food.m_pos.Y()) +
                VALUE_CLOSE_BRACKET;
        res += infoString + ",";
    }

    res = res.erase(res.size() - 1);

    return res;
}

// RemoveSnake event
RemoveSnakeOutputEvent::RemoveSnakeOutputEvent(uuid t_clientID)
        : m_clientID(t_clientID) {}

std::string RemoveSnakeOutputEvent::getData() {
    return "remsnake:" + EVENT_TYPE_OPEN_BRACKET + formatUid(m_clientID) + EVENT_TYPE_CLOSE_BRACKET +
           EVENT_LINE_SEPARATOR;
}

std::string RemoveSnakeOutputEvent::getDescription() {
    return "RemoveSnakeEvent";
}

// SnakeChangeDrection event
SnakeChangeDirectionOutputEvent::SnakeChangeDirectionOutputEvent(uuid t_clientID, const Vector2D &t_dir)
        : m_clientID(t_clientID), m_dir(t_dir) {}

std::string SnakeChangeDirectionOutputEvent::getData() {
    return "changedir:" + EVENT_TYPE_OPEN_BRACKET + formatUid(m_clientID) + joinValues(VALUE_SEPARATOR, 2, m_dir.X(), m_dir.Y()) + EVENT_TYPE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string SnakeChangeDirectionOutputEvent::getDescription() {
    return "SnakeChangeDirectionEvent";
}

// AddSnake event
AddSnakeOutputEvent::AddSnakeOutputEvent(uuid t_clientID, const std::shared_ptr<GameObject::Snake> snake) {
    m_data = "addsnake:" + EVENT_VALUE_OPEN_BRACKET + formatUid(t_clientID) +
             joinValues(VALUE_SEPARATOR, 5, snake->getPosition().X(), snake->getPosition().Y(),
                        snake->getDirection().X(), snake->getDirection().Y(),
                        (double) snake->getSize()) + EVENT_TYPE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string AddSnakeOutputEvent::getData() {
    return m_data;
}

std::string AddSnakeOutputEvent::getDescription() {
    return "AddSnakeEvent";
}

SyncOutputEvent::SyncOutputEvent(std::map<uuid, std::shared_ptr<GameObject::Snake>> t_snakes) {
    m_data = "sync:" + EVENT_TYPE_OPEN_BRACKET + playerValues(t_snakes) + EVENT_TYPE_CLOSE_BRACKET +
             EVENT_LINE_SEPARATOR;
}

std::string SyncOutputEvent::getData() {
    return m_data;
}

std::string SyncOutputEvent::getDescription() {
    return "SyncEvent";
}

}