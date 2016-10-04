//
// Created by stevijo on 04.10.16.
//

#ifndef LIVEPLAYLIST_TOKEN_H
#define LIVEPLAYLIST_TOKEN_H

#include "TokenVerifier.h"
#include <stdio.h>
#include <jwt.h>
#include <string>

class Token {
public:
    Token(const std::string& token) : token(token) {}
    ~Token() {
        if(jwt_token != NULL) {
            jwt_free(jwt_token);
        }
    }
    Token(Token&& token) = delete;
    Token(const Token&) = delete;
    Token& operator=(const Token& token) = delete;
    friend class TokenVerifier;
    bool decodeAndValid();
    std::string getGrant(const std::string& grant);
private:
    std::string token;
    jwt_t* jwt_token;
};

#endif //LIVEPLAYLIST_TOKEN_H
