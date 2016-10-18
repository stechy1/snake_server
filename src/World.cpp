#include <thread>
#include <iostream>
#include "World.h"

namespace SnakeServer {

    World::World(clientsMap_t *t_clients, const int t_width, const int t_height)
            : m_clients(t_clients), m_width(t_width), m_height(t_height) {
        std::cout << "World initialized" << std::endl;
    }

    World::~World() {}

    void World::generate() {
        std::cout << "Generuji svět" << std::endl;
    }

    std::thread World::start() {
        std::cout << "World service running..." << std::endl;
        return std::thread(&World::run, this);
    }

    void World::run() {
        if (m_running) {
            return;
        }

        m_running = true;

        long lag = 0;
        auto now = Time::now();
        auto lastTime = now;

        while (m_running) {

            std::unique_lock<std::mutex> lk(m_mutex);
            m_conditionVariable.wait(lk, [&] { lastTime = Time::now(); return !m_clients->empty() && m_ready; });

            now = Time::now();
            fsec delta = lastTime - now;
            ms elapsed = std::chrono::duration_cast<ms>(delta);
            lag += elapsed.count();

            if (!m_snakesToRemove.empty()) { // Pokud mám odebrat nějaké hady z mapy
                for (auto removeID : m_snakesToRemove) {
                    m_clients->erase(removeID);
                }

                m_snakesToRemove.clear();
            }

            // handle input from world's event queue

            unsigned int clientCount = 0;
            // update logic
            if (!m_clients->empty()) { // Pokud jsou nějací hadi ve světě
                for(clientsMap_t::iterator it = m_clients->begin(); it != m_clients->end(); it++) {
                    if (it->second->ready) {
                        ++clientCount;
                    } else {
                        it->second->snake->update();
                    }
                }
            }

            if (clientCount == m_clients->size()) {
                m_ready = false;
            }

            clientCount = 0;
            if (!m_snakesToAdd.empty()) { // Pokud chci nějaké hady přidat
                for(auto snake : m_snakesToAdd) {
                    (*m_clients)[snake.first]->snake = snake.second;
                    if ((*m_clients)[snake.first]->ready) {
                        ++clientCount;
                    }
                }

                m_snakesToAdd.clear();
                if (clientCount > 0) {
                    m_ready = true;
                }
            }
        }
    }

    void World::shutDown() {
        m_running = false;
        m_conditionVariable.notify_one(); // Vzbudíme vlákno, pokud nějaké čeká
    }
}