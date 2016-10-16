#ifndef SNAKE_WORLD
#define SNAKE_WORLD

#include <chrono>
#include <map>
#include <list>
#include "gameobject/BaseObject.h"
#include "gameobject/snake/Snake.h"
#include "event/GameEvent.h"
#include "Client.h"

namespace SnakeServer {

    class World {
    public:
        // Variables
        // Methods
        World(clientsMap_t *t_clients, const int t_width, const int t_height);

        virtual ~World();

        void generate(); // Vygeneruje novou mapu
        void addSnake(int i, std::unique_ptr<GameObject::Snake::Snake> &snake); // Přidá hada do mapy
        void removeSnake(int i); // Odebere hada z mapy
        std::thread start();
        void run();

    protected:
        // Variables
        // Methods
    private:
        // Variables
        clientsMap_t *m_clients;

        typedef std::chrono::high_resolution_clock Time;
        typedef std::chrono::milliseconds ms;
        typedef std::chrono::duration<float> fsec;
        typedef std::map<int, std::shared_ptr<GameObject::Snake::Snake>> snakeMap;

        const int m_width = 600;
        const int m_height = 600;
        bool running = false;


        //snakeMap m_snakes;                  // Mapa všech právě připojených hadů
        std::vector<int> m_snakesToRemove;  // Kolekce id všech hadů, kterí chtějí opustit mapu
        snakeMap m_snakesToAdd;              // Mapa všech hadů, kterí se připojují do mapy

        std::list<Event::GameEvent> gameEvent;

        // Methods

    }; // end class

}// end namespace

#endif