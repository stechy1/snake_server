#ifndef SNAKE_SERVER_FOOD_H
#define SNAKE_SERVER_FOOD_H

#include "Vector2D.h"

namespace SnakeServer {
namespace GameObject {
class Food {
public:

    Food(int t_uid, const Vector2D &m_pos);

    const Vector2D &getPosition() const;

    const int getUid() const;

private:
    Vector2D m_pos = Vector2D::ZERO();
    const int m_uid = -1;
};

}
}


#endif //SNAKE_SERVER_FOOD_H
