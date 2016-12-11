#ifndef LIVEPLAYLIST_SOCKETIOSERVICE_H
#define LIVEPLAYLIST_SOCKETIOSERVICE_H

#include <sio_client.h>

class SocketIOService {
public:
    static SocketIOService& instance();
    const sio::socket::ptr& socket();
private:
    SocketIOService();
    sio::client h{};
};


#endif
