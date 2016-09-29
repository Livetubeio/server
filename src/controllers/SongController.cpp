//
// Created by stevijo on 28.09.16.
//

#include "helper.h"
#include "controllers/SongController.h"
#include <rapidjson/document.h>

#include <google/youtube_api/you_tube_service.h>
#include <APICredential.h>
#include <YoutubeService.h>

using google_youtube_api::VideosResource_ListMethod;
using google_youtube_api::YouTubeService;
using google_youtube_api::VideoListResponse;

using namespace rapidjson;
using namespace googleapis;

void SongController::create(const Rest::Request &request, Net::Http::ResponseWriter response) {

    std::string parts = "snippet,contentDetails,statistics";
    auto credential = std::make_unique<APICredential>("");
    std::unique_ptr<VideosResource_ListMethod> listMethod(YoutubeService::service()->get_videos().NewListMethod(credential.get(),parts));

    listMethod->set_id("Ks-_Mh1QhMc");

    std::unique_ptr<VideoListResponse> videoList(VideoListResponse::New());

    listMethod->ExecuteAndParseResponse(videoList.get()).IgnoreError();

    std::stringstream ss;
    ss << videoList->Storage()["items"][0];

    response.send(Http::Code::Ok, ss.str(), MIME(Application,Json));
}
