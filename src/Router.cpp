//
// Created by stevijo on 28.09.16.
//

#include <controllers/VideoController.h>
#include <controllers/ChannelController.h>
#include "header/AccessControlAllowOrigin.h"
#include "header/AccessControlAllowMethods.h"
#include "header/AccessControlMaxAge.h"
#include "header/AccessControlAllowHeaders.h"
#include "Router.h"

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

    Routes::Post(router, "/videos", Routes::bind(&VideoController::create, VideoController::instance()));
    Routes::Put(router, "/channels", Routes::bind(&ChannelController::update, ChannelController::instance()));
    Routes::Options(router, "/", Routes::bind(&Router::handleOptions, this));
    Routes::Options(router, "*", Routes::bind(&Router::handleOptions, this));
}

void Router::handleOptions(const Rest::Request &request, Http::ResponseWriter response) {

    response.headers().add(
            std::make_shared<AccessControlAllowOrigin>(
                    std::initializer_list<std::string>{"*"})
    );
    response.headers().add(
            std::make_shared<AccessControlAllowMethods>(
                    std::initializer_list<std::string>{"GET","POST","PUT","DELETE"}
            )
    );
    response.headers().add(
            std::make_shared<AccessControlMaxAge>(2629744)
    );
    response.headers().add(
            std::make_shared<AccessControlAllowHeaders>(
                    std::initializer_list<std::string>{"X-LIVETUBE-AUTH"}
            )
    );
    response.send(Http::Code::Ok);
}
