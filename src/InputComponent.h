#ifndef SNAKE_SERVER_INPUTCOMPONENT_H
#define SNAKE_SERVER_INPUTCOMPONENT_H

#include "IComponent.h"

namespace SnakeServer {

    class BaseObject;
    class InputComponent : public IComponent {

    public:
        virtual void handleInput(std::unique_ptr<BaseObject> &baseObject) = 0;

        virtual ~InputComponent() {}
    };
}

#endif //SNAKE_SERVER_INPUTCOMPONENT_H
