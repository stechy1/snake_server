#include <cstdarg>
#include "Event.h"

namespace SnakeServer {

// Input events

// Login event
LoginInputEvent::LoginInputEvent(int t_userID, const std::string &t_username) : m_userID(t_userID), m_username(t_username) {}

EventType LoginInputEvent::getEventType() {
    WORLD;
}

int LoginInputEvent::getUserID() {
    return m_userID;
}

std::string LoginInputEvent::getDescription() {
    return "LoginInputEvent";
}

// Logout event
LogoutInputEvent::LogoutInputEvent(int t_userID) : m_userID(t_userID) {}

EventType LogoutInputEvent::getEventType() {
    return WORLD;
}

int LogoutInputEvent::getUserID() {
    return m_userID;
}

std::string LogoutInputEvent::getDescription() {
    return "LogoutInputEvent";
}

// ChangeDirection event
SnakeChangeDirectionInputEvent::SnakeChangeDirectionInputEvent(int t_userID, const Vector2D &t_direction) : m_userID(
        t_userID), m_direction(t_direction) {}

EventType SnakeChangeDirectionInputEvent::getEventType() {
    return GAME_OBJECT;
}

int SnakeChangeDirectionInputEvent::getUserID() {
    return m_userID;
}

std::string SnakeChangeDirectionInputEvent::getDescription() {
    return "ChangeDirectionEvent";
}

// Output events

// Init event
InitOutputEvent::InitOutputEvent(int t_uid, GameObject::Snake &t_snake, int t_width, int t_height,
                                 std::map<int, GameObject::Snake *> &t_snakes,
                                 std::map<int, GameObject::Food *> &t_food) {
    m_data =  "init:{" + joinValues("|", 6, (double)t_uid, t_snake.m_pos.X(), t_snake.m_pos.Y(), t_snake.m_dir.X(), t_snake.m_dir.Y(), (double)t_snake.size) + "}"
              + "size:{" + joinValues("|", 2, (double)t_width, (double)t_height) + "}"
              + "players:{" + playerValues(t_snakes) + "}"
              + "food:{" + foodValues(t_food) + "};";
}

std::string InitOutputEvent::getData() {
    return m_data;
}

std::string InitOutputEvent::getDescription() {
    return "InitEvent";
}

std::string InitOutputEvent::joinValues(std::string t_delimiter, int t_count, ...) {
    va_list ap;
    va_start(ap, t_count);

    std::string res = "[";

    for(int i = 0; i < t_count; ++i) {
        res += std::to_string(va_arg(ap, double)) + t_delimiter;
    }

    res.erase(res.size() - 1);
    res += "]";

    va_end(ap);
    return res;
}

std::string InitOutputEvent::playerValues(std::map<int, GameObject::Snake*> &t_snakes) {
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

std::string InitOutputEvent::foodValues(std::map<int, GameObject::Food*> &t_food) {
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

// RemoveSnake event
RemoveSnakeOutputEvent::RemoveSnakeOutputEvent(int t_uid) : m_uid(t_uid) {}

std::string RemoveSnakeOutputEvent::getData() {
    return "remsnake:{" + std::to_string(m_uid) + "}";
}

std::string RemoveSnakeOutputEvent::getDescription() {
    return "RemoveSnakeEvent";
}

// SnakeChangeDrection event
SnakeChangeDirectionOutputEvent::SnakeChangeDirectionOutputEvent(int t_uid, const Vector2D &t_dir) : m_uid(t_uid),
                                                                                                     m_dir(t_dir) {}

std::string SnakeChangeDirectionOutputEvent::getData() {
    return "changedir:" + std::to_string(m_dir.X()) + "|" + std::to_string(m_dir.Y()) + ";";
}

std::string SnakeChangeDirectionOutputEvent::getDescription() {
    return "SnakeChangeDirection";
}
}