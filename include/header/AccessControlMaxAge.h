#ifndef LIVEPLAYLIST_ACCESSCONTROLMAXAGE_H
#define LIVEPLAYLIST_ACCESSCONTROLMAXAGE_H

#include <http_header.h>
#include <stdlib.h>
#include <string>
#include <vector>

class AccessControlMaxAge : public Net::Http::Header::Header {
public:
    AccessControlMaxAge() {}
    AccessControlMaxAge(int age) : age(age) {}
    void parse(const std::string& data) {
        age = std::stoi(data);
    }

    void write(std::ostream& os) const {
        os << age;
    }

    NAME("Access-Control-Max-Age")
private:
    int age;
};


#endif
