#ifndef SNAKE_SERVER_PHYSICSCOMPONENT_H
#define SNAKE_SERVER_PHYSICSCOMPONENT_H

#include "IComponent.h"
#include "BaseObject.h"

namespace SnakeServer {

    class PhysicsComponent : IComponent {

        virtual void handlePhysics(std::unique_ptr<BaseObject> baseObject) = 0;

    }; // end class

} // end namespace

#endif //SNAKE_SERVER_PHYSICSCOMPONENT_H
