#include <iostream>
#include "DataParser.h"
#include "event/GameEvent.h"
#include "event/LoginEvent.h"
#include "event/SnakeChangeDirectionEvent.h"

namespace SnakeServer {

    DataParser::DataParser(clientsMap_t *t_clients)
            : m_clients(t_clients) {
        std::cout << "DataParser initialized" << std::endl;
    }

    DataParser::~DataParser() {
        if (thread.joinable()) {
            thread.join();
        }

        std::cout << "DataParser shut down" << std::endl;
    }

    void DataParser::onReceived(int clientID, std::string data) {
        m_clients->find(clientID)->second->cache->push_back(data);

        std::lock_guard<std::mutex> lk(m_mutex);
        m_ready = true;
        m_conditionVariable.notify_one();
    }

    void DataParser::start() {
        std::cout << "Data parsing service running..." << std::endl;
        thread =  std::thread(&DataParser::run, this);
    }

    void DataParser::run() {
        while(!m_interupt) {
            std::cout << "DataParser loop" << std::endl;
            std::unique_lock<std::mutex> lk(m_mutex);
            m_conditionVariable.wait(lk, [&] { return m_ready; });
            std::cout << "DataParser has some data" << std::endl;

            unsigned int notReady = 0;
            for (auto client : *m_clients) {
                if (/*!client.second->ready || */client.second->cache->empty()) {
                    ++notReady;
                    continue;
                }

                std::string data = client.second->cache->front();
                client.second->cache->pop_front();
                std::cout << "Naparsovana data: " << data << std::endl;

                std::unique_ptr<Event::GameEvent> event;
                if (data.find("login:") != std::string::npos) {
                    data = data.substr(6);

                    event = std::make_unique<Event::LoginEvent>(client.first, data);
                } else if (data.find("changedir:") != std::string::npos) {
                    data = data.substr(10);

                    std::vector<std::string> dirData = Utils::split(data, ";");
                    double x = std::stod(dirData[0]);
                    double y = std::stod(dirData[1]);
                    std::unique_ptr<Vector2D> vector = std::make_unique<Vector2D>(x, y);
                    event = std::make_unique<Event::SnakeChangeDirectionEvent>(client.first, vector);
                }

                if (event != nullptr) {
                    std::cout << "Event: " << event->getDescription() << std::endl;
                }
            }

            if (notReady == m_clients->size()) {
                m_ready = false;
            }

            lk.unlock();
        }

        std::cout << "DataParser ended" << std::endl;
    }

    void DataParser::shutDown() {
//        std::lock_guard<std::mutex> lk(m_mutex);
        m_interupt = true;
        m_ready = true;
        m_conditionVariable.notify_one();
    }
}