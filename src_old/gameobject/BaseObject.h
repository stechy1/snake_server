#ifndef SNAKE_SERVER_GAMEOBJECT_H
#define SNAKE_SERVER_GAMEOBJECT_H

#include "../Vector2D.h"
#include "../PhysicsComponent.h"
#include "../InputComponent.h"

namespace SnakeServer {

    namespace GameObject {

        class BaseObject {

        public:
            BaseObject();

            BaseObject(std::unique_ptr<Vector2D> t_pos);

            BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
                               std::unique_ptr<InputComponent> t_inputComponent,
                               std::unique_ptr<PhysicsComponent> t_physicsComponent);

            BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
                               std::unique_ptr<Vector2D> t_vel,
                               std::unique_ptr<InputComponent> t_inputComponent,
                               std::unique_ptr<PhysicsComponent> t_physicsComponent);

            virtual ~BaseObject();

            virtual void update() = 0;

            const std::unique_ptr<Vector2D> m_pos;
            const std::unique_ptr<Vector2D> m_dir;
            const std::unique_ptr<Vector2D> m_vel;

            const std::unique_ptr<InputComponent> m_inputComponent;
            const std::unique_ptr<PhysicsComponent> m_physicsComponent;

        private:


        }; // end class

    } // end namespace GameObject

} // end namespace SnakeServer

#endif //SNAKE_SERVER_GAMEOBJECT_H
