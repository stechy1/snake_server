#include "Commons.h"

namespace SnakeServer {

    namespace Utils {
        bool isInteger(const std::string &s) {
            if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

            char *p;
            strtol(s.c_str(), &p, 10);

            return (*p == 0);
        }

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
    } // end namespace Utils

} // end namespace SnakeServer