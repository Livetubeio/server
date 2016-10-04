//
// Created by stevijo on 02.10.16.
//

#ifndef LIVEPLAYLIST_XGITHUBAUTH_H
#define LIVEPLAYLIST_XGITHUBAUTH_H

#include <http_header.h>
#include <string>
#include <vector>

class XGithubAuth : public Net::Http::Header::Header {
public:
    XGithubAuth() {}
    XGithubAuth(std::string auth) : auth(auth) {}

    const std::string& getToken() const {
        return auth;
    }

    void parse(const std::string& data) {
        auth = data;
    }

    void write(std::ostream& os) const {
        os << auth;
    }

    NAME("x-github-auth")
private:
    std::string auth;
};


#endif //LIVEPLAYLIST_ACCESSCONTROLALLOWORIGIN_H
