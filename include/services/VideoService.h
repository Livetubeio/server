//
// Created by stevijo on 16.10.16.
//

#ifndef LIVEPLAYLIST_VIDEOSERVICE_H
#define LIVEPLAYLIST_VIDEOSERVICE_H

#include <string>
#include <rapidjson/document.h>

class VideoService {
public:
    typedef rapidjson::GenericMemberIterator<false, rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> iterator;
    std::pair<bool, iterator> getNextVideo(const std::string& channel);
private:
    rapidjson::Document channelData;
};


#endif //LIVEPLAYLIST_VIDEOSERVICE_H
