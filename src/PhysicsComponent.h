#ifndef SNAKE_SERVER_PHYSICSCOMPONENT_H
#define SNAKE_SERVER_PHYSICSCOMPONENT_H

#include "IComponent.h"

namespace SnakeServer {

    class BaseObject;
    class PhysicsComponent : public IComponent {

    public:
        virtual ~PhysicsComponent() {}

        virtual void handlePhysics(const std::unique_ptr<BaseObject> &baseObject) {};

    }; // end class

} // end namespace

#endif //SNAKE_SERVER_PHYSICSCOMPONENT_H
