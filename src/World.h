#ifndef SNAKE_SERVER_WORLD_H
#define SNAKE_SERVER_WORLD_H

#include <thread>
#include <map>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <boost/uuid/uuid.hpp>
#include "Snake.h"
#include "Server.h"
#include "Food.h"
#include "Event.h"

namespace SnakeServer {

typedef boost::uuids::uuid uuid;
using namespace std::chrono_literals;

static const double BORDER_MULTIPLIER = 0.7;
static const unsigned int SNAKE_SIZE = 15;
static const double UPS = 0.25;
static const int UPDATE_PERIOD = 300; // TODO najít optimální hodnotu

struct EventData {
    std::shared_ptr<GameObject::Snake> snake;
    std::unique_ptr<InputEvent> event;

    EventData(std::shared_ptr<GameObject::Snake> t_snake, std::unique_ptr<InputEvent> t_event)
            : snake(t_snake),
              event(std::move(
                      t_event)) {}

    EventData(EventData &&other)
            : snake(other.snake), event(std::move(other.event)) {}

    EventData &operator=(EventData &&other) {
        snake = other.snake;
        event = std::move(other.event);
        return *this;
    }

    EventData(const EventData &) = delete;

    EventData &operator=(const EventData &) = delete;

    ~EventData() = default;
};

class World {
public:
    World(int t_width, int t_height, Network::Server &t_dataSender);

    ~World();

    void start();

    void stop();

    std::shared_ptr<GameObject::Snake> addSnake(uuid clientID);

    void removeSnake(uuid clientID);

    std::shared_ptr<GameObject::Food> addFood(int id);

    void removeFood(int id);

    void addEvent(std::unique_ptr<InputEvent> event);

    void sendMessage(uuid clientID, std::string data);

    void broadcastMessage(uuid clientID, std::string data);

    int m_width = 0;
    int m_height = 0;
    double m_border = 0;
    std::map<uuid, std::shared_ptr<GameObject::Snake>> m_snakesOnMap;
    std::map<int, std::shared_ptr<GameObject::Food>> m_foodOnMap;

private:
    void init();

    void run();

    void applySnakeEvent(std::unique_ptr<EventData> eventData);

    void updateSnake(std::shared_ptr<GameObject::Snake> snake);

    void addGameObjects();

    void removeGameObjects();

    Network::Server &m_dataSender;

    typedef std::chrono::high_resolution_clock Time;

    std::map<uuid, std::shared_ptr<GameObject::Snake>> m_snakesToAdd;
    std::map<int, std::shared_ptr<GameObject::Food>> m_foodToAdd;
    std::vector<uuid> m_snakesToRemove;
    std::vector<int> m_foodToRemove;
    std::vector<std::unique_ptr<EventData>> m_eventQueue; // Hlavní event queue pro objekty na mapě

    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
    std::thread m_thread;
    bool m_interupt = false;
};

}

#endif //SNAKE_SERVER_WORLD_H
