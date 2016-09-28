//
// Created by stevijo on 28.09.16.
//

#ifndef LIVEPLAYLIST_ROUTER_H
#define LIVEPLAYLIST_ROUTER_H

#include <pistache/endpoint.h>
#include <pistache/router.h>

using namespace Net;

class Router {
public:
    Router(Net::Address addr) : httpEndpoint(std::make_unique<Http::Endpoint>(addr)) {}

    void init(size_t thr = 2);
    void start();
    void shutdown();
private:
    std::unique_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;

    void setupRoutes();

};


#endif //LIVEPLAYLIST_ROUTER_H
