#include <cstring>
#include <stdexcept>
#include <assert.h>
#include "TCPStream.h"

namespace SnakeServer {
namespace Network {

TCPStream::TCPStream(const int t_sd, const struct sockaddr_in *t_address, SingleStreamListener &t_listener)
        : m_sd(t_sd), m_listener(t_listener) {
    char ip[50];

    connectionStatus = CONNECTED;
    inet_ntop(PF_INET, (struct in_addr *) &(t_address->sin_addr.s_addr), ip, sizeof(ip) - 1);
    m_peerIP = *ip;
    m_peerPort = ntohs(t_address->sin_port);
}

TCPStream::~TCPStream() {}

void TCPStream::send(std::string data) {

    const unsigned long len = data.size();

    ssize_t n = ::send(m_sd, &data, len, 0);

    assert(n == len);

//    if (connectionStatus != CONNECTED) {
//        throw std::runtime_error("Client is not connected");
//    }
//
//    unsigned long count = m_outputBuffer.size();
//    std::string stringBuff;
//    std::list<std::string> bufferCopy = m_outputBuffer;
//    m_outputBuffer.clear();
//
//    for(auto &string : bufferCopy) {
//        stringBuff += string;
//    }
//
//    const char *buff = stringBuff.c_str();
//    m_outputBuffer.clear();
//
//    unsigned long len = strlen(buff);
//
//    int total = 0;
//    unsigned long bytesleft = len;
//    ssize_t n;
//
//    while (total < len) {
//        n = ::send(m_sd, buff+total, bytesleft, 0);
//        if (n == -1) {
//            break;
//            // TODO socket je v háji
//        }
//
//        assert (n == bytesleft);
//
//        total += n;
//        bytesleft -= n;
//    }
//
//    // TODO ošetřit errno v případě, že 'n == -1'
//    return count;
}

void TCPStream::receive() {
    char buff[BUFFER_SIZE];
    ssize_t len = recv(m_sd, buff, BUFFER_SIZE - 1, 0);
    std::string received;
    if (len == 0) {
        // Spojení bylo slušně ukončeno
        connectionStatus = DISCONNECTED;
        m_listener.onDisconnect(m_sd);
        return;
    }
    if (len == -1) {
        if (errno != EWOULDBLOCK) {
            connectionStatus = LOST_CONNECTION;
            m_listener.onLostConnection(m_sd);
            // Spojení bylo ztraceno
            return;
        }

        received = "";
    } else {
        received = std::string(buff, len);
    }

    // Vyzvednout z bufferu dříve přijatá data
    received = m_inputBuffer + received;

    // TODO naparsovat přijatá data, zavolat obslužnou událost, zbytek nezpracovaných dat vložit zpět do bufferu
    // Naparsovat přijatá data
    // Pokud se mi je podaří naparsovat, tak zavolám nějakou obslužnou událost pro zpracování naparsovaných dat
    std::list<std::string> list;
    list.push_back(received);
    m_listener.onDataReceived(m_sd, list);
    // Zbytek nezpracovaných dat vložit do bufferu
    m_inputBuffer = ""; // TODO Dočasné řešení. Vše, co nedokážu naparsovat tak zahodím
}

void TCPStream::closeStream() {
    ::close(m_sd);
}

//void TCPStream::prepareDataToSend(std::string data) {
//    m_outputBuffer.push_back(data);
//}

}
}