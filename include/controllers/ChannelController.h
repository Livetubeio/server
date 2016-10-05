//
// Created by stevijo on 01.10.16.
//

#ifndef LIVEPLAYLIST_CHANNELCONTROLLER_H
#define LIVEPLAYLIST_CHANNELCONTROLLER_H


#include "BaseController.h"
#include <endpoint.h>
#include <router.h>

using namespace Net;

class ChannelController : public BaseController<ChannelController> {
public:

    void update(const Rest::Request& request, Http::ResponseWriter response);

    void getBadge(const Rest::Request& request, Http::ResponseWriter response);

};


#endif //LIVEPLAYLIST_CHANNELCONTROLLER_H
