#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "World.h"

namespace SnakeServer {

World::World(int t_width, int t_height, Network::Server &t_dataSender)
        : m_width(t_width), m_height(t_height), m_dataSender(t_dataSender) {
    m_border = std::min(m_width, m_height) / BORDER_MULTIPLIER;
}

World::~World() {
    if (m_thread.joinable()) {
        m_thread.join();
    }

    std::cout << "World destruct OK" << std::endl;
}

void World::init() {
    std::cout << "Generuji svět..." << std::endl;
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        addFood(i);
    }

    for (auto &newFood : m_foodToAdd) {
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
    m_conditionVariable.notify_one();
}

void World::run() {
    double t = 0.0;
    double dt = 0.01;

    auto currentTime = Time::now();
    double accumulator = 0.0;

    while (!m_interupt) {
        std::unique_lock<std::mutex> lk(m_mutex);

        auto newTime = Time::now();
        auto delta = newTime - currentTime;
        using ms = std::chrono::milliseconds;
        double frameTime = std::chrono::duration_cast<ms>(delta).count();
        if (frameTime > UPS) {
            frameTime = UPS;
        }
        currentTime = newTime;
        accumulator += frameTime;

        removeGameObjects();

        for (auto &event : m_eventQueue) {
            applySnakeEvent(std::move(event));
        }
        m_eventQueue.clear();

        int x = 0;
        while (accumulator >= dt) {
            for (auto &item : m_snakesOnMap) {
                auto snake = item.second;
                updateSnake(snake);
                if (snake->getCounterValue() % UPDATE_PERIOD == 0) {
                    SyncOutputEvent syncEvent(m_snakesOnMap);
                    sendMessage(item.first, syncEvent.getData());
                }
            }
            t += dt;
            accumulator -= dt;
            x++;
        }

        addGameObjects();

        std::this_thread::sleep_for(ms(100-(int)(frameTime*100)));
    }
}

void World::removeSnake(uuid clientID) {
    m_snakesToRemove.push_back(clientID);
}

std::shared_ptr<GameObject::Snake> World::addSnake(uuid clientID) {
    if (m_snakesToAdd.find(clientID) != m_snakesToAdd.end() || m_snakesOnMap.find(clientID) != m_snakesOnMap.end()) {
        throw new std::runtime_error("Hrac s timto hadem jiz existuje");
    }
    std::cout << "Přidávám nového hada do hry" << std::endl;
    Vector2D pos = Vector2D::RANDOM(
            -m_width + m_border, -m_height + m_border, m_width - m_border, m_height - m_border);
    Vector2D dir = Vector2D::RIGHT();

    auto snake = std::make_shared<GameObject::Snake>(pos, dir);
    std::pair<uuid, std::shared_ptr<GameObject::Snake>> pair(clientID, snake);
    m_snakesToAdd.insert(pair);

    return snake;
}

std::shared_ptr<GameObject::Food> World::addFood(int id) {
    std::shared_ptr<GameObject::Food> food = std::make_shared<GameObject::Food>(id, Vector2D::RANDOM(
            -m_width + m_border, -m_height + m_border, m_width - m_border, m_height - m_border
    ));

    std::pair<int, std::shared_ptr<GameObject::Food>> pair(food->m_uid, food);
    m_foodToAdd.insert(pair);

    return food;
}

void World::removeFood(int id) {
    m_foodToRemove.push_back(id);
}

void World::addEvent(std::unique_ptr<InputEvent> event) {
    std::unique_lock<std::mutex> lk(m_mutex);
    switch (event->getEventType()) {
        case EventType::LOGIN: {
            uuid clientID = event->getUserID();
            auto newSnake = addSnake(clientID);
            InitOutputEvent initOutputEvent(clientID, newSnake, m_width, m_height, m_snakesOnMap, m_foodOnMap);
            AddSnakeOutputEvent addSnakeOutputEvent(clientID, newSnake);
            sendMessage(clientID, initOutputEvent.getData());
            broadcastMessage(clientID, addSnakeOutputEvent.getData());
            break;
        }
        case EventType::LOGOUT: {
            removeSnake(event->getUserID());
            break;
        }
        default: {
            auto id = event->getUserID();
            if (m_snakesOnMap.find(id) == m_snakesOnMap.end()) {
                return;
            }

            std::unique_ptr<EventData> myEvent = std::make_unique<EventData>(m_snakesOnMap.at(id), std::move(event));
            m_eventQueue.push_back(std::move(myEvent));
        }
    }
}

void World::sendMessage(uuid clientID, std::string data) {
    std::string msg = "(" + boost::uuids::to_string(clientID) + ")" + data;
    m_dataSender.sendData(clientID, msg);
}

void World::broadcastMessage(uuid clientID, std::string data) {
    for (auto &pair : m_snakesOnMap) {
        if (pair.first == clientID) {
            continue;
        }

        sendMessage(pair.first, data);
    }
}

void World::applySnakeEvent(std::unique_ptr<EventData> eventData) {
    auto snake = eventData->snake;
    auto event = std::move(eventData->event);
    auto e = &(*event);
    switch (event->getEventType()) {
        case EventType::CHANGE_DIR: {
            uuid clientID = event->getUserID();
            auto snakeChangeDirection = static_cast<SnakeChangeDirectionInputEvent *>(e);
            snake->setDirection(snakeChangeDirection->getDirection());
            SnakeChangeDirectionOutputEvent outputEvent(clientID, snakeChangeDirection->getDirection());
            broadcastMessage(clientID, outputEvent.getData());
            break;
        }
        default:
            std::cout << "Nebyl rozpoznan typ eventu" << std::endl;
    }
}

void World::updateSnake(std::shared_ptr<GameObject::Snake> snake) {
    Vector2D direction = snake->getDirection();
    Vector2D velocity = snake->getVelocity();
    Vector2D position = snake->getPosition();
    const Vector2D newPos = position + ((direction * velocity) *= SNAKE_SIZE);
    snake->setPosition(newPos);

    if (snake->getPosition().X() > m_width) {
        snake->setPosition(Vector2D(-m_width, position.Y()));
    }
    if (snake->getPosition().X() < -m_width) {
        snake->setPosition(Vector2D(m_width, position.Y()));
    }
    if (snake->getPosition().Y() > m_height) {
        snake->setPosition(Vector2D(position.X(), -m_height));
    }
    if (snake->getPosition().Y() < -m_height) {
        snake->setPosition(Vector2D(position.X(), m_height));
    }

    snake->incrementCounter();
}

void World::addGameObjects() {
    for (auto &newSnake : m_snakesToAdd) {
        m_snakesOnMap.insert(newSnake);
    }
    m_snakesToAdd.clear();

    for (auto &newFood : m_foodToAdd) {
        m_foodOnMap.insert(newFood);
    }
    m_foodToAdd.clear();
}

void World::removeGameObjects() {
    for (auto index : m_snakesToRemove) {
        RemoveSnakeOutputEvent event(index);
        broadcastMessage(index, event.getData());
        auto erased = m_snakesOnMap.erase(index);
        if (erased > 0) {
            std::string uid = boost::lexical_cast<std::string>(index);
            std::cout << "Odebiram hada z mapy s indexem: " << uid << std::endl;
        }
    }
    m_snakesToRemove.clear();

    for (int index : m_foodToRemove) {
        m_foodOnMap.erase(index);
    }
    m_foodToRemove.clear();
}

}