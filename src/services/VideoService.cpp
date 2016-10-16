//
// Created by stevijo on 16.10.16.
//

#include "services/VideoService.h"
#include "requests/UpdateChannelRequest.h"
#include "helper.h"
#include <chrono>
#include <rapidjson/document.h>
#include <sstream>
#include <cpr/cpr.h>

std::pair<bool, rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>>
VideoService::getNextVideo(const std::string &channel) {
    using namespace rapidjson;

    channelData.SetObject();

    std::stringstream url;
    url << "https://livetubeio-16323.firebaseio.com/channels/" << channel << ".json";
    auto res = cpr::Get(cpr::Url{url.str()});
    if(res.status_code != 200) {
        return std::make_pair<bool, iterator>(false, channelData.GetObject().MemberBegin());
    }

    channelData.Parse(res.text.c_str());

    if(!channelData.IsObject() || !channelData.HasMember("videos") || !channelData["videos"].IsObject() ||
       !channelData.HasMember("changed_at") || !channelData["changed_at"].IsInt64() ||
       !channelData.HasMember("video_time") || !channelData["video_time"].IsInt() ||
       !channelData.HasMember("active") || !channelData["active"].IsString() ||
       !channelData.HasMember("playerstate") || !channelData["playerstate"].IsInt()) {
        return std::make_pair<bool, iterator>(false, channelData.GetObject().MemberBegin());
    }

    UpdateChannelRequest::State playerState = static_cast<UpdateChannelRequest::State>(
            channelData["playerstate"].GetInt()
    );
    if(playerState != UpdateChannelRequest::State::PLAYING) {
        return std::make_pair<bool, iterator>(false, channelData.GetObject().MemberBegin());
    }

    // Variable Initialization
    auto ms = H::getTimestamp();

    auto changedAt = channelData["changed_at"].GetInt64();
    auto videoTime = channelData["video_time"].GetInt();
    auto offset = ms - changedAt + videoTime*1000;
    auto active = channelData["active"].GetString();
    auto it = channelData["videos"].GetObject().MemberBegin();
    auto end = channelData["videos"].GetObject().MemberEnd();
    auto start = it;

    // Get active Startpoint
    for(;;it++) {
        if(it == end) {
            return std::make_pair<bool, iterator>(false, std::move(it));
        }
        if(strcmp(it->name.GetString(),active) == 0) {
            break;
        }
    }

    offset -= H::getSecondsFromYoutubeTime(it->value.GetObject()["length"].GetString())*1000;
    if(offset <= -3000) {
        // Still playing current song
        return std::make_pair<bool, iterator>(true, std::move(it));
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
    ms = H::getTimestamp();
    UpdateChannelRequest channelRequest{channel};
    channelRequest.setChangedAt(ms);
    if(offset < 0) {
        channelRequest.setVideoTime(static_cast<int>(H::getSecondsFromYoutubeTime(it->value.GetObject()["length"].GetString())-offset/1000*-1));
    } else {
        channelRequest.setVideoTime(0);
    }
    channelRequest.setActive(it->name.GetString());
    channelRequest.executeAsync();
    // Hacky synchronization
    channelRequest.join();
    return std::make_pair<bool, iterator>(true, std::move(it));
}
