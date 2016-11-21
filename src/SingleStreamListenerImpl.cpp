#include <iostream>
#include "SingleStreamListenerImpl.h"
#include "Server.h"
#include "SimpleLogger.h"

namespace SnakeServer {
namespace Network {

SingleStreamListenerImpl::SingleStreamListenerImpl(Server &t_server, std::map<uuid, int> &t_clients_reference)
        : m_server(t_server), m_clients_reference(t_clients_reference) {}

SingleStreamListenerImpl::~SingleStreamListenerImpl() {}

void SingleStreamListenerImpl::onDataReceived(int sid, std::vector<std::string> data) {
    auto findRes = std::find_if(m_clients_reference.begin(), m_clients_reference.end(), [&](const std::pair<uuid, int> pair) {
        return pair.second == sid;
    });
    if (findRes != m_clients_reference.end()) {
        m_server.m_ioHandler.onDataReceived(findRes->first, data);
    }
}

void SingleStreamListenerImpl::onLostConnection(int sid) {
    // TODO implementovat handler onLostConection
    LOG_DEBUG << "Client lost connection.";
    auto findRes = std::find_if(m_clients_reference.begin(), m_clients_reference.end(), [&](const std::pair<uuid, int> pair) {
        return pair.second == sid;
    });
    if (findRes != m_clients_reference.end()) {
        uuid uid = findRes->first;
        m_clients_reference[uid] = -1;
    }
}

void SingleStreamListenerImpl::onDisconnect(int sid) {
    auto findRes = std::find_if(m_clients_reference.begin(), m_clients_reference.end(), [&](const std::pair<uuid, int> pair) {
        return pair.second == sid;
    });
    if (findRes != m_clients_reference.end()) {
        m_server.m_ioHandler.onDisconnect(findRes->first);
//        uuid uid = findRes->first;
//        m_clients_reference[uid] = -1;
    }
}

}
}