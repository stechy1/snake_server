#include <cstdarg>
#include "Event.h"

namespace SnakeServer {

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

std::string playerValues(std::map<int, std::shared_ptr<GameObject::Snake>> t_snakes) {
    std::string res = "";

    if (t_snakes.size() == 0) {
        return res;
    }

    for (auto &info : t_snakes) {
        auto snake = *info.second;
        std::string infoString = VALUE_OPEN_BRACKET
                                 + joinValues(VALUE_SEPARATOR, 6, (double) info.first, snake.getPosition().X(),
                                              snake.getPosition().Y(),
                                              snake.getDirection().X(), snake.getDirection().Y(),
                                              (double) snake.getSize())
                                 + VALUE_CLOSE_BRACKET;
        res += infoString + ",";
    }

    res = res.erase(res.size() - 1);


    return res;
}

// Input events

// Login event
LoginInputEvent::LoginInputEvent(int t_userID, const std::string &t_username)
        : m_userID(t_userID), m_username(t_username) {}

EventType LoginInputEvent::getEventType() {
    return LOGIN;
}

int LoginInputEvent::getUserID() {
    return m_userID;
}

std::string LoginInputEvent::getDescription() {
    return "LoginInputEvent";
}

// Logout event
LogoutInputEvent::LogoutInputEvent(int t_userID)
        : m_userID(t_userID) {}

EventType LogoutInputEvent::getEventType() {
    return LOGOUT;
}

int LogoutInputEvent::getUserID() {
    return m_userID;
}

std::string LogoutInputEvent::getDescription() {
    return "LogoutInputEvent";
}

// ChangeDirection event
SnakeChangeDirectionInputEvent::SnakeChangeDirectionInputEvent(int t_userID, const Vector2D &t_direction)
        : m_userID(t_userID), m_direction(t_direction) {}

EventType SnakeChangeDirectionInputEvent::getEventType() {
    return CHANGE_DIR;
}

int SnakeChangeDirectionInputEvent::getUserID() {
    return m_userID;
}

std::string SnakeChangeDirectionInputEvent::getDescription() {
    return "ChangeDirectionEvent";
}

const Vector2D &SnakeChangeDirectionInputEvent::getDirection() const {
    return m_direction;
}

// Output events

// Init event
InitOutputEvent::InitOutputEvent(int t_uid, std::shared_ptr<GameObject::Snake> t_snake, int t_width, int t_height,
                                 std::map<int, std::shared_ptr<GameObject::Snake>> t_snakes,
                                 std::map<int, GameObject::Food *> &t_food) {
    m_data = "init:" + EVENT_VALUE_OPEN_BRACKET +
             joinValues(VALUE_SEPARATOR, 6, (double) t_uid, t_snake->getPosition().X(), t_snake->getPosition().Y(),
                        t_snake->getDirection().X(), t_snake->getDirection().Y(), (double) t_snake->getSize()) +
             EVENT_VALUE_CLOSE_BRACKET
             + "size:" + EVENT_VALUE_OPEN_BRACKET +
             joinValues(VALUE_SEPARATOR, 2, (double) t_width, (double) t_height) + EVENT_VALUE_CLOSE_BRACKET
             + "players:" + EVENT_TYPE_OPEN_BRACKET + playerValues(t_snakes) + EVENT_TYPE_CLOSE_BRACKET
             + "food:" + EVENT_TYPE_OPEN_BRACKET + foodValues(t_food) + EVENT_TYPE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string InitOutputEvent::getData() {
    std::cout << "Posilam init event" << std::endl;
    std::cout << m_data << std::endl;
    return m_data;
}

std::string InitOutputEvent::getDescription() {
    return "InitEvent";
}

std::string InitOutputEvent::foodValues(std::map<int, GameObject::Food *> &t_food) {
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
RemoveSnakeOutputEvent::RemoveSnakeOutputEvent(int t_uid)
        : m_uid(t_uid) {}

std::string RemoveSnakeOutputEvent::getData() {
    return "remsnake:" + EVENT_TYPE_OPEN_BRACKET + std::to_string(m_uid) + EVENT_TYPE_CLOSE_BRACKET +
           EVENT_LINE_SEPARATOR;
}

std::string RemoveSnakeOutputEvent::getDescription() {
    return "RemoveSnakeEvent";
}

// SnakeChangeDrection event
SnakeChangeDirectionOutputEvent::SnakeChangeDirectionOutputEvent(int t_uid, const Vector2D &t_dir)
        : m_uid(t_uid), m_dir(t_dir) {}

std::string SnakeChangeDirectionOutputEvent::getData() {
    return "changedir:" + std::to_string(m_dir.X()) + VALUE_SEPARATOR + std::to_string(m_dir.Y()) +
           EVENT_LINE_SEPARATOR;
}

std::string SnakeChangeDirectionOutputEvent::getDescription() {
    return "SnakeChangeDirectionEvent";
}

// AddSnake event
AddSnakeOutputEvent::AddSnakeOutputEvent(int uid, const std::shared_ptr<GameObject::Snake> snake) {
    m_data = "addsnake:" + EVENT_VALUE_OPEN_BRACKET +
             joinValues(VALUE_SEPARATOR, 6, (double) uid, snake->getPosition().X(), snake->getPosition().Y(),
                        snake->getDirection().X(), snake->getDirection().Y(),
                        (double) snake->getSize()) + EVENT_TYPE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string AddSnakeOutputEvent::getData() {
    return m_data;
}

std::string AddSnakeOutputEvent::getDescription() {
    return "AddSnakeEvent";
}

SyncOutputEvent::SyncOutputEvent(std::map<int, std::shared_ptr<GameObject::Snake>> t_snakes) {
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