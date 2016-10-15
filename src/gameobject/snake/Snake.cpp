#include "Snake.h"

namespace SnakeServer {

    namespace GameObject {

        namespace Snake {

            Snake::Snake(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
                         std::unique_ptr<InputComponent> t_inputComponent, std::unique_ptr<PhysicsComponent> t_physicsComponent)
                    : BaseObject(t_pos, t_dir, t_inputComponent, t_physicsComponent) {}

            Snake::~Snake() {}

        } // end namespace Snake

    } // end namespace GameObject

} // end namespace SnakeServer