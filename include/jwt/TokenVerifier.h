#ifndef LIVEPLAYLIST_TOKENVERIFIER_H
#define LIVEPLAYLIST_TOKENVERIFIER_H

#include "Token.h"
#include <string>

class Token;

/**
 * Class responsible for verifying an JWT Token
 */
class TokenVerifier {
    friend class Token;
    TokenVerifier(Token& token) : token(token) {}
    bool verify();
    Token& token;
};

#endif
