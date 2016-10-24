#ifndef SNAKE_SERVER_TCPSTREAM_H
#define SNAKE_SERVER_TCPSTREAM_H

#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

namespace SnakeServer {
namespace Network {

    const unsigned int BUFFER_SIZE = 2048;

class SingleStreamListener {
public:
    SingleStreamListener() {}
    virtual ~SingleStreamListener() {}

    virtual void onDataReceived(int socketID, std::list<std::string> data) = 0;
    virtual void onLostConnection(int socketID) = 0;
    virtual void onDisconnect(int socketID) = 0;
    virtual void onRestoreConnection(int socketID) = 0;
};

enum ConnectionStatus {
    DISCONNECTED, CONNECTED, LOST_CONNECTION
};

class TCPStream {
public:
    friend class TCPConnection;

    TCPStream(const int t_sd, const struct sockaddr_in *t_address, SingleStreamListener &listener);
    virtual ~TCPStream();

    unsigned long send();
    void receive();
    void closeStream();

    void prepareDataToSend(std::string data);

private:
    int m_sd;
    std::string m_peerIP;
    uint16_t m_peerPort;

    ConnectionStatus connectionStatus = DISCONNECTED;

    std::string m_inputBuffer;
    std::list<std::string> m_outputBuffer;

    SingleStreamListener &m_listener;
};

}
}

#endif //SNAKE_SERVER_TCPSTREAM_H
