#include <iostream>
#include "Snake.h"

namespace SnakeServer {
namespace GameObject {

Snake::Snake(Vector2D &t_pos, Vector2D &t_dir)
        : m_pos(t_pos), m_dir(t_dir) {
    m_vel = Vector2D::ONES();
    m_vel *= VELOCITY_MULTIPLIER;
}

std::string Snake::getDescription() {
    return "SnakeObject";
}

}
}

