#ifndef SNAKE_SERVER_SNAKE_H
#define SNAKE_SERVER_SNAKE_H

#include <list>
#include "Vector2D.h"

namespace SnakeServer {
namespace GameObject {

static const float VELOCITY_MULTIPLIER = 0.7f;

class Snake {
public:
    Snake(Vector2D &t_pos, Vector2D &t_dir);

    std::string getDescription();

    Vector2D m_pos = Vector2D::ZERO();
    Vector2D m_dir = Vector2D::RIGHT();
    Vector2D m_vel = Vector2D::ONES();
    int size = 25;

};

}
}

#endif //SNAKE_SERVER_SNAKE_H
