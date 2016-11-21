#ifndef SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H
#define SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H

#include "TCPStream.h"
#include <boost/uuid/uuid.hpp>
#include <map>

namespace SnakeServer {
namespace Network {

typedef boost::uuids::uuid uuid;
class Server;

class SingleStreamListenerImpl : public SingleStreamListener {

public:
    SingleStreamListenerImpl(Server &t_server, std::map<uuid, int> &t_clients_reference);

    virtual ~SingleStreamListenerImpl();

    virtual void onDataReceived(int sid, std::vector<std::string> data) override;

    virtual void onLostConnection(int sid) override;

    virtual void onDisconnect(int sid) override;

private:
    Server &m_server;
    std::map<uuid, int> &m_clients_reference;
};

}
}


#endif //SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H
