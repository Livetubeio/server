//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include "requests/AddVideoRequest.h"
#include "controllers/VideoController.h"
#include <rapidjson/document.h>
#include <memory>

using namespace googleapis;

void VideoController::create(const Rest::Request &request, Net::Http::ResponseWriter response) {

    rapidjson::Document document;
    document.Parse(request.body().c_str());
    if (!document.IsObject() ||
        !document.HasMember("ytid") || !document.HasMember("channel") ||
        !document["ytid"].IsString() || !document["channel"].IsString()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    AddVideoRequest videoRequest{document["channel"].GetString(),document["ytid"].GetString()};
    videoRequest.executeAsync();

    response.send(Http::Code::Ok);

    // Clean up threads
    videoRequest.join();
}
