#ifndef LIVEPLAYLIST_ROUTER_H
#define LIVEPLAYLIST_ROUTER_H

#include <endpoint.h>
#include <router.h>

using namespace Net;

class Router {
public:
    Router(Net::Address addr) : httpEndpoint(std::make_unique<Http::Endpoint>(addr)) {}

    void init(size_t thr = 2);
    void start();
    void shutdown();
    void handleOptions(const Rest::Request& request, Http::ResponseWriter response);
    void serverTime(const Rest::Request& request, Http::ResponseWriter response);
private:
    std::unique_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;
    void setupRoutes();
};

#endif
