#include <iostream>
#include "DataParser.h"

namespace SnakeServer {

    DataParser::DataParser(clientsMap_t *t_clients)
            : m_clients(t_clients) {
//        printf("DataParser initialized\n");
        std::cout << "DataParser initialized" << std::endl;
    }

    DataParser::~DataParser() {}

    void DataParser::onReceived(int clientID, std::string data) {
        m_clients->find(clientID)->second->cache->push_back(data);

        std::lock_guard<std::mutex> lk(m_mutex);
        m_ready = true;
        m_conditionVariable.notify_one();
    }

    std::thread DataParser::start() {
        printf("Data parsing service running...\n");
        return std::thread(&DataParser::run, this);
    }

    void DataParser::run() {
        while(!m_interupt) {
            std::cout << "DataParser loop" << std::endl;
            std::unique_lock<std::mutex> lk(m_mutex);
            m_conditionVariable.wait(lk, [&] { return m_ready; });
            std::cout << "DataParser has some data" << std::endl;

            int notReady = 0;
            for (auto client : *m_clients) {
                if (!client.second->ready || client.second->cache->empty()) {
                    ++notReady;
                    continue;
                }

                std::string data = client.second->cache->front();
                client.second->cache->pop_front();
                std::cout << "Naparsovana data: " << data << std::endl;
            }

            if (notReady == m_clients->size()) {
                m_ready = false;
            }
        }
    }

    void DataParser::shutDown() {
        m_interupt = true;
    }
}