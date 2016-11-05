#include "Food.h"

namespace SnakeServer {
namespace GameObject {

Food::Food(int t_uid, const Vector2D &z_pos)
        : m_pos(z_pos), m_uid(t_uid) {}

}
}