#include <cstring>
#include "TCPStream.h"

namespace SnakeServer {
namespace Network {

TCPStream::TCPStream(const int t_sd, const struct sockaddr_in *t_address)
        : m_sd(t_sd) {
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr *) &(t_address->sin_addr.s_addr), ip, sizeof(ip) - 1);
    m_peerIP = *ip;
    m_peerPort = ntohs(t_address->sin_port);
}

TCPStream::~TCPStream() {}

void TCPStream::send() {
    const char *buff = m_outputBuffer.c_str();
    m_outputBuffer.clear();

    unsigned long len = strlen(buff);

    int total = 0;
    unsigned long bytesleft = len;
    ssize_t n;

    while (total < len) {
        n = ::send(m_sd, buff+total, bytesleft, 0);
        if (n == -1) {
            break;
        }

        total += n;
        bytesleft -= n;
    }
}

void TCPStream::receive() {
    char buff[BUFFER_SIZE];
    ssize_t len = recv(m_sd, buff, BUFFER_SIZE - 1, 0);
    std::string received;
    if (len == 0) {
        // Spojení bylo slušně ukončeno
        // TODO zavolat obslužnou událost pro zpracování slušného odpojení klienta
        return;
    }
    if (len == -1) {
        if (errno != EWOULDBLOCK) {
            //closeStream();
            // TODO zvolat obslužnou událost pro zpracování ztraceného spojení s uživatelem
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
    // Zbytek nezpracovaných dat vložit do bufferu
    m_inputBuffer = received;
}

void TCPStream::closeStream() {
    ::close(m_sd);
}

void TCPStream::prepareDataToSend(std::string data) {
    m_outputBuffer+= data;
}

}
}