#include "Snake.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

            Snake::Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
                         std::unique_ptr<InputComponent> t_inputComponent, std::unique_ptr<PhysicsComponent> t_physicsComponent)
                    : BaseObject(t_pos, t_dir, t_inputComponent, t_physicsComponent) {}

            Snake::~Snake() {}

            void Snake::addEvent(std::unique_ptr<Event::GameEvent> t_event) {
                //m_events.push_back(std::move(t_event));
                //m_events.push_back(t_event);
            }

            void Snake::addEvent(Event::GameEvent *t_event) {

            }

            void Snake::update() {
                if (!m_events.empty()) {
                    std::unique_ptr<Event::GameEvent> event = std::move(m_events.front());
                    m_events.pop_front();

                    event->applyChanges(this);
                }
            }

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer