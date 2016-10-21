#ifndef SNAKE_SERVER_ICOMPONENT_H
#define SNAKE_SERVER_ICOMPONENT_H

#include <memory>

namespace SnakeServer {

    class World;
    class IComponent {

    public:
        virtual ~IComponent() = default;

        //void init(std::unique_ptr<World> &world) {}

    }; // end class

} // end namespace

#endif //SNAKE_SERVER_ICOMPONENT_H
