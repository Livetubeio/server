#include "jwt/Token.h"

bool Token::decodeAndValid(){
    TokenVerifier verifier(*this);
    return verifier.verify();
}

std::string Token::getGrant(const std::string &grant) {
    if(jwt_token == NULL) return "";
    return jwt_get_grant(jwt_token, grant.c_str());
}

Token::~Token() {
    if(jwt_token != NULL) {
        jwt_free(jwt_token);
    }
}
