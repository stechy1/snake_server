#ifndef SNAKE_SERVER_TCPCONNECTION_H
#define SNAKE_SERVER_TCPCONNECTION_H

#include <map>
#include <memory>
#include <thread>
#include <sys/select.h>
#include "TCPStream.h"

namespace SnakeServer {
namespace Network {

const unsigned int BACKLOG = 10; // Maximální počet uživatelů čekajících ve frontě


class TCPConnection : public SingleStreamListener {
public:
    TCPConnection();
    ~TCPConnection();

    void init();
    void start();
    void run();
    void stop();

    virtual void onDataReceived(int socketID, std::list<std::string> data) override;
    virtual void onLostConnection(int socketID) override;
    virtual void onDisconnect(int socketID) override;
    virtual void onRestoreConnection(int socketID) override;

protected:
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

    std::thread m_thread;
    bool m_interupt = true;
    bool m_listening = false;

};

}
}

#endif //SNAKE_SERVER_TCPCONNECTION_H
