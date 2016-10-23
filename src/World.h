#ifndef SNAKE_SERVER_WORLD_H
#define SNAKE_SERVER_WORLD_H

#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "gameobject/snake/Snake.h"

namespace SnakeServer {

class World {
public:
    World(int t_width, int t_height);
    ~World();

    void init();
    void start();
    void stop();

    void addSnake(int uid);
    void removeSnake(int uid);

private:
    void run();

    int m_width = 0;
    int m_height = 0;
    double m_border = 0;

    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;

    std::map<int, GameObject::Snake::Snake&> m_snakesOnMap;
    std::map<int, GameObject::Snake::Snake&> m_snakesToAdd;
    std::list<int> m_snakesToRemove;

    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
    std::thread m_thread;
    bool m_interupt = false;
    bool m_ready = false;
};

}

#endif //SNAKE_SERVER_WORLD_H
