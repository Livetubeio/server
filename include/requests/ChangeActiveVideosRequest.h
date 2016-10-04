//
// Created by stevijo on 01.10.16.
//

#ifndef LIVEPLAYLIST_CHANGEACTIVEVIDEOSREQUEST_H
#define LIVEPLAYLIST_CHANGEACTIVEVIDEOSREQUEST_H

#include "ThreadPool.h"
#include "requests/BaseRequest.h"

class ChangeActiveVideosRequest : public BaseRequest {
public:
    ChangeActiveVideosRequest(const std::string& channel, const std::string& ytid) : channel(channel), ytid(ytid) {}
protected:
    void execute();
private:
    std::string ytid;
    std::string channel;
    constexpr static const char* url = "https://livetubeio-16323.firebaseio.com/channels/";
};


#endif //LIVEPLAYLIST_CHANGEACTIVEVIDEOSREQUEST_H
