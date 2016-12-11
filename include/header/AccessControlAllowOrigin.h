#ifndef LIVEPLAYLIST_ACCESSCONTROLALLOWORIGIN_H
#define LIVEPLAYLIST_ACCESSCONTROLALLOWORIGIN_H

#include <http_header.h>
#include <string>
#include <vector>

class AccessControlAllowOrigin : public Net::Http::Header::Header {
public:
    AccessControlAllowOrigin() {}
    AccessControlAllowOrigin(std::initializer_list<std::string> l) {
        origins.insert(origins.end(),l.begin(), l.end());
    }
    void parse(const std::string& data) {
        auto str = data;
        for(;;) {
            auto pos = str.find(',');
            if(pos == std::string::npos) break;
            origins.push_back(str.substr(0, pos));
            str = str.substr(pos+1);
        }
    }

    void write(std::ostream& os) const {
        for(auto it=begin(origins);it!=end(origins);it++) {
            if(it!=end(origins)-1) {
                os << *it << ", ";
            } else {
                os << *it;
            }
        }
    }

    NAME("Access-Control-Allow-Origin")
private:
    std::vector<std::string> origins;
};


#endif
