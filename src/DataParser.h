#ifndef SNAKE_SERVER_DATAPARSER_H
#define SNAKE_SERVER_DATAPARSER_H

#include <list>
#include <mutex>
#include <condition_variable>
#include "network/TCPConnection.h"
#include "Commons.h"

namespace SnakeServer {

    class DataParser : public Network::IOHandler {

    public:
        DataParser(clientsMap_t *t_clients);
        void onReceived(int clientID, std::string data);
        std::thread start();
        void run();
        void shutDown();

        virtual ~DataParser();

    private:

        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
        bool m_ready = false;
        bool m_interupt = false;
        clientsMap_t *m_clients;

    }; // end class

} // end namespace SnakeServer


#endif //SNAKE_SERVER_DATAPARSER_H
