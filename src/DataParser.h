#ifndef SNAKE_SERVER_DATAPARSER_H
#define SNAKE_SERVER_DATAPARSER_H

#include <list>
#include <mutex>
#include <condition_variable>
#include "network/TCPConnection.h"

namespace SnakeServer {

    class DataParser : public Network::IOHandler {

    public:
        DataParser(clientsMap_t &t_clients);
        void onReceived(int clientID, std::string data);
        std::thread start();
        void run();
        void shutDown();

        virtual ~DataParser();

    private:

        //typedef std::map<int, std::unique_ptr<std::list<std::string>>> cacheMap;

        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
        bool m_ready;
        bool m_interupt;
        clientsMap_t m_clients;

        //cacheMap m_cache;
    }; // end class

} // end namespace SnakeServer


#endif //SNAKE_SERVER_DATAPARSER_H
