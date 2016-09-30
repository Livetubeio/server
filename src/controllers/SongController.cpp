//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include "controllers/SongController.h"
#include <rapidjson/document.h>

#include <google/youtube_api/you_tube_service.h>
#include <APICredential.h>
#include <YoutubeService.h>
#include <memory>

using google_youtube_api::VideosResource_ListMethod;
using google_youtube_api::YouTubeService;
using google_youtube_api::VideoListResponse;

using namespace rapidjson;
using namespace googleapis;

void SongController::create(const Rest::Request &request, Net::Http::ResponseWriter response) {

    Document document;
    document.Parse(request.body().c_str());
    if (!document.IsObject() ||
        !document.HasMember("ytid") ||
        !document["ytid"].IsString()) {
        response.send(Http::Code::Internal_Server_Error);
        return;
    }

    std::string parts = "snippet,contentDetails,statistics";
    auto credential = std::make_unique<APICredential>("");
    std::unique_ptr<VideosResource_ListMethod> listMethod(
            YoutubeService::service()->get_videos().NewListMethod(credential.get(), parts));

    //listMethod->set_id(document["ytid"].GetString());

    std::unique_ptr<VideoListResponse> videoList(VideoListResponse::New());

    listMethod->ExecuteAndParseResponse(videoList.get()).IgnoreError();

    if (videoList->Storage()["items"].size() != 1) {
        response.send(Http::Code::Internal_Server_Error);
        return;
    }

    std::stringstream ss;
    ss << videoList->Storage()["items"][0];

    response.send(Http::Code::Ok, ss.str(), MIME(Application, Json));


}
