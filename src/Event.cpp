#include <cstdarg>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/assign/list_of.hpp>
#include "Event.h"

namespace SnakeServer {


std::string joinValues(std::string t_delimiter, const std::vector<std::string> &params) {

    std::string res = "";

    for (auto &param : params) {
        res += (param + t_delimiter);
    }

    res.erase(res.size() - 1);

    return res;
}

std::string playerValue(const uuid &uid, std::shared_ptr<GameObject::Snake> &t_snake) {
    return VALUE_OPEN_BRACKET
           + joinValues(VALUE_SEPARATOR,
                        boost::assign::list_of
                                (boost::uuids::to_string(uid))
                                (boost::lexical_cast<std::string>(t_snake->getUsername()))
                                (boost::lexical_cast<std::string>(t_snake->getPosition().X()))
                                (boost::lexical_cast<std::string>(t_snake->getPosition().Y()))
                                (boost::lexical_cast<std::string>(t_snake->getDirection().X()))
                                (boost::lexical_cast<std::string>(t_snake->getDirection().Y()))
                                (boost::lexical_cast<std::string>(t_snake->getSize())))
           + VALUE_CLOSE_BRACKET;
}

std::string playersValues(std::map<uuid, std::shared_ptr<GameObject::Snake>> t_snakes) {
    std::string res = "";

    if (t_snakes.size() == 0) {
        return res;
    }

    for (auto &info : t_snakes) {
        res += playerValue(info.first, info.second) + ",";
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

const std::string &LoginInputEvent::getUsername() const {
    return m_username;
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
InitOutputEvent::InitOutputEvent(uuid &t_clientID, std::shared_ptr<GameObject::Snake> &t_snake, int t_width,
                                 int t_height,
                                 std::map<uuid, std::shared_ptr<GameObject::Snake>> &t_snakes,
                                 std::map<int, std::shared_ptr<GameObject::Food>> &t_food) {
    m_data = "init:" + EVENT_TYPE_OPEN_BRACKET +
             playerValue(t_clientID, t_snake) + EVENT_TYPE_CLOSE_BRACKET
             + "size:" + EVENT_VALUE_OPEN_BRACKET +
             joinValues(VALUE_SEPARATOR, boost::assign::list_of
                     (boost::lexical_cast<std::string>(t_width))
                     (boost::lexical_cast<std::string>(t_height)))
             + EVENT_VALUE_CLOSE_BRACKET
             + "players:" + EVENT_TYPE_OPEN_BRACKET + playersValues(t_snakes) + EVENT_TYPE_CLOSE_BRACKET
             + "food:" + EVENT_TYPE_OPEN_BRACKET + foodValues(t_food) + EVENT_TYPE_CLOSE_BRACKET +
             EVENT_LINE_SEPARATOR;
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
                joinValues(VALUE_SEPARATOR, boost::assign::list_of
                        (boost::lexical_cast<std::string>(info.first))
                        (boost::lexical_cast<std::string>(food.getPosition().X()))
                        (boost::lexical_cast<std::string>(food.getPosition().Y())))
                + VALUE_CLOSE_BRACKET;
        res += infoString + ",";
    }

    res = res.erase(res.size() - 1);

    return res;
}

// RemoveSnake event
RemoveSnakeOutputEvent::RemoveSnakeOutputEvent(uuid t_clientID)
        : m_clientID(t_clientID) {}

std::string RemoveSnakeOutputEvent::getData() {
    return "remsnake:" + EVENT_TYPE_OPEN_BRACKET + (boost::uuids::to_string(m_clientID)) + EVENT_TYPE_CLOSE_BRACKET +
           EVENT_LINE_SEPARATOR;
}

std::string RemoveSnakeOutputEvent::getDescription() {
    return "RemoveSnakeEvent";
}

// RemoveFood event
EatFoodOutputEvent::EatFoodOutputEvent(int t_id, const uuid &t_clientId) : m_id(t_id), m_clientId(t_clientId) {}

std::string EatFoodOutputEvent::getData() {
    return "eatfood:" + EVENT_VALUE_OPEN_BRACKET
           + joinValues(VALUE_SEPARATOR, boost::assign::list_of
            (boost::lexical_cast<std::string>(m_id))
            (boost::uuids::to_string(m_clientId)))
           + EVENT_VALUE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string EatFoodOutputEvent::getDescription() {
    return "RemoveFoodEvent";
}

// SnakeChangeDrection event
SnakeChangeDirectionOutputEvent::SnakeChangeDirectionOutputEvent(uuid t_clientID, const Vector2D &t_dir)
        : m_clientID(t_clientID), m_dir(t_dir) {}

std::string SnakeChangeDirectionOutputEvent::getData() {
    return "changedir:" + EVENT_VALUE_OPEN_BRACKET + joinValues(VALUE_SEPARATOR, boost::assign::list_of
            (boost::lexical_cast<std::string>(m_dir.X()))
            (boost::lexical_cast<std::string>(m_dir.Y())))
           + VALUE_CLOSE_BRACKET
           + EVENT_TYPE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string SnakeChangeDirectionOutputEvent::getDescription() {
    return "SnakeChangeDirectionEvent";
}

// AddSnake event
AddSnakeOutputEvent::AddSnakeOutputEvent(uuid t_clientID, std::shared_ptr<GameObject::Snake> snake) {
    m_data = "addsnake:" + EVENT_TYPE_OPEN_BRACKET +
             playerValue(t_clientID, snake)
             + EVENT_TYPE_CLOSE_BRACKET + EVENT_LINE_SEPARATOR;
}

std::string AddSnakeOutputEvent::getData() {
    return m_data;
}

std::string AddSnakeOutputEvent::getDescription() {
    return "AddSnakeEvent";
}

SyncOutputEvent::SyncOutputEvent(std::map<uuid, std::shared_ptr<GameObject::Snake>> t_snakes) {
    m_data = "sync:" + EVENT_TYPE_OPEN_BRACKET + playersValues(t_snakes) + EVENT_TYPE_CLOSE_BRACKET +
             EVENT_LINE_SEPARATOR;
}

std::string SyncOutputEvent::getData() {
    return m_data;
}

std::string SyncOutputEvent::getDescription() {
    return "SyncEvent";
}

GameOverOutputEvent::GameOverOutputEvent(const uuid &t_clientID) : m_clientID(t_clientID) {}

std::string GameOverOutputEvent::getData() {
    return "gameover:" + EVENT_TYPE_OPEN_BRACKET + (boost::uuids::to_string(m_clientID)) + EVENT_TYPE_CLOSE_BRACKET +
           EVENT_LINE_SEPARATOR;
}

std::string GameOverOutputEvent::getDescription() {
    return "GameOverEvent";
}
}