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
        printf("Generuji svet");
    }

    std::thread World::start() {
        std::cout << "World service running..." << std::endl;
        return std::thread(&World::run, this);
    }

    void World::run() {
        if (running) {
            return;
        }

        running = true;

        long lag = 0;
        auto now = Time::now();
        auto lastTime = now;

        while (running) {
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


            // update logic
            if (!m_clients->empty()) { // Pokud jsou nějací hadi ve světě
                for(clientsMap_t::iterator it = m_clients->begin(); it != m_clients->end(); it++) {
                    //it->second->update();
                    it->second->snake->update();
                }
            }

            if (!m_snakesToAdd.empty()) { // Pokud chci nějaké hady odebrat
                for(snakeMap::iterator it = m_snakesToAdd.begin(); it != m_snakesToAdd.end(); it++) {
//                    auto id = it->first;
//                    auto snake = it->second;

                    //m_clients.insert(std::pair<int, std::unique_ptr<GameObject::Snake::Snake>>(id, std::move(snake)));
//                    (*m_clients)[id]->snake = std::move(snake);
                    (*m_clients)[it->first]->snake = it->second;
                }

                m_snakesToAdd.clear();
            }


        }
    }
}