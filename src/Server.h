#ifndef SNAKE_SERVER_TCPCONNECTION_H
#define SNAKE_SERVER_TCPCONNECTION_H

#include <map>
#include <memory>
#include <thread>
#include <sys/select.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "TCPStream.h"
#include "SingleStreamListenerImpl.h"

namespace SnakeServer {
namespace Network {

typedef boost::uuids::uuid uuid;

const unsigned int BACKLOG = 10; // Maximální počet uživatelů čekajících ve frontě

class IOHandler {
public:
    IOHandler() {}

    virtual ~IOHandler() {}

    virtual void onDataReceived(const uuid &clientID, const std::vector<std::string> data) const = 0;

    virtual void onDisconnect(const uuid &clientID) const = 0;
};

class IDataSender {
public:
    IDataSender() {}

    virtual ~IDataSender() {}

    virtual void sendData(const uuid &clientID, const std::string &data) = 0;
};

class Server : public IDataSender {
public:
    Server(const uint16_t t_port, const IOHandler &t_ioHandler, const uuid &t_seed);

    ~Server();

    friend class SingleStreamListenerImpl;

    void start();

    void stop();

    void disconnectClient(const uuid &clientID);

    virtual void sendData(const uuid &clientID, const std::string &data) override;

protected:
    void init();

    void run();

    void accept();

private:

    int m_lsd = -1; // Listen socket descriptor
    uint16_t m_port = 0;

    fd_set m_master_read_fds;  // Master file descriptor list for read events
    fd_set m_master_write_fds; // Master file descriptor list for write events
    fd_set m_read_fds;         // File descriptor list for read events
    fd_set m_write_fds;        // File descriptor list for write events
    int m_fdMax = 0;     // Nejmenší index socket file descriptoru
    int m_fdMin = 0;     // Největší index socket file descriptoru

    int m_pipefd[2] = {0, 0}; // Pipe pro interní komunikaci

    std::map<int, std::unique_ptr<TCPStream>> m_clients;
    std::map<uuid, int> m_clients_reference;
    boost::uuids::name_generator m_uuid_generator;

    const IOHandler &m_ioHandler;
    SingleStreamListenerImpl m_streamHandler;

    std::thread m_thread;
    bool m_interupt = true;
    bool m_listening = false;

};

}
}

#endif //SNAKE_SERVER_TCPCONNECTION_H
