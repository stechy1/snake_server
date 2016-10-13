#ifndef SNAKE_SERVER_INPUTCOMPONENT_H
#define SNAKE_SERVER_INPUTCOMPONENT_H

#include "IComponent.h"
#include "BaseObject.h"

namespace SnakeServer {

    class InputComponent : IComponent {

        virtual void  handleInput(std::unique_ptr<BaseObject> baseObject) = 0;

    };
}

#endif //SNAKE_SERVER_INPUTCOMPONENT_H
