//
// Created by stevijo on 01.10.16.
//

#include "controllers/ChannelController.h"
#include "header/XLiveTubeAuth.h"
#include "header/XGithubAuth.h"
#include "requests/UpdateChannelRequest.h"
#include "services/VideoService.h"
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
    using namespace rapidjson;
    typedef rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> iterator;

    auto channel = request.param(":id").as<std::string>();

    VideoService service;
    iterator it;
    std::tie(ignore, it) = service.getNextVideo(channel);
    if(!it->value.IsObject()) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    std::stringstream ss;
    ss << part1 << it->value.GetObject()["title"].GetString() << part2 << it->value.GetObject()["title"].GetString() << part3;

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

    VideoService service;
    bool res;
    std::tie(res, ignore) = service.getNextVideo(channel);
    if(!res) {
        response.send(Http::Code::Bad_Request);
    }
    lastChange = ms;

    response.send(Http::Code::Ok);

}
