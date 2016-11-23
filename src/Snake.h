#ifndef SNAKE_SERVER_SNAKE_H
#define SNAKE_SERVER_SNAKE_H

#include <list>
#include "Vector2D.h"

namespace SnakeServer {
namespace GameObject {

static const float VELOCITY_MULTIPLIER = 0.5f;

class Snake {
public:
    Snake(Vector2D &t_pos, Vector2D &t_dir);

    std::string getDescription();

    const Vector2D &getPosition() const;

    void setPosition(const Vector2D &t_pos);

    const Vector2D &getDirection() const;

    void setDirection(const Vector2D &t_dir);

    const Vector2D &getVelocity() const;

    void setVelocity(const Vector2D &t_vel);

    int getSize() const;

    void setSize(int t_size);

    const void incrementCounter();

    const unsigned int getCounterValue();

private:
    Vector2D m_pos = Vector2D::ZERO();
    Vector2D m_dir = Vector2D::RIGHT();
    Vector2D m_vel = Vector2D::ONES();
    int m_size = 25;
    unsigned int m_updateCounter = 0;

};

}
}

#endif //SNAKE_SERVER_SNAKE_H
