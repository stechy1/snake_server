#include "SnakeSimplePhysicsComponent.h"
#include "Snake.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

            SnakeSimplePhysicsComponent::SnakeSimplePhysicsComponent() {}

            SnakeSimplePhysicsComponent::~SnakeSimplePhysicsComponent() {}

            void SnakeSimplePhysicsComponent::handlePhysics(std::unique_ptr<BaseObject> &baseObject) {
                //auto snake = dynamic_cast<Snake&>(*baseObject);


            }

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer