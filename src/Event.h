#ifndef SNAKE_SERVER_EVENT_H
#define SNAKE_SERVER_EVENT_H

#include <string>
#include <map>
#include <boost/uuid/uuid.hpp>
#include "Vector2D.h"
#include "Food.h"
#include "Snake.h"

namespace SnakeServer {

typedef boost::uuids::uuid uuid;

static const std::string EVENT_LINE_SEPARATOR = "\n";
static const std::string VALUE_SEPARATOR = "|";
static const std::string ID_OPEN_BRACKET = "(";
static const std::string ID_CLOSE_BRACKET = ")";
static const std::string EVENT_TYPE_OPEN_BRACKET = "{";
static const std::string EVENT_TYPE_CLOSE_BRACKET = "}";
static const std::string VALUE_OPEN_BRACKET = "[";
static const std::string VALUE_CLOSE_BRACKET = "]";
static const std::string EVENT_VALUE_OPEN_BRACKET = "{[";
static const std::string EVENT_VALUE_CLOSE_BRACKET = "]}";

enum EventType {
    LOGIN,
    LOGOUT,
    CHANGE_DIR
};

// Získám přes parser
class InputEvent {
public:
    virtual EventType getEventType() = 0;

    virtual uuid &getUserID() = 0;

    virtual std::string getDescription() = 0;
};

class LoginInputEvent : public InputEvent {
public:
    LoginInputEvent(uuid t_clientID, const std::string &t_username);

    virtual EventType getEventType() override;

    virtual uuid &getUserID() override;

    virtual std::string getDescription() override;

    const std::string &getUsername() const;

private:
    uuid m_clientID;
    std::string m_username;
};

class LogoutInputEvent : public InputEvent {
public:
    LogoutInputEvent(uuid t_userID);

    virtual EventType getEventType() override;

    virtual uuid &getUserID() override;

    virtual std::string getDescription() override;

private:
    uuid m_clientID;
};

class SnakeChangeDirectionInputEvent : public InputEvent {
public:
    SnakeChangeDirectionInputEvent(uuid t_clientID, const Vector2D &t_direction);

    virtual EventType getEventType() override;

    virtual uuid &getUserID() override;

    virtual std::string getDescription() override;

    const Vector2D &getDirection() const;

private:
    uuid m_clientID;
    Vector2D m_direction;
};

// Jde ven ke klientům
class OutputEvent {
public:
    virtual std::string getData() = 0;

    virtual std::string getDescription() = 0;
};

class InitOutputEvent : public OutputEvent {
public:
    InitOutputEvent(uuid &t_clientID, std::shared_ptr<GameObject::Snake> &t_snake, int t_width, int t_height,
                    std::map<uuid, std::shared_ptr<GameObject::Snake>> &t_snakes,
                    std::map<int, std::shared_ptr<GameObject::Food>> &t_food);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    std::string foodValues(std::map<int, std::shared_ptr<GameObject::Food>> &t_food);

    std::string m_data = "";
};

class AddSnakeOutputEvent : public OutputEvent {
public:
    AddSnakeOutputEvent(uuid t_clientID, std::shared_ptr<GameObject::Snake> snake);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    std::string m_data;
};

class RemoveSnakeOutputEvent : public OutputEvent {
public:
    RemoveSnakeOutputEvent(uuid t_clientID);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    uuid m_clientID;
};

class EatFoodOutputEvent : public OutputEvent {
public:
    EatFoodOutputEvent(int t_id, const uuid &clientId);

    std::string getData() override;

    std::string getDescription() override;

    int getM_id() const;

private:
    int m_id;
    const uuid &m_clientId;
};

class SnakeChangeDirectionOutputEvent : public OutputEvent {
public:
    SnakeChangeDirectionOutputEvent(uuid t_clientID, const Vector2D &t_dir);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    uuid m_clientID;
    Vector2D m_dir;
};

class SyncOutputEvent : public OutputEvent {
public:
    SyncOutputEvent(std::map<uuid, std::shared_ptr<GameObject::Snake>> t_snakes);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    std::string m_data = "";
};



}

#endif //SNAKE_SERVER_EVENT_H
