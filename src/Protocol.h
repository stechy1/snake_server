#ifndef SNAKE_SERVER_DATAPARSER_H
#define SNAKE_SERVER_DATAPARSER_H

#include <stdexcept>
#include "Utils.h"
#include "event/BaseEvent.h"
#include "event/LoginEvent.h"
#include "event/LogoutEvent.h"
#include "event/SnakeChangeDirectionEvent.h"

namespace SnakeServer {

const std::string EVENT_DELIMITER = ":";
const std::string LOGIN = "login:";
const std::string LOGOUT = "logout";
const std::string CHANGE_DIR = "changedir:";

std::unique_ptr<Event::BaseEvent> parseEvent(int userID, std::string data) {
    unsigned long delimiterIndex = data.find(EVENT_DELIMITER);

    if (data.find(LOGIN) != std::string::npos) {
        std::string res = data.substr(delimiterIndex+1);

        std::unique_ptr<Event::BaseEvent> event = std::make_unique<Event::LoginEvent>(userID, res);
        return event;
    } else if (data.find(LOGOUT) != std::string::npos) {
        std::unique_ptr<Event::BaseEvent> event = std::make_unique<Event::LogoutEvent>(userID);
        return event;
    } else if (data.find(CHANGE_DIR) != std::string::npos) {
        std::string res = data.substr(delimiterIndex+1);

        std::vector<std::string> dirData = Utils::split(res, "|");
        double x = std::stod(dirData[0]);
        double y = std::stod(dirData[1]);

        Vector2D dir(x, y);
        std::unique_ptr<Event::BaseEvent> event = std::make_unique<Event::SnakeChangeDirectionEvent>(userID, dir);
        return event;
    }

    std::cout << "Nebyl nalezen odpovídající event" << std::endl;
    throw std::runtime_error("Could not parse event");
}

}

#endif //SNAKE_SERVER_DATAPARSER_H
