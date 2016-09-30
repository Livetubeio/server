//
// Created by stevijo on 30.09.16.
//

#ifndef LIVEPLAYLIST_ADDVIDEOREQUEST_H
#define LIVEPLAYLIST_ADDVIDEOREQUEST_H

#include <string>
#include <json/value.h>

class AddVideoRequest {
public:
    AddVideoRequest(const std::string& channel, const std::string& ytid) : channel(channel), ytid(ytid) { Init(); }
    void execute();
private:
    void Init();
    constexpr static const char* url = "https://livetubeio-16323.firebaseio.com/channels/";
    std::string channel;
    Json::Value youtube;
    std::string ytid;
};


#endif //LIVEPLAYLIST_ADDVIDEOREQUEST_H
