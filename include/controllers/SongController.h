//
// Created by stevijo on 28.09.16.
//

#ifndef LIVEPLAYLIST_SONGCONTROLLER_H
#define LIVEPLAYLIST_SONGCONTROLLER_H

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "BaseController.h"

using namespace Net;

class SongController : public BaseController<SongController> {
public:

    void create(const Rest::Request& request, Net::Http::ResponseWriter response);

};


#endif //LIVEPLAYLIST_SONGCONTROLLER_H
