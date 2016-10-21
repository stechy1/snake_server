#ifndef SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H
#define SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H

#include "GameEvent.h"
#include "../Vector2D.h"

namespace SnakeServer {

    namespace Event {

        class SnakeChangeDirectionEvent : public GameEvent {

        private:
            const int m_clientID = 0;
            const std::unique_ptr<Vector2D> m_direction;

        public:

            SnakeChangeDirectionEvent(int t_clientID, std::unique_ptr<Vector2D> &t_direction);

            virtual ~SnakeChangeDirectionEvent();

            virtual std::string getBytes() override;

            virtual void applyChanges(IUpdatable *updatable) override;

            virtual std::string getDescription() override;
        };

    }
}

#endif //SNAKE_SERVER_SNAKECHANGEDIRECTIONEVENT_H
