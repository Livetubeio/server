//
// Created by stevijo on 01.10.16.
//

#include "controllers/ChannelController.h"
#include "header/XLiveTubeAuth.h"
#include "header/XGithubAuth.h"
#include "requests/UpdateChannelRequest.h"
#include "YoutubeService.h"
#include "APICredential.h"
#include <rapidjson/document.h>
#include <cpr/cpr.h>

using namespace rapidjson;
using google_youtube_api::VideosResource_ListMethod;
using google_youtube_api::YouTubeService;
using google_youtube_api::VideoListResponse;

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
    UpdateChannelRequest updateChannelRequest{channel};


    if(!document.IsObject() || document.HasMember("playerstate") && !document["playerstate"].IsNumber() ||
            document.HasMember("active") && !document["active"].IsString() ||
            document.HasMember("video_time") && !document["video_time"].IsInt() ||
            document.HasMember("changed_at") && !document["changed_at"].IsInt64()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    if(document.HasMember("playerstate")) {
        UpdateChannelRequest::State state;
        switch(document["playerstate"].GetInt()) {
            case 1: {
                state = UpdateChannelRequest::State::PLAYING;
                break;
            }
            case 2: {
                state = UpdateChannelRequest::State::PAUSED;
                break;
            }
            default: {
                response.send(Http::Code::Bad_Request);
                return;
            }
        }
        updateChannelRequest.setState(state);
    }

    if(document.HasMember("active")) {
        updateChannelRequest.setActive(document["active"].GetString());
    }

    if(document.HasMember("video_time")) {
        updateChannelRequest.setVideoTime(document["video_time"].GetInt());
    }

    updateChannelRequest.setChangedAt(H::getTimestamp());

    updateChannelRequest.executeAsync();

    response.send(Http::Code::Ok);

    updateChannelRequest.join();
}

constexpr static const char* part1 = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"160\" height=\"20\">\n"
        "    <linearGradient id=\"b\" x2=\"0\" y2=\"100%\">\n"
        "        <stop offset=\"0\" stop-color=\"#bbb\" stop-opacity=\".1\"/>\n"
        "        <stop offset=\"1\" stop-opacity=\".1\"/>\n"
        "    </linearGradient>\n"
        "    <mask id=\"a\">\n"
        "        <rect width=\"160\" height=\"20\" rx=\"3\" fill=\"#fff\"/>\n"
        "    </mask>\n"
        "    <g mask=\"url(#a)\">\n"
        "        <rect width=\"20\" height=\"20\" fill=\"#555\"/>\n"
        "        <rect x=\"20\" width=\"140\" height=\"20\" fill=\"#F3452B\"/>\n"
        "        <rect width=\"160\" height=\"20\" fill=\"url(#b)\"/>\n"
        "    </g>\n"
        "    <g fill=\"#fff\" text-anchor=\"left\" font-family=\"DejaVu Sans,Verdana,Geneva,sans-serif\" font-size=\"11\">\n"
        "        <text x=\"6\" y=\"15\" fill=\"#010101\" fill-opacity=\".3\">►</text>\n"
        "        <text x=\"6\" y=\"14\">►</text>\n"
        "        <text x=\"26\" y=\"15\" fill=\"#010101\" fill-opacity=\".3\">";
constexpr static const char* part2 = "</text>\n"
        "        <text x=\"26\" y=\"14\">";
constexpr static const char* part3 = "</text>\n"
        "    </g>\n"
        "</svg>";

void ChannelController::getBadge(const Rest::Request &request, Http::ResponseWriter response) {
    auto channel = request.param(":id").as<std::string>();

    std::stringstream request1;
    request1 << "https://livetubeio-16323.firebaseio.com/channels/" << channel << ".json";

    auto res = cpr::Get(cpr::Url{request1.str()});
    if(res.status_code != 200) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    Document document;
    document.Parse(res.text.c_str());

    if(!document.IsObject() || !document.HasMember("active") || !document["active"].IsString() ||
            !document.HasMember("videos") || !document["videos"].IsObject()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    auto activeString = document["active"].GetString();
    if(!document["videos"].GetObject().HasMember(activeString)) {
        response.send(Http::Code::Bad_Request);
        return;
    }
    auto ytid = document["videos"].GetObject()[activeString].GetObject()["ytid"].GetString();

    std::string parts = "snippet";
    auto credential = std::make_unique<APICredential>();
    std::unique_ptr<VideosResource_ListMethod> listMethod(
            YoutubeService::service()->get_videos().NewListMethod(credential.get(), parts));

    listMethod->set_id(ytid);

    std::unique_ptr<VideoListResponse> videoList(VideoListResponse::New());

    listMethod->ExecuteAndParseResponse(videoList.get()).IgnoreError();
    if(!videoList->has_items()) {
        response.send(Http::Code::Internal_Server_Error);
        return;
    }

    auto youtube = videoList->Storage()["items"][0];

    std::stringstream ss;
    ss << part1 << youtube["snippet"]["title"].asCString() << part2 << youtube["snippet"]["title"].asCString() << part3;

    response.send(Http::Code::Ok,ss.str(),MIME(Image,Svg));
}

void ChannelController::updateVideo(const Rest::Request &request, Http::ResponseWriter response) {

    // Lock function so only 1 request uses cpu
    std::lock_guard<std::mutex> lock(mutex);
    auto ms = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
    );
    if(ms.count() - lastChange.count() < 3000) {
        response.send(Http::Code::Bad_Request);
        return;
    }
    auto channel = request.param(":id").as<std::string>();

    std::stringstream url;
    url << "https://livetubeio-16323.firebaseio.com/channels/" << channel << ".json";
    auto res = cpr::Get(cpr::Url{url.str()});
    if(res.status_code != 200) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    Document document;
    document.Parse(res.text.c_str());

    if(!document.IsObject() || !document.HasMember("videos") || !document["videos"].IsObject() ||
            !document.HasMember("changed_at") || !document["changed_at"].IsInt64() ||
            !document.HasMember("video_time") || !document["video_time"].IsInt() ||
            !document.HasMember("active") || !document["active"].IsString() ||
            !document.HasMember("playerstate") || !document["playerstate"].IsInt()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    UpdateChannelRequest::State playerState = static_cast<UpdateChannelRequest::State>(
            document["playerstate"].GetInt()
    );
    if(playerState != UpdateChannelRequest::State::PLAYING) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    // Variable Initialization
    ms = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
    );

    auto changedAt = document["changed_at"].GetInt64();
    auto videoTime = document["video_time"].GetInt();
    auto offset = ms.count() - changedAt + videoTime*1000;
    auto active = document["active"].GetString();
    auto it = document["videos"].GetObject().MemberBegin();
    auto end = document["videos"].GetObject().MemberEnd();
    auto start = it;

    // Get active Startpoint
    for(;;it++) {
        if(it == end) {
            response.send(Http::Code::Bad_Request);
            return;
        }
        if(strcmp(it->name.GetString(),active) == 0) {
            break;
        }
    }

    offset -= H::getSecondsFromYoutubeTime(it->value.GetObject()["length"].GetString())*1000;
    if(offset <= -3000) {
        // Still playing current song
        response.send(Http::Code::Bad_Request);
        return;
    }
    it++;

    while(offset > 0) {
        if(it != end) {
            auto& video = *it;
            // length in ms
            auto length = H::getSecondsFromYoutubeTime(video.value.GetObject()["length"].GetString())*1000;
            offset -= length;
            if(offset <= 0) {
                break;
            }
            it++;
        } else {
            it = start;
        }
    }

    // decided on new video create a request
    ms = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
    );
    UpdateChannelRequest channelRequest{channel};
    channelRequest.setChangedAt(ms.count());
    if(offset < 0) {
        channelRequest.setVideoTime(static_cast<int>(H::getSecondsFromYoutubeTime(it->value.GetObject()["length"].GetString())-offset/1000*-1));
    } else {
        channelRequest.setVideoTime(0);
    }
    channelRequest.setActive(it->name.GetString());
    channelRequest.executeAsync();
    // Hacky synchronization
    channelRequest.join();

    lastChange = ms;

    response.send(Http::Code::Ok);

}
