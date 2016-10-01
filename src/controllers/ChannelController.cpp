//
// Created by stevijo on 01.10.16.
//

#include "controllers/ChannelController.h"
#include <rapidjson/document.h>
#include <requests/ChangePlayerStateRequest.h>
#include <requests/ChangeActiveVideosRequest.h>

using namespace rapidjson;

void ChannelController::update(const Rest::Request &request, Http::ResponseWriter response) {

    Document document;
    document.Parse(request.body().c_str());

    // Predeclare Request
    std::unique_ptr<ChangePlayerStateRequest> changePlayerStateRequest;
    std::unique_ptr<ChangeActiveVideosRequest> changeActiveVideosRequest;

    if(!document.IsObject() ||
            !document.HasMember("channel") || !document["channel"].IsString()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

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
        changePlayerStateRequest.reset(new ChangePlayerStateRequest{document["channel"].GetString(),state});
        changePlayerStateRequest->executeAsync();
    }

    if(document.HasMember("active")) {
        changeActiveVideosRequest.reset(new ChangeActiveVideosRequest{document["channel"].GetString(),
                                                                      document["active"].GetString()});
        changeActiveVideosRequest->executeAsync();
    }

    response.send(Http::Code::Ok);

    // Clean up threads
    if(changePlayerStateRequest != nullptr) {
        changePlayerStateRequest->join();
    }
    if(changeActiveVideosRequest != nullptr) {
        changeActiveVideosRequest->join();
    }
}
