
#include "../../include/jwt/Token.h"
#include "../../include/Github.h"
#include "../../include/helper.h"

template<typename T>
bool BaseController<T>::verifyAccess(std::string channel, std::string token, std::string githubToken) {
    Token jwtToken(token);
    auto isValid = jwtToken.decodeAndValid();
    if(!isValid) {
        return false;
    }
    Github githubAuth(githubToken);
    auto res = githubAuth.userOwnsChannel(H::base64decode(channel));
    if(!res) {
        return false;
    }
}

