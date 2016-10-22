#include "BaseObject.h"

namespace SnakeServer {
namespace GameObject {

BaseObject::BaseObject() {
    m_pos = std::make_unique<Vector2D>(Vector2D::ZERO());
    m_dir = std::make_unique<Vector2D>(Vector2D::ZERO());
    m_vel = std::make_unique<Vector2D>(Vector2D::ZERO());
}

BaseObject::BaseObject(std::unique_ptr<Vector2D> t_pos) : m_pos(std::move(t_pos)) {
    m_dir = std::make_unique<Vector2D>(Vector2D::ZERO());
    m_vel = std::make_unique<Vector2D>(Vector2D::ZERO());

}

BaseObject::BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir) : m_pos(std::move(t_pos)), m_dir(std::move(t_dir)) {
    m_vel = std::make_unique<Vector2D>(Vector2D::ZERO());
}

BaseObject::BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir,
                       std::unique_ptr<Vector2D> t_vel) : m_pos(std::move(t_pos)), m_dir(std::move(t_dir)), m_vel(std::move(t_vel)) {}

std::string BaseObject::getDescription() {
    return "BaseObject";
}

}
}
