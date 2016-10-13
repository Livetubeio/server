//
// Created by stevijo on 05.10.16.
//

#include "controllers/LoginController.h"
#include "jwt/Token.h"
#include "header/XLiveTubeAuth.h"
#include "header/XGithubAuth.h"

void LoginController::login(const Rest::Request& request, Http::ResponseWriter response) {

    auto headers = request.headers();
    auto token = headers.get<XLiveTubeAuth>();
    auto github = headers.get<XGithubAuth>();

    Token jwtToken(token->getToken());
    auto res = jwtToken.decodeAndValid();
    if(!res) {
        response.send(Http::Code::Bad_Request);
        return;
    }
    Github cache(github->getToken(),jwtToken.getGrant("sub"));
    cache.updateCache();

    response.send(Http::Code::Ok);
}
