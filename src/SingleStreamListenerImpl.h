#ifndef SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H
#define SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H

#include "TCPStream.h"

namespace SnakeServer {
namespace Network {
class TCPConnection;

class SingleStreamListenerImpl : public SingleStreamListener {

public:
    SingleStreamListenerImpl(TCPConnection &t_tcpConnection);

    virtual ~SingleStreamListenerImpl();

    virtual void onDataReceived(int socketID, std::vector<std::string> data) override;

    virtual void onLostConnection(int socketID) override;

    virtual void onDisconnect(int socketID) override;

    virtual void onRestoreConnection(int socketID) override;

private:
    TCPConnection &m_tcpConnection;
};

}
}


#endif //SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H
