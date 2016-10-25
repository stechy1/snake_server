#include "BaseObject.h"

namespace SnakeServer {
namespace GameObject {

BaseObject::BaseObject() {
    m_pos = Vector2D::ZERO();
    m_dir = Vector2D::ZERO();
    m_vel = Vector2D::ZERO();
}

BaseObject::BaseObject(Vector2D &t_pos) : m_pos(t_pos) {
    m_dir = Vector2D::ZERO();
    m_vel = Vector2D::ZERO();
}

BaseObject::BaseObject(Vector2D &t_pos, Vector2D &t_dir) : m_pos(t_pos), m_dir(t_dir) {
    m_vel = Vector2D::ZERO();
}

BaseObject::BaseObject(Vector2D &t_pos, Vector2D &t_dir, Vector2D &t_vel) : m_pos(t_pos), m_dir(t_dir), m_vel(t_vel) {}


std::string BaseObject::getDescription() {
    return "BaseObject";
}

}
}
