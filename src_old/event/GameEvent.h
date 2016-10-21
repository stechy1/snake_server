#ifndef SNAKE_SERVER_GAMEEVENT_H
#define SNAKE_SERVER_GAMEEVENT_H

#include <memory>
#include "../IUpdatable.h"

namespace SnakeServer {

    namespace Event {

        class GameEvent {

        public:

            GameEvent() {};

            virtual ~GameEvent() {};

            virtual std::string getBytes()= 0;

            virtual void applyChanges(IUpdatable *updatable) = 0;

            virtual std::string getDescription()= 0;
//            static std::unique_ptr<GameEvent> from(std::string bytes, int clientID) {
//                auto type = bytes.at(0);
//                return std::make_unique<LoginEvent>(clientID, bytes);
//                switch (type) {
//                    case 0:
//                        return std::make_unique<LoginEvent>(clientID, bytes);
//                    default:
//                        return nullptr;
//                }
//            }

        }; // end class

    } // end namespace Event

} // end namespace SnakeServer


#endif //SNAKE_SERVER_GAMEEVENT_H
