#ifndef SNAKE_SERVER_BASEOBJECT_H
#define SNAKE_SERVER_BASEOBJECT_H

#include "../Vector2D.h"

namespace SnakeServer {
namespace GameObject {

class BaseObject {
public:
    BaseObject();
    BaseObject(Vector2D &t_pos);
    BaseObject(Vector2D &t_pos, Vector2D &t_dir);
    BaseObject(Vector2D &t_pos, Vector2D &t_dir, Vector2D &t_vel);

    virtual ~BaseObject() {}

    virtual void update(double t, double dt) = 0;

    virtual std::string getDescription();

    Vector2D m_pos = Vector2D::ZERO();
    Vector2D m_dir;
    Vector2D m_vel;

};

}
}


#endif //SNAKE_SERVER_BASEOBJECT_H
