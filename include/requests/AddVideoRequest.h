//
// Created by stevijo on 30.09.16.
//

#ifndef LIVEPLAYLIST_ADDVIDEOREQUEST_H
#define LIVEPLAYLIST_ADDVIDEOREQUEST_H

#include <string>
#include <json/value.h>
#include <condition_variable>

#include "BaseRequest.h"
#include "ThreadPool.h"

class AddVideoRequest : public  BaseRequest {
public:
    AddVideoRequest(const std::string& channel, const std::string& ytid) : channel(channel), ytid(ytid) { }
protected:
    void execute();
private:
    constexpr static const char* url = "https://livetubeio-16323.firebaseio.com/channels/";
    std::string channel;
    std::string ytid;
};


#endif //LIVEPLAYLIST_ADDVIDEOREQUEST_H
