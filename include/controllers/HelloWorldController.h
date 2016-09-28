//
// Created by stevijo on 28.09.16.
//

#ifndef LIVEPLAYLIST_HELLOWORLDCONTROLLER_H
#define LIVEPLAYLIST_HELLOWORLDCONTROLLER_H

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "BaseController.h"

using namespace Net;

class HelloWorldController : public BaseController<HelloWorldController> {
public:
   void index(const Rest::Request& request, Net::Http::ResponseWriter response) {
       response.send(Http::Code::Ok, "Hello World\n");
   }
};


#endif //LIVEPLAYLIST_HELLOWORLDCONTROLLER_H
