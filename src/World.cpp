#include "World.h"

namespace SnakeServer {

World::World(int t_width, int t_height, Network::TCPConnection &t_dataSender)
        : m_width(t_width), m_height(t_height), m_border(0), m_dataSender(t_dataSender) {
    m_border = std::min(m_width, m_height) / 0.7;
}

World::~World() {
    if (m_thread.joinable()) {
        m_thread.join();
    }

    for(auto tmp : m_foodOnMap) {
        delete tmp.second;
    }

    std::cout << "World destruct OK" << std::endl;
}

void World::init() {
    std::cout << "Generuji svět..." << std::endl;
    srand (time(NULL));
    for (int i = 0; i < 10; ++i) {
        addFood(i);
    }

    for(auto &newFood : m_foodToAdd) {
        m_foodOnMap.insert(newFood);
    }
    m_foodToAdd.clear();
}

void World::start() {
    init();
    m_thread = std::thread(&World::run, this);
}

void World::stop() {
    m_interupt = true;
    m_ready = true;
    m_conditionVariable.notify_one();
}

void World::run() {
    double t = 0.0;
    double dt = 0.01;

    auto currentTime = Time::now();
    double accumulator = 0.0;

    while ( !m_interupt ) {

        std::unique_lock<std::mutex> lk(m_mutex);
        m_conditionVariable.wait(lk, [&] {
            currentTime = Time::now();
            return (!m_snakesOnMap.empty() && m_ready) ||
                    (!m_snakesToAdd.empty()) || (m_interupt && m_ready);
        });

        auto newTime = Time::now();
        auto delta = newTime - currentTime;
        using ms = std::chrono::milliseconds;
        double frameTime = std::chrono::duration_cast<ms>(delta).count();
        if (frameTime > 0.25) {
            frameTime = 0.25;
        }
        currentTime = newTime;
        accumulator += frameTime;

        removeGameObjects();

        for(auto &e : m_eventQueue) {
            applySnakeEvent(std::move(e));
        }
        m_eventQueue.clear();

//        while (accumulator >= dt) {
            for(auto &snake : m_snakesOnMap) {
                //snake.second->update(t, dt);
                updateSnake(snake.first, snake.second);
            }
//            t += dt;
//            accumulator -= dt;
//        }

        addGameObjects();

        m_ready = !m_snakesOnMap.empty();

        std::cout << "Loop" << std::endl;
        std::this_thread::sleep_for(2s);
    }
}

void World::removeSnake(int uid) {
    m_snakesToRemove.push_back(uid);
}

std::shared_ptr<GameObject::Snake> World::addSnake(int uid) {
    if (m_snakesToAdd.find(uid) != m_snakesToAdd.end() || m_snakesOnMap.find(uid) != m_snakesOnMap.end()) {
        throw new std::runtime_error("Hrac s timto hadem jiz existuje");
    }
    std::cout << "Přidávám nového hada do hry" << std::endl;
    Vector2D pos = Vector2D::RANDOM(
            -m_width + m_border, -m_height + m_border, m_width - m_border, m_height - m_border);
    Vector2D dir = Vector2D::RANDOM();

    auto snake = std::make_shared<GameObject::Snake>(pos, dir);
    std::pair<int, std::shared_ptr<GameObject::Snake>> pair(uid, snake);
    m_snakesToAdd.insert(pair);

    return snake;
}

GameObject::Food *World::addFood(int id) {
    GameObject::Food *food = new GameObject::Food(id, Vector2D::RANDOM(
            -m_width + m_border, -m_height + m_border, m_width - m_border, m_height - m_border
    ));

    std::pair<int, GameObject::Food*> pair(food->m_uid, food);
    m_foodToAdd.insert(pair);

    return food;
}

void World::removeFood(int uid) {
    m_foodToRemove.push_back(uid);
}

void World::addEvent(std::unique_ptr<InputEvent> event) {
    std::unique_lock<std::mutex> lk(m_mutex);
    if (event->getEventType() == EventType::WORLD) {

        //event->applyChanged(*this);
    } else {
        int id = event->getUserID();
        std::unique_ptr<EventData> myEvent = std::make_unique<EventData>(m_snakesOnMap.at(id), std::move(event));
        m_eventQueue.push_back(std::move(myEvent));
    }
}

void World::sendMessage(int uid, std::string data) {
    m_dataSender.sendData(uid, data);
}

void World::broadcastMessage(int uid, std::string data) {
    for(auto &pair : m_snakesOnMap) {
        if (pair.first == uid) {
            continue;
        }

        std::string msg = "{" + std::to_string(uid) + "}" + data;
        std::cout << "Broadcast: " << msg << std::endl;
        m_dataSender.sendData(pair.first, msg);
    }
}

void World::wakeUp() {
    m_ready = true;
    m_conditionVariable.notify_one();
}

void World::applySnakeEvent(std::unique_ptr<EventData> eventData) {
    auto event = std::move(eventData->event);
    if (dynamic_cast<SnakeChangeDirectionInputEvent*>(*event) != NULL) {
        // Zde budu provádět akce, které se týkají změny směru hada
    }

}

void World::updateSnake(int uid, std::shared_ptr<GameObject::Snake> snake) {
    const Vector2D newPos = (snake->m_dir * snake->m_vel) *= SNAKE_SIZE;
    snake->m_pos+=newPos;
}

void World::addGameObjects() {
    for(auto &newSnake : m_snakesToAdd) {
        m_snakesOnMap.insert(newSnake);
    }
    m_snakesToAdd.clear();

    for(auto &newFood : m_foodToAdd) {
        m_foodOnMap.insert(newFood);
    }
    m_foodToAdd.clear();
}

void World::removeGameObjects() {
    for(int index : m_snakesToRemove) {
        std::cout << "Odebiram hada z mapy s indexem: " << index << std::endl;
        RemoveSnakeOutputEvent event(index);
        broadcastMessage(index, event.getData());
        m_dataSender.disconnectClient(index);
        m_snakesOnMap.erase(index);
    }
    m_snakesToRemove.clear();

    for(int index : m_foodToRemove) {
        m_foodOnMap.erase(index);
    }
    m_foodToRemove.clear();
}

}