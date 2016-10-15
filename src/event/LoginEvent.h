#ifndef SNAKE_SERVER_LOGINEVENT_H
#define SNAKE_SERVER_LOGINEVENT_H

#include <string>

namespace SnakeServer {

    namespace Event {

        //class GameEvent;
        class LoginEvent {

        public:
            LoginEvent(int m_clientID, std::string t_data);
            //LoginEvent()

            virtual ~LoginEvent();

            std::string getBytes();

        private:
            std::string m_nickname;
            int m_clientID;

        }; // end class

    } // end namespace Event

} // end namespace SnakeServer


#endif //SNAKE_SERVER_LOGINEVENT_H
