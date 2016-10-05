//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include "header/XLiveTubeAuth.h"
#include "header/XGithubAuth.h"
#include "requests/AddVideoRequest.h"
#include "requests/DeleteVideoRequest.h"
#include "controllers/VideoController.h"
#include "jwt/Token.h"
#include <rapidjson/document.h>
#include "Github.h"
#include <algorithm>

using namespace rapidjson;

void VideoController::create(const Rest::Request &request, Net::Http::ResponseWriter response) {

    auto channel = request.param(":id").as<std::string>();

    auto headers = request.headers();
    auto token = headers.get<XLiveTubeAuth>();
    auto github = headers.get<XGithubAuth>();

    auto res = verifyAccess(channel,token->getToken(),github->getToken());
    if(!res) {
        response.send(Http::Code::Bad_Request);
        return;
    }


    Document body;
    body.Parse(request.body().c_str());
    if (!body.IsObject() ||
        !body.HasMember("ytid") ||
        !body["ytid"].IsString()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    AddVideoRequest videoRequest{channel,body["ytid"].GetString()};
    videoRequest.executeAsync();

    H::addCorsHeaders(response);
    response.send(Http::Code::Ok);

    videoRequest.join();
}

void VideoController::remove(const Rest::Request &request, Net::Http::ResponseWriter response) {
    auto channel = request.param(":id").as<std::string>();
    auto video = request.param(":video").as<std::string>();

    auto headers = request.headers();
    auto token = headers.get<XLiveTubeAuth>();
    auto github = headers.get<XGithubAuth>();

    auto res = verifyAccess(channel,token->getToken(),github->getToken());
    if(!res){
        response.send(Http::Code::Bad_Request);
        return;
    }

    DeleteVideoRequest deleteVideoRequest{channel,video};
    deleteVideoRequest.executeAsync();

    response.send(Http::Code::Ok);

    deleteVideoRequest.join();

}
