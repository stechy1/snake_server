#ifndef SNAKE_SERVER_DATAPARSER_H
#define SNAKE_SERVER_DATAPARSER_H

#include <stdexcept>
#include "Utils.h"
#include "Event.h"

namespace SnakeServer {

const std::string EVENT_DELIMITER = ":";
const std::string LOGIN = "login:";
const std::string LOGOUT = "logout";
const std::string CHANGE_DIR = "changedir:";

std::unique_ptr<InputEvent> parseEvent(int userID, std::string data) {
    unsigned long delimiterIndex = data.find(EVENT_DELIMITER);

    if (data.find(LOGIN) != std::string::npos) {
        std::string res = data.substr(delimiterIndex+1);
        return std::make_unique<LoginInputEvent>(userID, res);
    } else if (data.find(LOGOUT) != std::string::npos) {
        return std::make_unique<LogoutInputEvent>(userID);
    } else if (data.find(CHANGE_DIR) != std::string::npos) {
        std::string res = data.substr(delimiterIndex+1);
        std::vector<std::string> dirData = Utils::split(res, "|");
        double x = std::stod(dirData[0]);
        double y = std::stod(dirData[1]);

        Vector2D dir(x, y);
        return std::make_unique<SnakeChangeDirectionInputEvent>(userID, dir);
    }

    std::cout << "Nebyl nalezen odpovídající event" << std::endl;
    throw std::runtime_error("Could not parse event");
}

}

#endif //SNAKE_SERVER_DATAPARSER_H
