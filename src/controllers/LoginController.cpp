//
// Created by stevijo on 05.10.16.
//

#include "controllers/LoginController.h"
#include "header/XLiveTubeAuth.h"
#include "header/XGithubAuth.h"

void LoginController::login(const Rest::Request& request, Http::ResponseWriter response) {

    auto headers = request.headers();
    auto github = headers.get<XGithubAuth>();

    Github cache(github->getToken());
    cache.updateCache();

    H::addCorsHeaders(response);
    response.send(Http::Code::Ok);
}
