#ifndef SNAKE_SNAKE
#define SNAKE_SNAKE


#include "../BaseObject.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

    class Snake : public BaseObject {
    public:
//         Variables
        //const unsigned int size = 1000;
        // Methods
        Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
        std::unique_ptr<InputComponent> t_inputComponent, std::unique_ptr<PhysicsComponent> t_physicsComponent);

        virtual ~Snake();


//    protected:
        // Variables
        // Methods
//    private:
        // Variables


        // Methods

    }; // end class

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer

#endif