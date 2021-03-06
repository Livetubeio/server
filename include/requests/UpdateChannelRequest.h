#ifndef LIVEPLAYLIST_UPDATECHANNELREQUEST_H
#define LIVEPLAYLIST_UPDATECHANNELREQUEST_H

#include <string>
#include <sstream>
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
    void setChangedAt(long changedAt);
    void setVideoTime(int time);
protected:
    void execute();
private:
    std::string channel;
    std::string active;
    bool hasActive = false;
    State state;
    bool hasState = false;
    int videoTime;
    bool hasVideoTime = false;
    long changedAt;
    bool hasChangedAt = false;
};


#endif
