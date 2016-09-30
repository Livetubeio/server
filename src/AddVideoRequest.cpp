//
// Created by stevijo on 30.09.16.
//

#include "AddVideoRequest.h"
#include "YoutubeService.h"
#include "APICredential.h"
#include <google/youtube_api/you_tube_service.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <cpr/cpr.h>
#include <iostream>

using google_youtube_api::VideosResource_ListMethod;
using google_youtube_api::YouTubeService;
using google_youtube_api::VideoListResponse;

void AddVideoRequest::Init() {
    std::string parts = "snippet,contentDetails,statistics";
    auto credential = std::make_unique<APICredential>();
    std::unique_ptr<VideosResource_ListMethod> listMethod(
            YoutubeService::service()->get_videos().NewListMethod(credential.get(), parts));

    listMethod->set_id(ytid);

    std::unique_ptr<VideoListResponse> videoList(VideoListResponse::New());

    listMethod->ExecuteAndParseResponse(videoList.get()).IgnoreError();

    youtube = videoList->Storage()["items"][0];
}

void AddVideoRequest::execute() {
    std::stringstream ss;
    ss << AddVideoRequest::url << this->channel << "/videos.json";
    ss.clear();

    // Generate JSON
    rapidjson::Document root;
    rapidjson::Value child;

    auto& allocator = root.GetAllocator();
    root.SetObject();

    rapidjson::Value title, youtid;
    title.SetString(rapidjson::StringRef(youtube["snippet"]["title"].asCString()));
    youtid.SetString(rapidjson::StringRef(ytid.c_str()));
    root.AddMember(rapidjson::StringRef("title"), title , allocator);
    root.AddMember(rapidjson::StringRef("ytid"), youtid, allocator);

    // Printing Json
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    root.Accept(writer);
    std::cout << buffer.GetString() << std::endl;

    // Send Request
    auto r = cpr::Patch(cpr::Url{ss.str()},cpr::Body{buffer.GetString()});
    std::cout << r.status_code << std::endl;

    return;
}
