#ifndef SNAKE_SERVER_EVENT_H
#define SNAKE_SERVER_EVENT_H

#include <string>
#include <map>
#include "Vector2D.h"
#include "Food.h"
#include "Snake.h"

namespace SnakeServer {

enum EventType {
    WORLD = 1 << 0,
    GAME_OBJECT = 1 << 1,
    LOGIN = 1 << 2,
    LOGOUT = 1 << 3,
    CHANGE_DIR = 1 << 4
};

inline EventType operator|(EventType a, EventType b) {
    return static_cast<EventType>(static_cast<int>(a) | static_cast<int>(b));
}

inline EventType operator&(EventType a, EventType b) {
    return static_cast<EventType>(static_cast<int>(a) & static_cast<int>(b));
}

// Získám přes parser
class InputEvent {
public:
    virtual EventType getEventType() = 0;

    virtual int getUserID() = 0;

    virtual std::string getDescription() = 0;
};

class LoginInputEvent : public InputEvent {
public:
    LoginInputEvent(int t_userID, const std::string &t_username);

    virtual EventType getEventType() override;

    virtual int getUserID() override;

    virtual std::string getDescription() override;

private:
    int m_userID;
    std::string m_username;
};

class LogoutInputEvent : public InputEvent {
public:
    LogoutInputEvent(int t_userID);

    virtual EventType getEventType() override;

    virtual int getUserID() override;

    virtual std::string getDescription() override;

private:
    int m_userID;
};

class SnakeChangeDirectionInputEvent : public InputEvent {
public:
    SnakeChangeDirectionInputEvent(int t_userID, const Vector2D &t_direction);

    virtual EventType getEventType() override;

    virtual int getUserID() override;

    virtual std::string getDescription() override;

    const Vector2D &getDirection() const;

private:
    int m_userID;
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
    InitOutputEvent(int t_uid, std::shared_ptr<GameObject::Snake> t_snake, int t_width, int t_height,
                    std::map<int, std::shared_ptr<GameObject::Snake>> t_snakes,
                    std::map<int, GameObject::Food *> &t_food);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    std::string playerValues(std::map<int, std::shared_ptr<GameObject::Snake>> t_snakes);

    std::string foodValues(std::map<int, GameObject::Food *> &t_food);

    std::string m_data = "";
};

class AddSnakeOutputEvent : public OutputEvent {
public:
    AddSnakeOutputEvent(int uid, const Vector2D &t_pos, const Vector2D &t_dir);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    std::string m_data;
};

class RemoveSnakeOutputEvent : public OutputEvent {
public:
    RemoveSnakeOutputEvent(int t_uid);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    int m_uid;
};

class SnakeChangeDirectionOutputEvent : public OutputEvent {
public:
    SnakeChangeDirectionOutputEvent(int t_uid, const Vector2D &t_dir);

    virtual std::string getData() override;

    virtual std::string getDescription() override;

private:
    int m_uid;
    Vector2D m_dir;
};

}

#endif //SNAKE_SERVER_EVENT_H
