//
// Created by stevijo on 05.10.16.
//

#ifndef LIVEPLAYLIST_DELETEVIDEOREQUEST_H
#define LIVEPLAYLIST_DELETEVIDEOREQUEST_H

#include <string>
#include "BaseRequest.h"

class DeleteVideoRequest : public BaseRequest {
public:
    DeleteVideoRequest(const std::string& channel, const std::string& video) : channel(channel), video(video) {}
protected:
    void execute();
private:
    std::string channel;
    std::string video;
    constexpr static const char* url = "https://livetubeio-16323.firebaseio.com/channels/";

};


#endif //LIVEPLAYLIST_DELETEVIDEOREQUEST_H
