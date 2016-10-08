//
// Created by stevijo on 28.09.16.
//

#include "controllers/VideoController.h"
#include "controllers/ChannelController.h"
#include "controllers/LoginController.h"
#include "header/XGithubAuth.h"
#include "header/XLiveTubeAuth.h"
#include "Router.h"

using namespace Net;

void Router::init(size_t thr) {
    auto opts = Http::Endpoint::options().threads(thr).flags(Net::Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    setupRoutes();
}

void Router::start() {
    Net::Http::Header::Registry::registerHeader<XGithubAuth>();
    Net::Http::Header::Registry::registerHeader<XLiveTubeAuth>();
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void Router::shutdown() {
    httpEndpoint->shutdown();
}

void Router::setupRoutes() {
    using namespace Net::Rest;

    Routes::Post(router, "/channels/:id/videos", Routes::bind(&VideoController::create, VideoController::instance()));
    Routes::Options(router, "/channels/*/videos", Routes::bind(&Router::handleOptions, this));

    Routes::Delete(router,"/channels/:id/videos/:video", Routes::bind(&VideoController::remove, VideoController::instance()));
    Routes::Options(router,"/channels/*/videos/*", Routes::bind(&Router::handleOptions, this));

    Routes::Post(router, "/login", Routes::bind(&LoginController::login, LoginController::instance()));
    Routes::Options(router, "/", Routes::bind(&Router::handleOptions, this));
    Routes::Options(router, "/*", Routes::bind(&Router::handleOptions, this));

    Routes::Get(router, "/channels/:id", Routes::bind(&ChannelController::getBadge, ChannelController::instance()));
    Routes::Post(router, "/channels/:id/update", Routes::bind(&ChannelController::updateVideo, ChannelController::instance()));
    Routes::Options(router, "/channels/*/update", Routes::bind(&Router::handleOptions, this));
    Routes::Put(router, "/channels/:id", Routes::bind(&ChannelController::update, ChannelController::instance()));
    Routes::Options(router, "/channels/*", Routes::bind(&Router::handleOptions, this));

}

void Router::handleOptions(const Rest::Request &request, Http::ResponseWriter response) {

    H::addCorsHeaders(response);
    response.send(Http::Code::Ok);
}
