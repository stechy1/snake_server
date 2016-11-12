#ifndef SNAKE_SERVER_TCPSTREAM_H
#define SNAKE_SERVER_TCPSTREAM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <boost/uuid/uuid.hpp>

namespace SnakeServer {
namespace Network {

typedef boost::uuids::uuid uuid;
const unsigned int BUFFER_SIZE = 2048;
const std::string DELIMITER = ";";

class SingleStreamListener {
public:
    SingleStreamListener() {}

    virtual ~SingleStreamListener() {}

    virtual void onDataReceived(int sid, std::vector<std::string> data) = 0;

    virtual void onLostConnection(int sid) = 0;

    virtual void onDisconnect(int sid) = 0;

    virtual void onRestoreConnection(int sid) = 0;
};

enum ConnectionStatus {
    DISCONNECTED, CONNECTED, LOST_CONNECTION
};

class TCPStream {
public:
    friend class Server;

    TCPStream(const int t_sd, const struct sockaddr_in *t_address, SingleStreamListener &listener);

    virtual ~TCPStream();

    void send(std::string data);

    void receive();

    void closeStream();

    const std::string &getIP() const;

    uint16_t getPort() const;

private:
    int m_sd;
    std::string m_peerIP;
    uint16_t m_peerPort;

    ConnectionStatus connectionStatus = DISCONNECTED;

    std::string m_inputBuffer;

    SingleStreamListener &m_listener;
};

}
}

#endif //SNAKE_SERVER_TCPSTREAM_H
