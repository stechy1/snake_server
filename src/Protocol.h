#ifndef SNAKE_SERVER_DATAPARSER_H
#define SNAKE_SERVER_DATAPARSER_H

#include <stdexcept>
#include "event/BaseEvent.h"
#include "event/LoginEvent.h"

namespace SnakeServer {

const std::string LOGIN = "login:";

Event::BaseEvent parseEvent(int userID, std::string data) {

    if (data.find("login:") != std::string::npos) {
        std::string res = data.substr(LOGIN.size());

        //Event::BaseEvent event = Event::LoginEvent(userID, res);
        Event::LoginEvent event(userID, res);
        return event;
    }

    throw std::runtime_error("Could not parse event");
}

}

#endif //SNAKE_SERVER_DATAPARSER_H
