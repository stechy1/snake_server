#include "LoginEvent.h"

namespace SnakeServer {

    namespace Event {

        LoginEvent::LoginEvent(int t_clientID, std::string t_data)
                : m_clientID(t_clientID) {
            m_nickname = t_data.substr(1);
        }

        LoginEvent::~LoginEvent() {}

        std::string LoginEvent::getBytes() {
            return "";
        }

        std::string LoginEvent::getDescription() {
            return "LoginEvent";
        }
    }
}