#include "RemoveSnakeEvent.h"

namespace SnakeServer {
namespace Event {

RemoveSnakeEvent::RemoveSnakeEvent(int t_uid) : m_uid(t_uid) {}

RemoveSnakeEvent::~RemoveSnakeEvent() {}

std::string RemoveSnakeEvent::getDescription() {
    return "RemoveSnakeEvent";
}

std::string RemoveSnakeEvent::getData() {
    return "remsnake:{" + std::to_string(m_uid) + "}";
}

void RemoveSnakeEvent::applyChanged(IUpdatable &updatable) {

}

EventType RemoveSnakeEvent::getEventType() {
    return WORLD;
}

int RemoveSnakeEvent::getUserID() {
    return m_uid;
}

}
}