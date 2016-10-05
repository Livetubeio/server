//
// Created by stevijo on 05.10.16.
//

#ifndef LIVEPLAYLIST_UPDATECHANNELREQUEST_H
#define LIVEPLAYLIST_UPDATECHANNELREQUEST_H

#include <string>
#include "BaseRequest.h"

class UpdateChannelRequest : public BaseRequest {
public:
    enum class State {
        PLAYING = 1,
        PAUSED = 2
    };
    UpdateChannelRequest(const std::string& channel) : channel(channel) {}
    void setActive(const std::string& active);
    void setState(const State& state);
protected:
    void execute();
private:
    std::string channel;
    std::string active;
    bool hasActive = false;
    State state;
    bool hasState = false;
    constexpr static const char* url = "https://livetubeio-16323.firebaseio.com/channels/";
};


#endif //LIVEPLAYLIST_UPDATECHANNELREQUEST_H
