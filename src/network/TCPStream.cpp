#include "TCPStream.h"

#include <iostream>

namespace SnakeServer {

    namespace Network {

        TCPStream::TCPStream() {}

        TCPStream::TCPStream(const int t_sd, const struct sockaddr_in *t_address) : m_sd(t_sd) {
            char ip[50];
            inet_ntop(PF_INET, (struct in_addr *) &(t_address->sin_addr.s_addr), ip, sizeof(ip) - 1);
            m_peerIP = *ip;
            m_peerPort = ntohs(t_address->sin_port);
        }

        TCPStream::~TCPStream() {
            closeStream();
        }

        std::string TCPStream::receive() {
            char buff[BUFFER_SIZE];
            ssize_t received = recv(m_sd, buff, BUFFER_SIZE - 1, 0);

            if (received == -1) {
                if (errno != EWOULDBLOCK) {
                    closeStream();
                    throw new std::runtime_error("connection_lost");
                }

                return "";
            }

            return std::string(buff, received);
        }

        std::string TCPStream::getPeerIP() {
            return m_peerIP;
        }

        int TCPStream::getPeerPort() {
            return m_peerPort;
        }

        void TCPStream::closeStream() {
            ::close(m_sd);
        }

    } // endnamespace Network

} // end namespace SnakeServer