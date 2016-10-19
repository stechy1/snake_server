#include "SnakeChangeDirectionEvent.h"
#include "../gameobject/snake/Snake.h"

namespace SnakeServer {

    namespace Event {

        SnakeChangeDirectionEvent::SnakeChangeDirectionEvent(int t_clientID, std::unique_ptr<Vector2D> &t_direction)
                : m_clientID(t_clientID), m_direction(std::move(t_direction)) {}

        SnakeChangeDirectionEvent::~SnakeChangeDirectionEvent() {}

        std::string SnakeChangeDirectionEvent::getBytes() {
            return "";
        }

        std::string SnakeChangeDirectionEvent::getDescription() {
            return "SnakeChangeDirectionEvent";
        }

        void SnakeChangeDirectionEvent::applyChanges(IUpdatable *updatable) {
            GameObject::Snake::Snake *snake = static_cast<GameObject::Snake::Snake*>(updatable);

            snake->m_dir->set(*m_direction.get());
        }

    } // end namespace Event

} // end namespace SnakeServer


