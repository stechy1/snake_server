#ifndef SNAKE_SERVER_PHYSICSCOMPONENT_H
#define SNAKE_SERVER_PHYSICSCOMPONENT_H

#include "IComponent.h"
namespace SnakeServer {

    class BaseObject;
    class PhysicsComponent : public IComponent {

    public:
        virtual void handlePhysics(std::unique_ptr<BaseObject> &baseObject) = 0;

        virtual ~PhysicsComponent() {}

    }; // end class

} // end namespace

#endif //SNAKE_SERVER_PHYSICSCOMPONENT_H
