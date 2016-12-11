#ifndef LIVEPLAYLIST_TOKEN_H
#define LIVEPLAYLIST_TOKEN_H

#include "TokenVerifier.h"
#include <stdio.h>
#include <jwt.h>
#include <string>

/**
 * Wrapper class for jwt token
 */
class Token {
public:
    Token(const std::string& token) : token(token) {}
    ~Token();
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

#endif
