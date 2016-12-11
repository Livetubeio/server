#ifndef LIVEPLAYLIST_LOGINCONTROLLER_H
#define LIVEPLAYLIST_LOGINCONTROLLER_H

#include "BaseController.h"
#include <endpoint.h>

using namespace Net;

/**
 * The LoginController is the controller responsible
 * for login routes
 *
 */
class LoginController : public BaseController<LoginController> {
public:

    void login(const Rest::Request& request, Http::ResponseWriter response);

};


#endif
