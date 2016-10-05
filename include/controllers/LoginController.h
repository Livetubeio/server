//
// Created by stevijo on 05.10.16.
//

#ifndef LIVEPLAYLIST_LOGINCONTROLLER_H
#define LIVEPLAYLIST_LOGINCONTROLLER_H

#include "BaseController.h"
#include <endpoint.h>

using namespace Net;

class LoginController : public BaseController<LoginController> {
public:

    void login(const Rest::Request& request, Http::ResponseWriter response);

};


#endif //LIVEPLAYLIST_LOGINCONTROLLER_H
