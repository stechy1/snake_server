#include "BaseObject.h"

namespace SnakeServer {

    namespace GameObject {

        BaseObject::BaseObject()
                : m_pos(Vector2D::RANDOM()) {}

        BaseObject::BaseObject(std::unique_ptr<Vector2D> t_pos)
                : m_pos(std::move(t_pos)) {}

        BaseObject::BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
                std::unique_ptr<InputComponent> t_inputComponent, std::unique_ptr<PhysicsComponent> t_physicsComponent)
                : m_pos(std::move(t_pos)), m_dir(std::move(t_dir)), m_vel(std::move(Vector2D::ONES())),
                  m_inputComponent(std::move(t_inputComponent)), m_physicsComponent(std::move(t_physicsComponent)) {}

        BaseObject::BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
                               std::unique_ptr<Vector2D> t_vel,
                               std::unique_ptr<InputComponent> t_inputComponent,
                               std::unique_ptr<PhysicsComponent> t_physicsComponent)
                : m_pos(std::move(t_pos)), m_dir(std::move(t_dir)), m_vel(std::move(t_vel)),
                  m_inputComponent(std::move(t_inputComponent)), m_physicsComponent(std::move(t_physicsComponent)) {}

        BaseObject::~BaseObject() {}

    } // end namespace GameObject

} // end namespace SnakeServer
