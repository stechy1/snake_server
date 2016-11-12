#include <iostream>
#include "SingleStreamListenerImpl.h"
#include "Server.h"

namespace SnakeServer {
namespace Network {

SingleStreamListenerImpl::SingleStreamListenerImpl(Server &t_tcpConnection, std::map<uuid, int> &t_clients_reference)
        : m_tcpConnection(t_tcpConnection), m_clients_reference(t_clients_reference) {}

SingleStreamListenerImpl::~SingleStreamListenerImpl() {}

void SingleStreamListenerImpl::onDataReceived(int sid, std::vector<std::string> data) {
    auto findRes = std::find_if(m_clients_reference.begin(), m_clients_reference.end(), [&](const std::pair<uuid, int> pair) {
        return pair.second == sid;
    });
    if (findRes != m_clients_reference.end()) {
        m_tcpConnection.m_ioHandler.onDataReceived(findRes->first, data);
    }
}

void SingleStreamListenerImpl::onLostConnection(int sid) {
    // TODO implementovat handler onLostConection
}

void SingleStreamListenerImpl::onDisconnect(int sid) {
    auto findRes = std::find_if(m_clients_reference.begin(), m_clients_reference.end(), [&](const std::pair<uuid, int> pair) {
        return pair.second == sid;
    });
    if (findRes != m_clients_reference.end()) {
        m_tcpConnection.m_ioHandler.onDisconnect(findRes->first);
    }
}

void SingleStreamListenerImpl::onRestoreConnection(int sid) {
    // TODO implementovat handler onRestoreConnection
}

}
}