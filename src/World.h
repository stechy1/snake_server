#ifndef SNAKE_SERVER_WORLD_H
#define SNAKE_SERVER_WORLD_H

#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include "Snake.h"
#include "TCPConnection.h"
#include "Food.h"

namespace SnakeServer {

using namespace std::chrono_literals;

static const unsigned int SNAKE_SIZE = 15;

class World : public Event::IUpdatable {
public:
    World(int t_width, int t_height, Network::TCPConnection &t_dataSender);
    ~World();

    void init();
    void start();
    void stop();
    void wakeUp();

    GameObject::Snake *addSnake(int uid);
    void removeSnake(int uid);

    GameObject::Food *addFood(int id);
    void removeFood(int uid);

    void addEvent(Event::BaseEvent *event);
    void sendMessage(int uid, std::string data);
    void broadcastMessage(int uid, std::string data);

    int m_width = 0;
    int m_height = 0;
    double m_border = 0;
    std::map<int, GameObject::Snake*> m_snakesOnMap;
    std::map<int, GameObject::Food*> m_foodOnMap;

private:
    void run();
    void updateSnake(int uid, GameObject::Snake &snake);

    void addGameObjects();
    void removeGameObjects();

    Network::TCPConnection &m_dataSender;

    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;

    std::map<int, GameObject::Snake*> m_snakesToAdd;
    std::map<int, GameObject::Food*> m_foodToAdd;
    std::list<int> m_snakesToRemove;
    std::list<int> m_foodToRemove;

    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
    std::thread m_thread;
    bool m_interupt = false;
    bool m_ready = false;
};

}

#endif //SNAKE_SERVER_WORLD_H
