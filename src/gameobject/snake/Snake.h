#ifndef SNAKE_SNAKE
#define SNAKE_SNAKE


#include "../BaseObject.h"
#include "../../event/GameEvent.h"
#include <list>

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

    class Snake : public BaseObject, public IUpdatable {
    public:
//         Variables
        //const unsigned int size = 1000;
        // Methods
        Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
        std::unique_ptr<InputComponent> t_inputComponent, std::unique_ptr<PhysicsComponent> t_physicsComponent);

        virtual ~Snake();

        void addEvent(std::unique_ptr<Event::GameEvent> t_event);
        void addEvent(Event::GameEvent *t_event);

        virtual void update() override;

//    protected:
        // Variables
        // Methods
    private:
        // Variables
        std::list<std::unique_ptr<Event::GameEvent>> m_events;

        // Methods

    }; // end class

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer

#endif