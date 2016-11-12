#ifndef SNAKE_SERVER_DATAPARSER_H
#define SNAKE_SERVER_DATAPARSER_H

#include <stdexcept>
#include <boost/uuid/uuid.hpp>
#include "Event.h"

namespace SnakeServer {

typedef boost::uuids::uuid uuid;

const std::string P_EVENT_DELIMITER = ":";
const std::string P_LOGIN = "login:";
const std::string P_LOGOUT = "logout";
const std::string P_CHANGE_DIR = "changedir:";

std::vector<std::string> split(const std::string str, const std::string delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

std::unique_ptr<InputEvent> parseEvent(uuid clientID, std::string data) {
    unsigned long delimiterIndex = data.find(P_EVENT_DELIMITER);

    if (data.find(P_LOGIN) != std::string::npos) {
        std::string res = data.substr(delimiterIndex + 1);
        return std::make_unique<LoginInputEvent>(clientID, res);
    } else if (data.find(P_LOGOUT) != std::string::npos) {
        return std::make_unique<LogoutInputEvent>(clientID);
    } else if (data.find(P_CHANGE_DIR) != std::string::npos) {
        std::string res = data.substr(delimiterIndex + 1);
        std::vector<std::string> dirData = split(res, "|");
        double x = std::stod(dirData[0]);
        double y = std::stod(dirData[1]);

        Vector2D dir(x, y);
        return std::make_unique<SnakeChangeDirectionInputEvent>(clientID, dir);
    }

    std::cout << "Nebyl nalezen odpovídající event" << std::endl;
    throw std::runtime_error("Could not parse event");
}

}

#endif //SNAKE_SERVER_DATAPARSER_H
