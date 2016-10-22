#ifndef SNAKE_SERVER_BASEOBJECT_H
#define SNAKE_SERVER_BASEOBJECT_H

#include "../Vector2D.h"

namespace SnakeServer {
namespace GameObject {

class BaseObject {
public:
    BaseObject();
    BaseObject(std::unique_ptr<Vector2D> t_pos);
    BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir);
    BaseObject(std::unique_ptr<Vector2D> t_pos, std::unique_ptr<Vector2D> t_dir, std::unique_ptr<Vector2D> t_vel);

    virtual ~BaseObject() {}

    virtual void update(double t, double dt) = 0;

    virtual std::string getDescription();

    std::unique_ptr<Vector2D> m_pos;
    std::unique_ptr<Vector2D> m_dir;
    std::unique_ptr<Vector2D> m_vel;

};

}
}


#endif //SNAKE_SERVER_BASEOBJECT_H
