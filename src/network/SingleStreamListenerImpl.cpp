#include <iostream>
#include "SingleStreamListenerImpl.h"

namespace SnakeServer {
namespace Network {

SingleStreamListenerImpl::SingleStreamListenerImpl() {}

SingleStreamListenerImpl::~SingleStreamListenerImpl() {}

void SingleStreamListenerImpl::onDataReceived(int socketID, std::list<std::string> data) {
    // TODO implementovat handler onDataReceived
    //m_ioHandler.onDataReceived(socketID, data);
    for(auto &tmp : data) {
        std::cout << "Received: sID: " << socketID << ", data: " << tmp << std::endl;
    }
}

void SingleStreamListenerImpl::onLostConnection(int socketID) {
    // TODO implementovat handler onLostConection
}

void SingleStreamListenerImpl::onDisconnect(int socketID) {
    // TODO implementovat handler onDisconnect
    //FD_CLR(socketID, &m_master_read_fds);
    //FD_CLR(socketID, &m_master_write_fds);
    //m_ioHandler.onDisconnect(socketID);
}

void SingleStreamListenerImpl::onRestoreConnection(int socketID) {
    // TODO implementovat handler onRestoreConnection
}

}
}