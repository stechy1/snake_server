#ifndef SNAKE_SERVER_INPUTCOMPONENT_H
#define SNAKE_SERVER_INPUTCOMPONENT_H

#include "IComponent.h"

namespace SnakeServer {

    //class BaseObject;
    class InputComponent : public IComponent {

    public:
        virtual ~InputComponent() {}

        virtual void handleInput(const std::unique_ptr<BaseObject> &baseObject) {};

    }; // end class

} // end namespace

#endif //SNAKE_SERVER_INPUTCOMPONENT_H
