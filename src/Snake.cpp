#include <iostream>
#include "Snake.h"

namespace SnakeServer {
namespace GameObject {

Snake::Snake(Vector2D &t_pos, Vector2D &t_dir, const std::string &t_username)
        : m_pos(t_pos), m_dir(t_dir), m_username(t_username) {
    m_vel = Vector2D::ONES();
    m_vel *= VELOCITY_MULTIPLIER;
}

std::string Snake::getDescription() {
    return "SnakeObject";
}

const Vector2D &Snake::getPosition() const {
    return m_pos;
}

void Snake::setPosition(const Vector2D &t_pos) {
    Snake::m_pos = t_pos;
}

const Vector2D &Snake::getDirection() const {
    return m_dir;
}

void Snake::setDirection(const Vector2D &t_dir) {
    Snake::m_dir = t_dir;
}

const Vector2D &Snake::getVelocity() const {
    return m_vel;
}

void Snake::setVelocity(const Vector2D &t_vel) {
    Snake::m_vel = t_vel;
}

int Snake::getSize() const {
    return m_size;
}

void Snake::setSize(int t_size) {
    Snake::m_size = t_size;
}

const std::string &Snake::getUsername() const {
    return m_username;
}

}
}

