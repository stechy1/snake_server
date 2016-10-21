#ifndef SNAKE_SERVER_SNAKESIMPLEINPUTCOMPONENT_H
#define SNAKE_SERVER_SNAKESIMPLEINPUTCOMPONENT_H


#include "../BaseObject.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

            class SnakeSimpleInputComponent : public InputComponent {
            public:
                SnakeSimpleInputComponent();

                ~SnakeSimpleInputComponent();

                virtual void handleInput(const std::unique_ptr<BaseObject> &baseObject);

            }; // end class

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer


#endif //SNAKE_SERVER_SNAKESIMPLEINPUTCOMPONENT_H
