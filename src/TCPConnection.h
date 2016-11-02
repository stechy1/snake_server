#ifndef SNAKE_SERVER_TCPCONNECTION_H
#define SNAKE_SERVER_TCPCONNECTION_H

#include <map>
#include <memory>
#include <thread>
#include <sys/select.h>
#include "TCPStream.h"
#include "SingleStreamListenerImpl.h"

namespace SnakeServer {
namespace Network {

const unsigned int BACKLOG = 10; // Maximální počet uživatelů čekajících ve frontě

class IOHandler {
public:
    IOHandler() {}

    virtual ~IOHandler() {}

    virtual void onDataReceived(int socketID, std::vector<std::string> data) = 0;

    virtual void onDisconnect(int socketID) = 0;
};

class IDataSender {
public:
    IDataSender() {}

    virtual ~IDataSender() {}

    virtual void sendData(int socketID, std::string data) = 0;
};

class TCPConnection : public IDataSender {
public:
    TCPConnection(uint16_t t_port, IOHandler &t_ioHandler);

    ~TCPConnection();

    friend class SingleStreamListenerImpl;

    void start();

    void stop();

    void disconnectClient(int socketID);

    virtual void sendData(int socketID, std::string data) override;

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

    IOHandler &m_ioHandler;
    SingleStreamListenerImpl m_streamHandler;

    std::thread m_thread;
    bool m_interupt = true;
    bool m_listening = false;

};

}
}

#endif //SNAKE_SERVER_TCPCONNECTION_H
