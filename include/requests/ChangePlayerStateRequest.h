//
// Created by stevijo on 01.10.16.
//

#ifndef LIVEPLAYLIST_CHANGEPLAYERSTATEREQUEST_H
#define LIVEPLAYLIST_CHANGEPLAYERSTATEREQUEST_H

#include <string>
#include "requests/BaseRequest.h"

class ChangePlayerStateRequest : public BaseRequest {
public:
    enum class State {
        PLAYING = 1,
        PAUSED = 2
    };
    ChangePlayerStateRequest(const std::string& channel, State state) : channel(channel), state(state) {}
protected:
    void execute();
private:
    std::string channel;
    State state;
    constexpr static const char* url = "https://livetubeio-16323.firebaseio.com/channels/";
};


#endif //LIVEPLAYLIST_CHANGEPLAYERSTATEREQUEST_H
