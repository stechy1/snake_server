#include "LogoutEvent.h"
#include "World.h"

namespace SnakeServer {
namespace Event {

LogoutEvent::LogoutEvent(int t_userID) : m_userID(t_userID) {}

LogoutEvent::~LogoutEvent() {}

std::string LogoutEvent::getDescription() {
    return "LogoutEvent";
}

std::string LogoutEvent::getData() {
    return "";
}

void LogoutEvent::applyChanged(IUpdatable &updatable) {
    SnakeServer::World &world = static_cast<SnakeServer::World&>(updatable);

    world.removeSnake(m_userID);
}

EventType LogoutEvent::getEventType() {
    return EventType::WORLD;
}

int LogoutEvent::getUserID() {
    return m_userID;
}

}
}
