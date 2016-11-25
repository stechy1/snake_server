#include "Food.h"

namespace SnakeServer {
namespace GameObject {

Food::Food(int t_uid, const Vector2D &z_pos)
        : m_pos(z_pos), m_uid(t_uid) {}

    const Vector2D &Food::getPosition() const {
        return m_pos;
    }

    const int Food::getUid() const {
        return m_uid;
    }

}
}