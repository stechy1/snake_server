#include "SnakeSimplePhysicsComponent.h"
#include "Snake.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

            SnakeSimplePhysicsComponent::SnakeSimplePhysicsComponent() {}

            SnakeSimplePhysicsComponent::~SnakeSimplePhysicsComponent() {}

            void SnakeSimplePhysicsComponent::handlePhysics(std::unique_ptr<BaseObject> &baseObject) {
                //auto snake = static_cast<Snake&>(baseObject.get());
            }

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer