#ifndef SNAKE_COMMONS
#define SNAKE_COMMONS

#include <string>
#include <vector>

namespace SnakeServer {
    namespace Utils {

        bool isInteger(const std::string &s);

        std::vector<std::string> split(const std::string str, const std::string delim);
    } // end namespace Utils

} // end namespace SnakeServer
#endif