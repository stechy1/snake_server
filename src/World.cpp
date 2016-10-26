#include "World.h"

namespace SnakeServer {

World::World(int t_width, int t_height) : m_width(t_width), m_height(t_height), m_border(0) {
    m_border = std::min(m_width, m_height) / 0.7;
}

World::~World() {
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void World::init() {
    std::cout << "Generuji svět..." << std::endl;
}

void World::start() {
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
            return (!m_snakesOnMap.empty() && m_ready) || (m_interupt && m_ready);
        });

        auto newTime = Time::now();
        fsec delta = newTime - currentTime;
        double frameTime = std::chrono::duration_cast<ms>(delta).count();
        if (frameTime > 0.25)
            frameTime = 0.25;
        currentTime = newTime;
        accumulator += frameTime;

        for(int index : m_snakesToRemove) {
            m_snakesOnMap.erase(index);
        }
        m_snakesToRemove.clear();

        while (accumulator >= dt) {
            for(auto &snake : m_snakesOnMap) {
                snake.second.update(t, dt);
            }
            t += dt;
            accumulator -= dt;
        }

        for(auto &newSnake : m_snakesToAdd) {
            m_snakesOnMap.insert(newSnake);
        }
        m_snakesToAdd.clear();

        m_ready = !m_snakesOnMap.empty();
    }
}

void World::removeSnake(int uid) {
    m_snakesToRemove.push_back(uid);

    m_ready = true;
    m_conditionVariable.notify_one();
}

void World::addSnake(int uid) {
    std::cout << "Přidávám nového hada do hry" << std::endl;
    Vector2D pos = Vector2D::RANDOM(
            -m_width + m_border, -m_height + m_border, m_width - m_border, m_height - m_border);
    Vector2D dir = Vector2D::RANDOM();

    GameObject::Snake::Snake snake(pos, dir);
    std::pair<int, GameObject::Snake::Snake&> pair(uid, snake);
    m_snakesToAdd.insert(pair);

    m_ready = true;
    m_conditionVariable.notify_one();
}

void World::addEvent(Event::BaseEvent &event) {
    if (event.getEventType() == Event::EventType::WORLD) {
        event.applyChanged(*this);
    } else {
        int id = event.getUserID();
        m_snakesOnMap[id].addEvent(event);
    }
}

}