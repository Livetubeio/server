#ifndef LIVEPLAYLIST_CHANNELCONTROLLER_H
#define LIVEPLAYLIST_CHANNELCONTROLLER_H


#include "BaseController.h"
#include <endpoint.h>
#include <router.h>
#include <chrono>
#include <mutex>

using namespace Net;

/**
 * The ChannelController is the controller responsible
 * for channel routes
 *
 */
class ChannelController : public BaseController<ChannelController> {
public:

    void update(const Rest::Request& request, Http::ResponseWriter response);

    void getBadge(const Rest::Request& request, Http::ResponseWriter response);

    void updateVideo(const Rest::Request& request, Http::ResponseWriter response);
private:
    std::mutex mutex;
    std::chrono::milliseconds lastChange = std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now().time_since_epoch()
    );

};


#endif
