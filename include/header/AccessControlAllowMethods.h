#ifndef LIVEPLAYLIST_ACCESSCONTROLALLOWMETHODS_H
#define LIVEPLAYLIST_ACCESSCONTROLALLOWMETHODS_H

#include <http_header.h>
#include <string>
#include <vector>

class AccessControlAllowMethods : public Net::Http::Header::Header {
public:
    AccessControlAllowMethods() {}
    AccessControlAllowMethods(std::initializer_list<std::string> l) {
        methods.insert(methods.end(),l.begin(), l.end());
    }
    void parse(const std::string& data) {
        auto str = data;
        for(;;) {
            auto pos = str.find(',');
            if(pos == std::string::npos) break;
            methods.push_back(str.substr(0, pos));
            str = str.substr(pos+1);
        }
    }

    void write(std::ostream& os) const {
        for(auto it=begin(methods);it!=end(methods);it++) {
            if(it!=end(methods)-1) {
                os << *it << ", ";
            } else {
                os << *it;
            }
        }
    }

    NAME("Access-Control-Allow-Methods")
private:
    std::vector<std::string> methods;
};

#endif
