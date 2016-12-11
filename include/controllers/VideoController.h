#ifndef LIVEPLAYLIST_VIDEOCONTROLLER_H
#define LIVEPLAYLIST_VIDEOCONTROLLER_H

#include <endpoint.h>
#include <router.h>
#include "BaseController.h"

using namespace Net;

/**
 * The VideoController is the controller responsible
 * for video routes
 *
 */
class VideoController : public BaseController<VideoController> {
public:

    void create(const Rest::Request& request, Net::Http::ResponseWriter response);

    void remove(const Rest::Request &request, Net::Http::ResponseWriter response);

};


#endif
