#ifndef SNAKE_SERVER_GAMEOBJECT_H
#define SNAKE_SERVER_GAMEOBJECT_H


#include "Vector2D.h"

namespace SnakeServer {

    class BaseObject {

    public:
        virtual BaseObject();
        virtual BaseObject(const Vector2D<double> &t_pos);
        virtual BaseObject(const Vector2D<double> &t_pos, const Vector2D<double> &t_dir, const Vector2D<double> &t_vel);

        const Vector2D<double> m_pos = Vector2D<double>(0, 0);
        const Vector2D<double> m_dir = Vector2D::RIGHT();
        const Vector2D<double> m_vel = Vector2D::ONES();
    private:


    }; // end class
} // end namespace

#endif //SNAKE_SERVER_GAMEOBJECT_H
