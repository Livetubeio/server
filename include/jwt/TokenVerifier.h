//
// Created by stevijo on 04.10.16.
//

#ifndef LIVEPLAYLIST_TOKENVERIFIER_H
#define LIVEPLAYLIST_TOKENVERIFIER_H

#include "Token.h"
#include <string>

class Token;

class TokenVerifier {
    friend class Token;
    TokenVerifier(Token& token) : token(token) {}
    bool verify();
    Token& token;
};


#endif //LIVEPLAYLIST_TOKENVERIFIER_H
