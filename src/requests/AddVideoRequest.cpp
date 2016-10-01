//
// Created by stevijo on 30.09.16.
//

#include "requests/AddVideoRequest.h"
#include "YoutubeService.h"
#include "APICredential.h"
#include <google/youtube_api/you_tube_service.h>
#include <thread>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <cpr/cpr.h>
#include <iostream>

using google_youtube_api::VideosResource_ListMethod;
using google_youtube_api::YouTubeService;
using google_youtube_api::VideoListResponse;

void AddVideoRequest::Init() {

    std::string parts = "snippet,contentDetails";
    auto credential = std::make_unique<APICredential>();
    std::unique_ptr<VideosResource_ListMethod> listMethod(
            YoutubeService::service()->get_videos().NewListMethod(credential.get(), parts));

    listMethod->set_id(ytid);

    std::unique_ptr<VideoListResponse> videoList(VideoListResponse::New());

    listMethod->ExecuteAndParseResponse(videoList.get()).IgnoreError();

    youtube = videoList->Storage()["items"][0];
    youtubeDone = true;
    std::cout << youtube["contentDetails"] << std::endl;
    cv.notify_all();
    std::cout << "youtube done" << std::endl;
}

void AddVideoRequest::execute() {
    if(!youtubeDone) {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << "waiting async" << std::endl;
        cv.wait(lock);
    }
    std::cout << "starting Request execute" << std::endl;

    std::stringstream ss;
    ss << AddVideoRequest::url << this->channel << "/videos.json";

    // Generate JSON
    rapidjson::Document root;

    auto& allocator = root.GetAllocator();
    root.SetObject();

    rapidjson::Value title, youtid, length;
    title.SetString(rapidjson::StringRef(youtube["snippet"]["title"].asCString()));
    length.SetString(rapidjson::StringRef(youtube["contentDetails"]["duration"].asCString()));
    youtid.SetString(rapidjson::StringRef(ytid.c_str()));
    root.AddMember(rapidjson::StringRef("title"), title , allocator);
    root.AddMember(rapidjson::StringRef("length"), length, allocator);
    root.AddMember(rapidjson::StringRef("ytid"), youtid, allocator);

    // Printing Json
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    root.Accept(writer);
    std::cout << buffer.GetString() << std::endl;

    // Send Request
    auto r = cpr::Post(cpr::Url{ss.str()},cpr::Body{buffer.GetString()});
    std::cout << r.status_code << std::endl;

    return;
}

