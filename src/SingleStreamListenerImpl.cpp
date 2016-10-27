#include <iostream>
#include "SingleStreamListenerImpl.h"
#include "TCPConnection.h"

namespace SnakeServer {
namespace Network {

SingleStreamListenerImpl::SingleStreamListenerImpl(TCPConnection &t_tcpConnection) : m_tcpConnection(t_tcpConnection) {}

SingleStreamListenerImpl::~SingleStreamListenerImpl() {}

void SingleStreamListenerImpl::onDataReceived(int socketID, std::list<std::string> data) {
    m_tcpConnection.m_ioHandler.onDataReceived(socketID, data);
}

void SingleStreamListenerImpl::onLostConnection(int socketID) {
    // TODO implementovat handler onLostConection
}

void SingleStreamListenerImpl::onDisconnect(int socketID) {
    // TODO implementovat handler onDisconnect
    //FD_CLR(socketID, &m_master_read_fds);
    //FD_CLR(socketID, &m_master_write_fds);
    //m_ioHandler.onDisconnect(socketID);
    m_tcpConnection.m_ioHandler.onDisconnect(socketID);
}

void SingleStreamListenerImpl::onRestoreConnection(int socketID) {
    // TODO implementovat handler onRestoreConnection
}

}
}