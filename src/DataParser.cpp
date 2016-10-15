#include "DataParser.h"

namespace SnakeServer {

    DataParser::DataParser(clientsMap_t &t_clients)
            : m_clients(t_clients) {
        printf("DataParser initialized");
    }

    DataParser::~DataParser() {}

    void DataParser::onReceived(int clientID, std::string data) {
        m_clients.find(clientID)->second->cache->push_back(data);
//        cache->push_back(data);
//        if (m_cache.find(clientID) != m_cache.end()) { // Pokud už existuje klient v cachi
//            m_cache[clientID]->push_back(data);
//        } else { // Pokud klient ještě nemá záznam v cache, tak jej vytvořím
//            std::unique_ptr<std::list<std::string>> cache(new std::list<std::string>);// = std::make_unique<std::list<std::string>>>();
//            m_cache.insert(std::pair<int, std::unique_ptr<std::list<std::string>>>(clientID, std::move(cache)));
//        }

        std::lock_guard<std::mutex> lk(m_mutex);
        m_ready = true;
        m_conditionVariable.notify_one();
    }

    std::thread DataParser::start() {
        return std::thread(&DataParser::run, this);
    }

    void DataParser::run() {
        while(!m_interupt) {
            std::unique_lock<std::mutex> lk(m_mutex);
            m_conditionVariable.wait(lk, [&] { return m_ready; });

            for (auto client : m_clients) {
                if (client.second->cache->empty()) {
                    continue;
                }


            }
//            for(clientsMap_titerator it = m_cache.begin(); it != m_cache.end(); it++) {
//                if (it->second->empty()) {
//                    continue;
//                }
//
//
//            }
        }
    }

    void DataParser::shutDown() {
        m_interupt = true;
    }
}