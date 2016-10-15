#ifndef SNAKE_SERVER_SNAKESIMPLEPHYSICSCOMPONENT_H
#define SNAKE_SERVER_SNAKESIMPLEPHYSICSCOMPONENT_H

#include "../BaseObject.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

            class SnakeSimplePhysicsComponent : public PhysicsComponent {
            public:
                SnakeSimplePhysicsComponent();

                ~SnakeSimplePhysicsComponent();

                virtual void handlePhysics(std::unique_ptr<BaseObject> &baseObject) override ;
            }; // end class

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer


#endif //SNAKE_SERVER_SNAKESIMPLEPHYSICSCOMPONENT_H
