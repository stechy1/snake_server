#include "SnakeSimpleInputComponent.h"
#include "Snake.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

            SnakeSimpleInputComponent::SnakeSimpleInputComponent() {}

            void SnakeSimpleInputComponent::handleInput(std::unique_ptr<BaseObject> &baseObject) {
                //auto snake = dynamic_cast<Snake&>(*baseObject);


            }

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer