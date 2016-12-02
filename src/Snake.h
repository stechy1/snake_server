#ifndef SNAKE_SERVER_SNAKE_H
#define SNAKE_SERVER_SNAKE_H

#include <list>
#include "Vector2D.h"

namespace SnakeServer {
namespace GameObject {

static const float VELOCITY_MULTIPLIER = 0.5f;
static const int SNAKE_INCREMENT_CONSTANT = 3;

class Snake {
public:
    Snake(Vector2D &t_pos, Vector2D &t_dir, const std::string &t_username);

    void incrementSize();

    std::string getDescription();

    const Vector2D &getPosition() const;

    void setPosition(const Vector2D &t_pos);

    const Vector2D &getDirection() const;

    void setDirection(const Vector2D &t_dir);

    const Vector2D &getVelocity() const;

    void setVelocity(const Vector2D &t_vel);

    int getSize() const;

    void setSize(int t_size);

    const std::string &getUsername() const;

private:
    Vector2D m_pos = Vector2D::ZERO();
    Vector2D m_dir = Vector2D::RIGHT();
    Vector2D m_vel = Vector2D::ONES();
    const std::string m_username;
    int m_size = 25;
    unsigned int m_updateCounter = 0;

};

}
}

#endif //SNAKE_SERVER_SNAKE_H
