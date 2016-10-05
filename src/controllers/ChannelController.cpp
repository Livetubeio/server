//
// Created by stevijo on 01.10.16.
//

#include "controllers/ChannelController.h"
#include "header/XLiveTubeAuth.h"
#include "header/XGithubAuth.h"
#include "requests/UpdateChannelRequest.h"
#include "YoutubeService.h"
#include "APICredential.h"
#include <google/youtube_api/you_tube_service.h>
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


    if(document.HasMember("playerstate") && !document["playerstate"].IsNumber() ||
            document.HasMember("active") && !document["active"].IsString()) {
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

    updateChannelRequest.executeAsync();

    H::addCorsHeaders(response);
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
    request1 << "https://livetubeio-16323.firebaseio.com/channels/" << channel << "/active.json";

    auto res = cpr::Get(cpr::Url{request1.str()});
    if(res.status_code != 200) {
        response.send(Http::Code::Bad_Request);
        return;
    }

    Document document;
    document.Parse(res.text.c_str());

    auto active = document.GetString();

    std::string parts = "snippet";
    auto credential = std::make_unique<APICredential>();
    std::unique_ptr<VideosResource_ListMethod> listMethod(
            YoutubeService::service()->get_videos().NewListMethod(credential.get(), parts));

    listMethod->set_id(active);

    std::unique_ptr<VideoListResponse> videoList(VideoListResponse::New());

    listMethod->ExecuteAndParseResponse(videoList.get()).IgnoreError();

    auto youtube = videoList->Storage()["items"][0];

    std::stringstream ss;
    ss << part1 << youtube["snippet"]["title"].asCString() << part2 << youtube["snippet"]["title"].asCString() << part3;

    H::addCorsHeaders(response);
    response.send(Http::Code::Ok,ss.str(),MIME(Image,Svg));
}
