//
// Created by stevijo on 28.09.16.
//

#include <controllers/SongController.h>
#include "Router.h"
#include "controllers/HelloWorldController.h"

using namespace Net;

void Router::init(size_t thr) {
    auto opts = Http::Endpoint::options().threads(thr).flags(Net::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    setupRoutes();
}

void Router::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void Router::shutdown() {
    httpEndpoint->shutdown();
}

void Router::setupRoutes() {
    using namespace Net::Rest;

    Routes::Post(router, "/songs", Routes::bind(&SongController::create, SongController::instance()));
}
