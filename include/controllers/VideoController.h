//
// Created by stevijo on 28.09.16.
//

#ifndef LIVEPLAYLIST_SONGCONTROLLER_H
#define LIVEPLAYLIST_SONGCONTROLLER_H

#include <endpoint.h>
#include <router.h>
#include "BaseController.h"

using namespace Net;

class VideoController : public BaseController<VideoController> {
public:

    void create(const Rest::Request& request, Net::Http::ResponseWriter response);

    void remove(const Rest::Request &request, Net::Http::ResponseWriter response);

};


#endif //LIVEPLAYLIST_SONGCONTROLLER_H
