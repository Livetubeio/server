//
// Created by stevijo on 02.10.16.
//

#ifndef LIVEPLAYLIST_XLIVETUBEAUTH_H
#define LIVEPLAYLIST_XLIVETUBEAUTH_H

#include <http_header.h>
#include <string>
#include <vector>

class XLiveTubeAuth : public Net::Http::Header::Header {
public:
    XLiveTubeAuth() {}
    XLiveTubeAuth(std::string auth) : auth(auth) {}

    const std::string& getToken() const {
        return auth;
    }

    void parse(const std::string& data) {
        auth = data;
    }

    void write(std::ostream& os) const {
        os << auth;
    }

    NAME("X-LIVETUBE-AUTH")
private:
    std::string auth;
};


#endif //LIVEPLAYLIST_ACCESSCONTROLALLOWORIGIN_H
