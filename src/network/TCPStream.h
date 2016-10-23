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

class TCPStream {
public:
    friend class TCPConnection;

    TCPStream(const int t_sd, const struct sockaddr_in *t_address);
    virtual ~TCPStream();

    void send();
    void receive();
    void closeStream();

    void prepareDataToSend(std::string data);

private:
    int m_sd;
    std::string m_peerIP;
    uint16_t m_peerPort;

    std::string m_inputBuffer;
    std::string m_outputBuffer;
};

}
}

#endif //SNAKE_SERVER_TCPSTREAM_H
