#include "BaseObject.h"

namespace SnakeServer {

    BaseObject::BaseObject()
            : m_pos(Vector2D::RANDOM()) {}

    BaseObject::BaseObject(const Vector2D<double> &t_pos)
            : m_pos(t_pos) {}

    BaseObject::BaseObject(const Vector2D<double> &t_pos, const Vector2D<double> &t_dir,
                           const Vector2D<double> &t_vel)
            : m_pos(t_pos), m_dir(t_dir), m_vel(t_vel) {}


}
