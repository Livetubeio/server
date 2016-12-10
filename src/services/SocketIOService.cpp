//
// Created by stevijo on 10.12.16.
//

#include "services/SocketIOService.h"

SocketIOService& SocketIOService::instance() {
    static SocketIOService instance;
    return instance;
}

SocketIOService::SocketIOService() {
    h.connect("http://localhost:3000");
}

const sio::socket::ptr& SocketIOService::socket() {
    return h.socket();
}
