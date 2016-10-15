//
// Created by stech on 12.10.2016.
//

#ifndef SNAKE_SERVER_ICOMPONENT_H
#define SNAKE_SERVER_ICOMPONENT_H

#include <memory>
#include "World.h"

namespace SnakeServer {

    class IComponent {

    public:
        virtual void init(std::unique_ptr<World> world) = 0;

        virtual ~IComponent() {};

    }; // end class

} // end namespace

#endif //SNAKE_SERVER_ICOMPONENT_H
