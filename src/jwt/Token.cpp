//
// Created by stevijo on 04.10.16.
//

#include "jwt/Token.h"

bool Token::decodeAndValid(){
    TokenVerifier verifier(*this);
    return verifier.verify();
}

std::string Token::getGrant(const std::string &grant) {
    if(jwt_token == NULL) return "";
    return jwt_get_grant(jwt_token, grant.c_str());
}
