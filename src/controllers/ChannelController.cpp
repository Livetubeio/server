//
// Created by stevijo on 01.10.16.
//

#include "controllers/ChannelController.h"
#include "header/XLiveTubeAuth.h"
#include "header/XGithubAuth.h"
#include <rapidjson/document.h>
#include <requests/ChangePlayerStateRequest.h>
#include <requests/ChangeActiveVideosRequest.h>

using namespace rapidjson;

void ChannelController::update(const Rest::Request &request, Http::ResponseWriter response) {

    auto channel = request.param(":id").as<std::string>();

    auto headers = request.headers();
    auto token = headers.get<XLiveTubeAuth>();
    auto github = headers.get<XGithubAuth>();

    auto res = verifyAccess(channel,token->getToken(), github->getToken());
    if(!res) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    Document document;
    document.Parse(request.body().c_str());

    // Predeclare Request
    std::unique_ptr<ChangePlayerStateRequest> changePlayerStateRequest;
    std::unique_ptr<ChangeActiveVideosRequest> changeActiveVideosRequest;


    if(document.HasMember("playerstate") && !document["playerstate"].IsNumber() ||
            document.HasMember("active") && !document["active"].IsString()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    if(document.HasMember("playerstate")) {
        ChangePlayerStateRequest::State state;
        switch(document["playerstate"].GetInt()) {
            case 1: {
                state = ChangePlayerStateRequest::State::PLAYING;
                break;
            }
            case 2: {
                state = ChangePlayerStateRequest::State::PAUSED;
                break;
            }
            default: {
                response.send(Http::Code::Bad_Request);
                return;
            }
        }
        changePlayerStateRequest.reset(new ChangePlayerStateRequest{channel,state});
        changePlayerStateRequest->executeAsync();
    }

    if(document.HasMember("active")) {
        changeActiveVideosRequest.reset(new ChangeActiveVideosRequest{channel,
                                                                      document["active"].GetString()});
        changeActiveVideosRequest->executeAsync();
    }

    H::addCorsHeaders(response);
    response.send(Http::Code::Ok);

    if(changeActiveVideosRequest) {
        changeActiveVideosRequest->join();
    }
    if(changePlayerStateRequest) {
        changePlayerStateRequest->join();
    }
}
