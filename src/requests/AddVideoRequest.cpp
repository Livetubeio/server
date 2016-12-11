#include "requests/AddVideoRequest.h"
#include "services/YoutubeService.h"
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

void AddVideoRequest::execute() {
    using namespace rapidjson;

    std::string parts = "snippet,contentDetails";
    auto credential = std::make_unique<APICredential>();
    std::unique_ptr<VideosResource_ListMethod> listMethod(
            YoutubeService::service()->get_videos().NewListMethod(credential.get(), parts));

    listMethod->set_id(ytid);

    std::unique_ptr<VideoListResponse> videoList(VideoListResponse::New());

    listMethod->ExecuteAndParseResponse(videoList.get()).IgnoreError();

    if(!videoList->has_items()) {
        return;
    }

    auto youtube = videoList->Storage()["items"][0];

    std::stringstream ss;
    ss << AddVideoRequest::url << this->channel << "/videos.json";

    // Generate JSON
    Document root;

    auto& allocator = root.GetAllocator();
    root.SetObject();

    Value title, youtid, length;
    title.SetString(StringRef(youtube["snippet"]["title"].asCString()));
    length.SetString(StringRef(youtube["contentDetails"]["duration"].asCString()));
    youtid.SetString(StringRef(ytid.c_str()));
    root.AddMember(StringRef("title"), title , allocator);
    root.AddMember(StringRef("length"), length, allocator);
    root.AddMember(StringRef("ytid"), youtid, allocator);

    // Printing Json
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);

    // Send Request
    auto r = cpr::Post(cpr::Url{ss.str()},cpr::Body{buffer.GetString()});
}

