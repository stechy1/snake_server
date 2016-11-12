#include <cstring>
#include <stdexcept>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include "TCPStream.h"

namespace SnakeServer {
namespace Network {

inline std::string &ltrim(std::string &s, const char *t = " \t\n\r\f\v") {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

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
    const char *buff = data.c_str();

    ssize_t n = ::send(m_sd, buff, len, 0);

    assert(n == len);
}

void TCPStream::receive() {
    char buff[BUFFER_SIZE];
    ssize_t len = recv(m_sd, buff, BUFFER_SIZE - 1, 0);
    std::string received;
    if (len == 0) {
        // Spojení bylo slušně ukončeno
        connectionStatus = DISCONNECTED;
        m_listener.onDisconnect(m_sd);
        closeStream();
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
    received = m_inputBuffer + ltrim(received);
    unsigned long index = 0;

    // Naparsovat přijatá data
    std::vector<std::string> list;
    while ((index = received.find(DELIMITER)) != std::string::npos) {
        unsigned long size = received.size();
        std::string data = received.substr(0, index);
        list.push_back(data);

        if (size - index + 1 > 0) {
            received = received.substr(index + 1, size);
        } else {
            received = "";
        }
    }
    m_inputBuffer = received;

    // Pokud se mi je podaří naparsovat, tak zavolám nějakou obslužnou událost pro zpracování naparsovaných dat
    m_listener.onDataReceived(m_sd, list);
}

void TCPStream::closeStream() {
    ::shutdown(m_sd, SHUT_RDWR);
    ::close(m_sd);
}

const std::string &TCPStream::getIP() const {
    return m_peerIP;
}

uint16_t TCPStream::getPort() const {
    return m_peerPort;
}


}
}