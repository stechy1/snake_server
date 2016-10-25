#ifndef SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H
#define SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H

#include "TCPStream.h"

namespace SnakeServer {
namespace Network {
class SingleStreamListenerImpl : public SingleStreamListener {

public:
    SingleStreamListenerImpl();
    virtual ~SingleStreamListenerImpl();

    virtual void onDataReceived(int socketID, std::list<std::string> data) override;

    virtual void onLostConnection(int socketID) override;

    virtual void onDisconnect(int socketID) override;

    virtual void onRestoreConnection(int socketID) override;

};

}
}


#endif //SNAKE_SERVER_SINGLESTREAMLISTENERIMPL_H
