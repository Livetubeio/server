#ifndef LIVEPLAYLIST_ACCESSCONTROLALLOWHEADERS_H
#define LIVEPLAYLIST_ACCESSCONTROLALLOWHEADERS_H

#include <http_header.h>
#include <string>
#include <vector>

class AccessControlAllowHeaders : public Net::Http::Header::Header {
public:
    AccessControlAllowHeaders() {}
    AccessControlAllowHeaders(std::initializer_list<std::string> l) {
        headers.insert(headers.end(),l.begin(), l.end());
    }
    void parse(const std::string& data) {
        auto str = data;
        for(;;) {
            auto pos = str.find(',');
            if(pos == std::string::npos) break;
            headers.push_back(str.substr(0, pos));
            str = str.substr(pos+1);
        }
    }

    void write(std::ostream& os) const {
        for(auto it=begin(headers);it!=end(headers);it++) {
            if(it!=end(headers)-1) {
                os << *it << ", ";
            } else {
                os << *it;
            }
        }
    }

    NAME("Access-Control-Allow-Headers")
private:
    std::vector<std::string> headers;
};


#endif
