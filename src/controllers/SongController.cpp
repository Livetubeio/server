//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include "AddVideoRequest.h"
#include "controllers/SongController.h"
#include <rapidjson/document.h>
#include <memory>

using namespace googleapis;

void SongController::create(const Rest::Request &request, Net::Http::ResponseWriter response) {

    rapidjson::Document document;
    document.Parse(request.body().c_str());
    if (!document.IsObject() ||
        !document.HasMember("ytid") ||
        !document["ytid"].IsString()) {
        response.send(Http::Code::Internal_Server_Error);
        return;
    }

    AddVideoRequest videoRequest{"test",document["ytid"].GetString()};
    videoRequest.execute();

    response.send(Http::Code::Ok);
}
